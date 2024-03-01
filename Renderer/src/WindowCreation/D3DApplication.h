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

		LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	protected:
		WindowCreation windowCreation;
		KeyboardClass keyboard;
		MouseClass mouse;
		Graphics gfx;

	private:
		float fWidth, fHeight;

		static LRESULT CALLBACK ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lParam);
		static LRESULT CALLBACK _ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara);
		void RegisterRawInput();
	};
}

