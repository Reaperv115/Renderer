#pragma once
#include "../Utilities/ErrorLogger.h"
#include "../WindowCreation/WindowCreation.h"
namespace Rhine
{
	class Graphics
	{
		Microsoft::WRL::ComPtr<ID3D11Device> d3dDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> d3ddeviceContext;
		Microsoft::WRL::ComPtr<IDXGISwapChain1> dxgiswapChain;
		Microsoft::WRL::ComPtr<IDXGIFactory2> dxgiFactory;
	public:
		bool InitializeDirectX(int width, int height, WindowCreation windowCreation);
	};
}

