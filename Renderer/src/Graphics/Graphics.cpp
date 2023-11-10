#include "trpch.h"
#include "Graphics.h"

bool Rhine::Graphics::InitializeDirectX(int width, int height, HWND handle)
{
	// filling out swap chain description
	DXGI_SWAP_CHAIN_DESC1 swapchainDescription;
	ZeroMemory(&swapchainDescription, sizeof(DXGI_SWAP_CHAIN_DESC1));
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
	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDescription;
	ZeroMemory(&fullscreenDescription, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));
	fullscreenDescription.RefreshRate.Numerator = 60;
	fullscreenDescription.RefreshRate.Denominator = 1;
	fullscreenDescription.Windowed = true;

	// creating and error-checking various components needed for d3d11.
	// return true if they all succeed and false if any fail
	HRESULT hr = D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_DEBUG, 0, 0, D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), 0, d3ddeviceContext.GetAddressOf());
	if (FAILED(hr))
	{
		Rhine::ErrorLogger::Log(hr, "Failed to create Device");
		return false;
	}

	hr = CreateDXGIFactory(__uuidof(dxgiFactory), (void**)dxgiFactory.GetAddressOf());
	if (FAILED(hr))
	{
		Rhine::ErrorLogger::Log(hr, "Failed to create factory");
		return false;
	}

	hr = dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), handle, &swapchainDescription, &fullscreenDescription, 0, dxgiswapChain.GetAddressOf());
	if (FAILED(hr))
	{
		Rhine::ErrorLogger::Log(hr, "Failed to create swap chain");
		return false;
	}

	// creating backbuffer to create RenderTargetView to render to
	dxgiswapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&backBuffer);
	d3dDevice->CreateRenderTargetView(backBuffer.Get(), 0, rendertargetView.GetAddressOf());

	// creating and setting viewport
	d3d11viewPort.TopLeftX = 0;
	d3d11viewPort.TopLeftY = 0;
	d3d11viewPort.MinDepth = 0.0f;
	d3d11viewPort.MaxDepth = 1.0f;
	d3d11viewPort.Width = width;
	d3d11viewPort.Height = height;
	d3ddeviceContext->RSSetViewports(1, &d3d11viewPort);

	return true;
}

void Rhine::Graphics::Render()
{
	float rgba[] = {0.0f, 1.0, 0.0f, 1.0f};
	d3ddeviceContext->ClearRenderTargetView(rendertargetView.Get(), rgba);
	dxgiswapChain->Present(1, 0);
}
