#pragma once
#include "../Utilities/ErrorLogger.h"
#include "../Utilities/Vertex.h"
#include "../Utilities/Matrices.h"



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
		ComPtr<ID3D11DepthStencilView> depthstencilView;
		ComPtr<ID3D11Texture2D> depthstencilBuffer;
		D3D11_TEXTURE2D_DESC depthstencilDescription;
		ComPtr<ID3D11DepthStencilState> depthstencilState;
		ComPtr<ID3D11SamplerState> samplerState;
		ComPtr<ID3D11ShaderResourceView> GGtexture;
		ComPtr<ID3D11ShaderResourceView> Marveltexture;
		ComPtr<ID3D11ShaderResourceView> Doomtexture;

		Rhine::Transform transform;

		ComPtr<ID3D11Buffer> triangleBuffer;
		ComPtr<ID3D11Buffer> rectangleBuffer;
		ComPtr<ID3D11Buffer> constantBuffer;

		std::string vertexshaderPath = "../bin/x64-Debug/Renderer/VertexShader.cso";
		std::string pixelshaderPath = "../bin/x64-Debug/Renderer/PixelShader.cso";
		ComPtr<ID3DBlob> shaderBuffer;
		ComPtr<ID3D11VertexShader> vShader;
		ComPtr<ID3D11PixelShader> pShader;
		ComPtr<ID3D11InputLayout> rectangleinputLayout;
	public:
		bool InitializeDirectX(int width, int height, HWND handle);
		void InitializeScene();
		void Render(double deltatime);
		void DrawTriangle(float x, float y);
		void DrawRectangle(float x, float y);
		void DrawRectangleIndexed(double deltatime);
		void DrawTriangleIndexed();
	private:
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
	};

	
}

// error-checking macro
#define RHINE_ASSERT(hr, message) if (FAILED(hr)) {ErrorLogger::Log(hr, message);} 

