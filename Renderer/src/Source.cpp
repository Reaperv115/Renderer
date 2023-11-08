#include "trpch.h"
#include "Utilities/ErrorLogger.h"

#include <d3d11.h>
#include <dxgi.h>
#include <dxgi1_2.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;
	HWND hwnd;

	int width = 1000;
	int height = 800;

	Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3ddeviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain1> dxgiswapChain;
	Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;

	AllocConsole();
	auto obj = freopen("CONIN$", "r", stdin);
	auto obj2 = freopen("CONOUT$", "w", stdout);
	auto obj3 = freopen("CONOUT$", "w", stderr);

	hInst = hInstance;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.lpszClassName = L"Renderer";
	wc.lpszMenuName = L"Renderer";
	wc.hInstance = hInst;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProcedure;
	RegisterClassEx(&wc);

	// creating window and checking to make sure it succeeded
	hwnd = CreateWindowEx(0, L"Renderer", L"Renderer", WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, hInst, NULL);
	if (hwnd == NULL)
	{
		Rhine::ErrorLogger::Log("Failed to create window handle");
		return -1;
	}
	else
	{
		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);
	}

	
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
	}
	
	hr = CreateDXGIFactory(__uuidof(dxgiFactory), (void**)dxgiFactory.GetAddressOf());
	if (FAILED(hr))
	{
		Rhine::ErrorLogger::Log(hr, "Failed to create factory");
	}
	hr = dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), hwnd, &swapchainDescription, &fullscreenDescription, 0, dxgiswapChain.GetAddressOf());
	if (FAILED(hr))
	{
		Rhine::ErrorLogger::Log(hr, "Failed to create swap chain");
	}
	
#pragma region application loops
	MSG msg = { 0 };
	/*while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/
	
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#pragma endregion working app loops using both GetMessage and PeekMessage

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);
		RECT rect;
		GetClientRect(hwnd, &rect);
		HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
		FillRect(hdc, &rect, brush);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
}