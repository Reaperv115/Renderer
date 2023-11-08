#pragma once
#include "../Utilities/StringConverter.h"
#include "../Utilities/ErrorLogger.h"

namespace Rhine
{
	class WindowCreation
	{
	public:
		bool InitializeWindow(HINSTANCE inst, std::string className, std::string windowName);
		bool Run();
	private:
		int width = 1000;
		int height = 800;
	private:
		HWND windowHandle;
		HINSTANCE applicationInstance;
		std::wstring className;
		std::wstring windowName;
	private:

		void CreateConsoleWindow();
		void RegisterWindowClass();

		// function for running the window
		static LRESULT CALLBACK WindowProcedures(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	};
}

