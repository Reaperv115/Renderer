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

	// creating depth/stencil view
	ZeroMemory(&depthstencilDescription, sizeof(depthstencilDescription));
	depthstencilDescription.Width = width;
	depthstencilDescription.Height = height;
	depthstencilDescription.MipLevels = 1;
	depthstencilDescription.ArraySize = 1;
	depthstencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthstencilDescription.SampleDesc.Count = 1;
	depthstencilDescription.SampleDesc.Quality = 0;
	depthstencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthstencilDescription.CPUAccessFlags = 0;
	depthstencilDescription.MiscFlags = 0;
	RHINE_ASSERT(d3dDevice->CreateTexture2D(&depthstencilDescription, NULL, depthstencilBuffer.GetAddressOf()), "Failed to create depth stencil buffer");
	RHINE_ASSERT(d3dDevice->CreateDepthStencilView(depthstencilBuffer.Get(), NULL, depthstencilView.GetAddressOf()), "Failed to create depth stencil view");

	d3ddeviceContext->OMSetRenderTargets(1, rendertargetView.GetAddressOf(), depthstencilView.Get());

	// create depth stencil state
	D3D11_DEPTH_STENCIL_DESC depthstencilDescription;
	ZeroMemory(&depthstencilDescription, sizeof(depthstencilDescription));
	depthstencilDescription.DepthEnable = true;
	depthstencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthstencilDescription.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	RHINE_ASSERT(d3dDevice->CreateDepthStencilState(&depthstencilDescription, depthstencilState.GetAddressOf()), "Failed to create depth stencil state");

	// creating and setting viewport
	d3d11viewPort.TopLeftX = 0;
	d3d11viewPort.TopLeftY = 0;
	d3d11viewPort.MinDepth = 0.0f;
	d3d11viewPort.MaxDepth = 1.0f;
	d3d11viewPort.Width = 800;
	d3d11viewPort.Height = 600;
	d3ddeviceContext->RSSetViewports(1, &d3d11viewPort);

	// creating rasterizer state
	D3D11_RASTERIZER_DESC rasterizerDescription;
	ZeroMemory(&rasterizerDescription, sizeof(rasterizerDescription));
	rasterizerDescription.CullMode = D3D11_CULL_FRONT;
	rasterizerDescription.FillMode = D3D11_FILL_SOLID;
	rasterizerDescription.FrontCounterClockwise = true;
	RHINE_ASSERT(d3dDevice->CreateRasterizerState(&rasterizerDescription, rasterizerState.GetAddressOf()), "Failed to create rasterizer state");

	

	return true;
}


void Rhine::Graphics::InitializeScene()
{
	

	// green triangle vertex buffer data
	Vertex Triangle[] =
	{
		{ -0.5f,  -0.5f,   1.0f,	  0.0f, 1.0f, 0.0f },// bottom left
		{  0.5f,   0.5f,   1.0f,	  0.0f, 1.0f, 0.0f },// top
		{  0.5f,  -0.5f,   1.0f,	  0.0f, 1.0f, 0.0f },// bottom right
	};
	D3D11_BUFFER_DESC bufferDescription;
	ZeroMemory(&bufferDescription, sizeof(bufferDescription));
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescription.ByteWidth = sizeof(Triangle);
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.CPUAccessFlags = 0;
	bufferDescription.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA Data;
	ZeroMemory(&Data, sizeof(Data));
	Data.pSysMem = Triangle;
	RHINE_ASSERT(d3dDevice->CreateBuffer(&bufferDescription, &Data, triangleBuffer.GetAddressOf()), "Failed to create vertex buffer");

	

	// red rectangle vertex buffer data
	Vertex Rectangle[] =
	{
		{ -0.25f,  -0.25f, 0.0f,       1.0f, 0.0f, 0.0f },// bottom left
		{ -0.25f,   0.25f, 0.0f,	   1.0f, 0.0f, 0.0f },// top left
		{  0.25f,   0.25f, 0.0f,	   1.0f, 0.0f, 0.0f },// top right

		{  0.25f,   0.25f, 0.0f,       1.0f, 0.0f, 0.0f },// top right
		{ -0.25f,  -0.25f, 0.0f,       1.0f, 0.0f, 0.0f },// bottom left
		{  0.25f,  -0.25f, 0.0f,       1.0f, 0.0f, 0.0f }// bottom right
	};
	D3D11_BUFFER_DESC tmprectanglebufrerDescription;
	ZeroMemory(&tmprectanglebufrerDescription, sizeof(tmprectanglebufrerDescription));
	tmprectanglebufrerDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tmprectanglebufrerDescription.ByteWidth = sizeof(Rectangle);
	tmprectanglebufrerDescription.Usage = D3D11_USAGE_DEFAULT;
	tmprectanglebufrerDescription.CPUAccessFlags = 0;
	tmprectanglebufrerDescription.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA tmprectangleData;
	ZeroMemory(&tmprectangleData, sizeof(tmprectangleData));
	tmprectangleData.pSysMem = Rectangle;
	RHINE_ASSERT(d3dDevice->CreateBuffer(&tmprectanglebufrerDescription, &tmprectangleData, rectangleBuffer.GetAddressOf()), "Failed to create vertex buffer");
	
	// vertex shader
	D3D11_INPUT_ELEMENT_DESC rectanglelayoutDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	UINT numElements = ARRAYSIZE(rectanglelayoutDesc);

	// creating vertex shader
	RHINE_ASSERT(D3DReadFileToBlob(StringConverter::StringtoWideString(vertexshaderPath).c_str(), shaderBuffer.GetAddressOf()), "Failed to read vertex shader");
	RHINE_ASSERT(d3dDevice->CreateVertexShader(shaderBuffer.Get()->GetBufferPointer(), shaderBuffer.Get()->GetBufferSize(), NULL, vShader.GetAddressOf()), "Failed to create vertex shader");
	RHINE_ASSERT(d3dDevice->CreateInputLayout(rectanglelayoutDesc, numElements, shaderBuffer->GetBufferPointer(), shaderBuffer->GetBufferSize(), rectangleinputLayout.GetAddressOf()), "Failed to create input layout");

	// pixel shader
	RHINE_ASSERT(D3DReadFileToBlob(StringConverter::StringtoWideString(pixelshaderPath).c_str(), shaderBuffer.GetAddressOf()), "Failed to read pixel shader");
	RHINE_ASSERT(d3dDevice->CreatePixelShader(shaderBuffer.Get()->GetBufferPointer(), shaderBuffer.Get()->GetBufferSize(), NULL, pShader.GetAddressOf()), "Failed to create pixel shader");

	
}

