#pragma once
#include "../Utilities/ErrorLogger.h"
#include "../Engine/Timer.h"

namespace Rhine
{
	static bool appPaused = false;
	static Timer timer;
	static int frameCnt = 0;
	static float timeelapsed = 0.0f;
	class WindowCreation
	{
	public:
		bool InitializeWindow(HINSTANCE inst, std::string className, std::string windowName, int width, int height);
		bool Run();
		HWND GetWindowHandle();
	private:
		HWND windowHandle;
		HINSTANCE applicationInstance;
		std::wstring className;
		std::wstring windowName;
		std::wstring mainwndCaption;
		

	private:
		void CalculateFrameStats();
		void CreateDebugConsoleWindow();
		void RegisterWindowClass();


		// function for running the window
		static LRESULT CALLBACK WindowProcedures(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	};
}

