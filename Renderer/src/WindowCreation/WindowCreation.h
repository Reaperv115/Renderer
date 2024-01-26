#pragma once
#include "../Utilities/ErrorLogger.h"
#include "../Engine/Mouse/MouseClass.h"

namespace glitc
{
	class WindowCreation
	{
	public:
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
		bool InitializeWindow(HINSTANCE inst, std::string className, std::string windowName, int width, int height);
		bool Run();
		HWND GetWindowHandle();
		MouseClass* GetMouseClassRef();
	private:
		static LRESULT CALLBACK ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lParam);
		static LRESULT CALLBACK _ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara);
		HWND windowHandle;
		HINSTANCE applicationInstance;
		std::wstring className;
		std::wstring windowName;
		std::wstring mainwndCaption;
		MouseClass *mc = new MouseClass();
		

	private:
		void CreateDebugConsoleWindow();
		void RegisterWindowClass();

		
	};
}