void Rhine::Graphics::Render()
{
	// clearing backbuffer to some color
	float rgba[] = { 1.0f, 1.0, 1.0f, 1.0f };
	d3ddeviceContext->ClearRenderTargetView(rendertargetView.Get(), rgba);
	d3ddeviceContext->ClearDepthStencilView(depthstencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);


	
	// drawing square
	d3ddeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	d3ddeviceContext->RSSetState(rasterizerState.Get());
	d3ddeviceContext->OMSetDepthStencilState(depthstencilState.Get(), 0);
	d3ddeviceContext->IASetInputLayout(rectangleinputLayout.Get());
	d3ddeviceContext->VSSetShader(vShader.Get(), NULL, 0);
	d3ddeviceContext->PSSetShader(pShader.Get(), NULL, 0);

	
	DrawRectangle(0.25f, 0.25f);
	DrawTriangle(0.5f, 0.5f);
	d3ddeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DrawRectangleIndexed();

	
	/*d3ddeviceContext->IASetIndexBuffer(rectangleindexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
	d3ddeviceContext->DrawIndexed(6, 0, 0);*/
	

	dxgiswapChain->Present(1, 0);
}

void Rhine::Graphics::DrawTriangle(float x, float y)
{
	// vertex data structure
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;

		struct
		{
			float r, g, b;
		} col;
	};

	// green triangle vertex buffer data
	Vertex Triangle[] =
	{
		{ -0.5f,  -0.5f,   1.0f,	  0.0f, 1.0f, 0.0f },// bottom left
		{  0.5f,   0.5f,   1.0f,	  0.0f, 1.0f, 0.0f },// top
		{  0.5f,  -0.5f,   1.0f,	  0.0f, 1.0f, 0.0f },// bottom right
	};
	D3D11_BUFFER_DESC bufferDescription;
	ZeroMemory(&bufferDescription, sizeof(bufferDescription));
	bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDescription.ByteWidth = sizeof(Triangle);
	bufferDescription.Usage = D3D11_USAGE_DEFAULT;
	bufferDescription.CPUAccessFlags = 0;
	bufferDescription.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA Data;
	ZeroMemory(&Data, sizeof(Data));
	Data.pSysMem = Triangle;
	RHINE_ASSERT(d3dDevice->CreateBuffer(&bufferDescription, &Data, triangleBuffer.GetAddressOf()), "Failed to create vertex buffer");
	d3ddeviceContext->IASetVertexBuffers(0, 1, triangleBuffer.GetAddressOf(), &stride, &offset);
	d3ddeviceContext->Draw(std::size(Triangle), 0);
}

