#include "trpch.h"
#include "Graphics.h"



bool Rhine::Graphics::InitializeDirectX(int width, int height, HWND handle)
{
	// filling out swap chain description
	DXGI_SWAP_CHAIN_DESC1 swapchainDescription = { 0 };
	swapchainDescription.BufferCount = 1;
	swapchainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	swapchainDescription.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapchainDescription.Width = width;
	swapchainDescription.Height = height;
	swapchainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDescription.SampleDesc.Count = 1;
	swapchainDescription.SampleDesc.Quality = 0;

	// filling out options for going full-screen
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDescription = { 0 };
	fullscreenDescription.RefreshRate.Numerator = 60;
	fullscreenDescription.RefreshRate.Denominator = 1;
	fullscreenDescription.Windowed = true;

	// creating device
	RHINE_ASSERT(D3D11CreateDevice(NULL, 
		D3D_DRIVER_TYPE_HARDWARE, 
		NULL, 
		D3D11_CREATE_DEVICE_DEBUG, 
		0, 
		0, 
		D3D11_SDK_VERSION, 
		d3dDevice.GetAddressOf(), 
		0, 
		d3ddeviceContext.GetAddressOf()), "Failed to create device");
	// creating factory
	RHINE_ASSERT(CreateDXGIFactory(__uuidof(dxgiFactory), (void**)dxgiFactory.GetAddressOf()), "Failed to create factory");

	// creating swapchain
	RHINE_ASSERT(dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), handle, &swapchainDescription, &fullscreenDescription, 0, dxgiswapChain.GetAddressOf()), "Failed to create swapchain");

	// creating backbuffer to create RenderTargetView to render to
	RHINE_ASSERT(dxgiswapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer), "Failed to create backbuffer");
	RHINE_ASSERT(d3dDevice->CreateRenderTargetView(backBuffer.Get(), 0, rendertargetView.GetAddressOf()), "Failed to create render target view");

	return true;
}


void Rhine::Graphics::Render()
{
	float rgba[] = {1.0f, 1.0, 1.0f, 1.0f};
	

	struct Vertex
	{
		float x;
		float y;

		float r, g, b;
	};

	Vertex Triangle[] =
	{
		{0.0f, 0.5f, 1.0f, 0.0f, 0.0f},
		{0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
		{-0.5f, 0.0f, 0.0f, 0.0f, 1.0f},

		{0.5f, 0.5f, 1.0f, 0.0f, 0.0f},
		{0.5f, 0.8f, 0.0f, 1.0f, 0.0f},
		{0.7f, 0.5f, 0.0f, 0.0f, 1.0f}
	};

	// triangle buffer description
	trianglebufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	trianglebufferDesc.ByteWidth = sizeof(Triangle);
	trianglebufferDesc.Usage = D3D11_USAGE_DEFAULT;
	trianglebufferDesc.CPUAccessFlags = 0;
	trianglebufferDesc.MiscFlags = 0;

	triangleData.pSysMem = Triangle;
	triangleData.SysMemPitch = 0;
	triangleData.SysMemSlicePitch = 0;
	RHINE_ASSERT(d3dDevice->CreateBuffer(&trianglebufferDesc, &triangleData, triangleBuffer.GetAddressOf()), "Failed to create vertex buffer");

	// vertex shader
	D3D11_INPUT_ELEMENT_DESC trianglelayoutDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(trianglelayoutDesc);

	// creating vertex shader
	RHINE_ASSERT(D3DReadFileToBlob(StringConverter::StringtoWideString(vertexshaderPath).c_str(), shaderBuffer.GetAddressOf()), "Failed to read vertex shader");
	RHINE_ASSERT(d3dDevice->CreateVertexShader(shaderBuffer.Get()->GetBufferPointer(), shaderBuffer.Get()->GetBufferSize(), NULL, vShader.GetAddressOf()), "Failed to create vertex shader");
	RHINE_ASSERT(d3dDevice->CreateInputLayout(trianglelayoutDesc, numElements, shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), triangleinputLayout.GetAddressOf()), "Failed to create input layout");

	// pixel shader
	RHINE_ASSERT(D3DReadFileToBlob(StringConverter::StringtoWideString(pixelshaderPath).c_str(), shaderBuffer.GetAddressOf()), "Failed to read pixel shader");
	RHINE_ASSERT(d3dDevice->CreatePixelShader(shaderBuffer.Get()->GetBufferPointer(), shaderBuffer.Get()->GetBufferSize(), NULL, pShader.GetAddressOf()), "Failed to create pixel shader");

	d3ddeviceContext->OMSetRenderTargets(1, rendertargetView.GetAddressOf(), nullptr);

	// creating and setting viewport
	d3d11viewPort.TopLeftX = 0;
	d3d11viewPort.TopLeftY = 0;
	d3d11viewPort.MinDepth = 0.0f;
	d3d11viewPort.MaxDepth = 1.0f;
	d3d11viewPort.Width = 800;
	d3d11viewPort.Height = 600;
	d3ddeviceContext->RSSetViewports(1, &d3d11viewPort);

	d3ddeviceContext->ClearRenderTargetView(rendertargetView.Get(), rgba);
	d3ddeviceContext->IASetInputLayout(triangleinputLayout.Get());
	d3ddeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3ddeviceContext->IASetVertexBuffers(0, 1, triangleBuffer.GetAddressOf(), &stride, &offset);
	d3ddeviceContext->VSSetShader(vShader.Get(), NULL, 0);
	d3ddeviceContext->PSSetShader(pShader.Get(), NULL, 0);

	

	d3ddeviceContext->Draw((UINT)std::size(Triangle), 0);

	dxgiswapChain->Present(1, 0);
}
