#include "trpch.h"
#include "Graphics.h"

bool Rhine::Graphics::InitializeDirectX(int width, int height, WindowCreation windowCreation)
{
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


	DXGI_SWAP_CHAIN_FULLSCREEN_DESC fullscreenDescription;
	ZeroMemory(&fullscreenDescription, sizeof(DXGI_SWAP_CHAIN_FULLSCREEN_DESC));
	fullscreenDescription.RefreshRate.Numerator = 60;
	fullscreenDescription.RefreshRate.Denominator = 1;
	fullscreenDescription.Windowed = true;
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
	hr = dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), windowCreation.GetWindowHandle(), &swapchainDescription, &fullscreenDescription, 0, dxgiswapChain.GetAddressOf());
	if (FAILED(hr))
	{
		Rhine::ErrorLogger::Log(hr, "Failed to create swap chain");
		return false;
	}
	return true;
}