void Rhine::Graphics::DrawRectangle(float x, float y)
{
	// vertex data structure
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;

		struct
		{
			float r, g, b;
		} col;
	};

	// red rectangle vertex buffer data
	Vertex Rectangle[] =
	{
		{ -x,  -y, 0.0f,       1.0f, 0.0f, 0.0f },// bottom left
		{ -x,   y, 0.0f,	   1.0f, 0.0f, 0.0f },// top left
		{  x,   y, 0.0f,	   1.0f, 0.0f, 0.0f },// top right

		{  x,   y, 0.0f,       1.0f, 0.0f, 0.0f },// top right
		{ -x,  -y, 0.0f,       1.0f, 0.0f, 0.0f },// bottom left
		{  x,  -y, 0.0f,       1.0f, 0.0f, 0.0f }// bottom right
	};
	D3D11_BUFFER_DESC tmprectanglebufrerDescription;
	ZeroMemory(&tmprectanglebufrerDescription, sizeof(tmprectanglebufrerDescription));
	tmprectanglebufrerDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tmprectanglebufrerDescription.ByteWidth = sizeof(Rectangle);
	tmprectanglebufrerDescription.Usage = D3D11_USAGE_DEFAULT;
	tmprectanglebufrerDescription.CPUAccessFlags = 0;
	tmprectanglebufrerDescription.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA tmprectangleData;
	ZeroMemory(&tmprectangleData, sizeof(tmprectangleData));
	tmprectangleData.pSysMem = Rectangle;
	RHINE_ASSERT(d3dDevice->CreateBuffer(&tmprectanglebufrerDescription, &tmprectangleData, rectangleBuffer.GetAddressOf()), "Failed to create vertex buffer");
	d3ddeviceContext->IASetVertexBuffers(0, 1, rectangleBuffer.GetAddressOf(), &stride, &offset);
	d3ddeviceContext->Draw(std::size(Rectangle), 0);
}

void Rhine::Graphics::DrawRectangleIndexed()
{
	// vertex data structure
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
		} pos;

		struct
		{
			float r, g, b;
		} col;
	};

	// rectangle vertex buffer data
	Vertex Rectangle[] =
	{
		{ -0.25f,  -0.9f, 0.0f,       1.0f, 0.0f, 0.0f },// bottom left
		{ -0.25f,   -0.7f, 0.0f,	   1.0f, 0.0f, 0.0f },// top left
		{  0.25f,   -0.7f, 0.0f,	   1.0f, 0.0f, 0.0f },// top right
		{  0.25f,  -0.9f, 0.0f,       1.0f, 0.0f, 0.0f }// bottom right
	};
	ComPtr<ID3D11Buffer> tmpBuffer;
	D3D11_BUFFER_DESC tmprectanglebufrerDescription;
	ZeroMemory(&tmprectanglebufrerDescription, sizeof(tmprectanglebufrerDescription));
	tmprectanglebufrerDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tmprectanglebufrerDescription.ByteWidth = sizeof(Rectangle);
	tmprectanglebufrerDescription.Usage = D3D11_USAGE_DEFAULT;
	tmprectanglebufrerDescription.CPUAccessFlags = 0;
	tmprectanglebufrerDescription.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA tmprectangleData;
	ZeroMemory(&tmprectangleData, sizeof(tmprectangleData));
	tmprectangleData.pSysMem = Rectangle;
	RHINE_ASSERT(d3dDevice->CreateBuffer(&tmprectanglebufrerDescription, &tmprectangleData, tmpBuffer.GetAddressOf()), "Failed to create vertex buffer");

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	d3ddeviceContext->IASetVertexBuffers(0, 1, tmpBuffer.GetAddressOf(), &stride, &offset);

	// rectangle index buffer data
	unsigned int indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};
	ComPtr<ID3D11Buffer> rectangleindexBuffer;
	D3D11_BUFFER_DESC indexbufferDescription;
	ZeroMemory(&indexbufferDescription, sizeof(indexbufferDescription));
	indexbufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexbufferDescription.Usage = D3D11_USAGE_DEFAULT;
	indexbufferDescription.CPUAccessFlags = 0;
	indexbufferDescription.MiscFlags = 0;
	indexbufferDescription.ByteWidth = sizeof(indices);
	indexbufferDescription.StructureByteStride = sizeof(unsigned int);
	D3D11_SUBRESOURCE_DATA rectangleData;
	ZeroMemory(&rectangleData, sizeof(rectangleData));
	rectangleData.pSysMem = indices;
	RHINE_ASSERT(d3dDevice->CreateBuffer(&indexbufferDescription, &rectangleData, rectangleindexBuffer.GetAddressOf()), "Failed to create index buffer");
	d3ddeviceContext->IASetIndexBuffer(rectangleindexBuffer.Get(), DXGI_FORMAT_R32G32B32_FLOAT, 0);
	d3ddeviceContext->DrawIndexed(std::size(indices), 0, 0);
}

