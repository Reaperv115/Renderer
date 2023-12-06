#pragma once
#include "../Utilities/ErrorLogger.h"
#include "../WindowCreation/WindowCreation.h"


namespace Rhine
{
	class Graphics
	{
		ComPtr<ID3D11Device> d3dDevice;
		ComPtr<ID3D11DeviceContext> d3ddeviceContext;
		ComPtr<IDXGISwapChain1> dxgiswapChain;
		ComPtr<IDXGIFactory2> dxgiFactory;
		ComPtr<ID3D11RenderTargetView> rendertargetView;
		ComPtr<ID3D11Texture2D> backBuffer;
		D3D11_VIEWPORT d3d11viewPort;
		ComPtr<ID3D11RasterizerState> rasterizerState;

		ComPtr<ID3D11Buffer> triangleBuffer;
		D3D11_BUFFER_DESC trianglebufferDesc;

		ComPtr<ID3D11Buffer> triangleindexBuffer;
		D3D11_BUFFER_DESC indexbufferDescription;
		D3D11_SUBRESOURCE_DATA triangleData;
		std::string vertexshaderPath = "../bin/x64-Debug/Renderer/VertexShader.cso";
		std::string pixelshaderPath = "../bin/x64-Debug/Renderer/PixelShader.cso";
		ComPtr<ID3DBlob> shaderBuffer;
		ComPtr<ID3D11VertexShader> vShader;
		ComPtr<ID3D11PixelShader> pShader;
		ComPtr<ID3D11InputLayout> triangleinputLayout;
	public:
		bool InitializeDirectX(int width, int height, HWND handle);
		void Render();
	};
}

// error-checking macro
#define RHINE_ASSERT(hr, message) if (FAILED(hr)) {ErrorLogger::Log(hr, message);} 

