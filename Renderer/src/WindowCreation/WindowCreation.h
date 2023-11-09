#pragma once
#include "../Utilities/ErrorLogger.h"

namespace Rhine
{
	class WindowCreation
	{
	public:
		bool InitializeWindow(HINSTANCE inst, std::string className, std::string windowName, int width, int height);
		void Run();
		HWND GetWindowHandle();
	private:
		HWND windowHandle;
		HINSTANCE applicationInstance;
		std::wstring className;
		std::wstring windowName;
	private:

		void CreateDebugConsoleWindow();
		void RegisterWindowClass();


		// function for running the window
		static LRESULT CALLBACK WindowProcedures(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	};
}

