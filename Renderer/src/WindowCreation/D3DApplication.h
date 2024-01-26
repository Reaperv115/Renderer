#pragma once
#include "WindowCreation.h"
#include "../Graphics/Graphics.h"



namespace glitc
{
	namespace wrl = Microsoft::WRL;
	class D3DApplication
	{
	public:
		D3DApplication();
		HINSTANCE GetApplicationInstance() const;
		HWND GetWindowHandle() const;
	protected:
		WindowCreation* windowCreation = new WindowCreation();
		Graphics* gfx = new Graphics();

		HINSTANCE hInst;
		HWND windowHandle;

		bool InitializeRenderWindow(HINSTANCE hInst, std::string className, std::string windowName, float width, float height);
		bool InitializeGraphicsAPI(float width, float height, HWND handle);

		wrl::ComPtr<ID3D11Device> pDevice;
		wrl::ComPtr<ID3D11DeviceContext> pdeviceContext;
		wrl::ComPtr<IDXGISwapChain1> pswapChain;
		wrl::ComPtr<IDXGIFactory1> pFactory;
		wrl::ComPtr<ID3D11RenderTargetView> prendertargetView;
		wrl::ComPtr<ID3D11Texture2D> backBuffer;
		D3D11_VIEWPORT viewPort;
	private:
		float fWidth, fHeight;

	};
}

