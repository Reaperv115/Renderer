#pragma once
#include "../Utilities/ErrorLogger.h"
#include "../Engine/Mouse/MouseClass.h"
#include "../Engine/Keyboard/KeyboardClass.h"

namespace glitc
{
	class WindowCreation
	{
	public:
		WindowCreation();
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
		bool InitializeWindow(HINSTANCE inst, std::string className, std::string windowName, int width, int height);
		bool Run();
	public:
		HWND GetWindowHandle() const;
		MouseClass* GetMouseClassRef() const;
		KeyboardClass* GetKeyboardClassRef() const;
		HINSTANCE GetApplicationInstance() const;
	private:
		static LRESULT CALLBACK ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lParam);
		static LRESULT CALLBACK _ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara);
		MouseClass* mc = new MouseClass();
		KeyboardClass* kbc = new KeyboardClass();
		HWND windowHandle;
		HINSTANCE applicationInstance;
		std::wstring className;
		std::wstring windowName;
		float xPosition, yPosition;
	private:
		void CreateDebugConsoleWindow();
		void RegisterWindowClass();

		
	};
}

