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
		static double GetWidth();
		static double GetHeight();
	protected:
		WindowCreation windowCreation;
		KeyboardClass keyboard;
		MouseClass mouse;
		Graphics gfx;
		double width, height;
	private:
		static LRESULT CALLBACK ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lParam);
		static LRESULT CALLBACK _ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara);
		void RegisterRawInput();
	};
}

