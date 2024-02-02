#pragma once
#include "../Utilities/ErrorLogger.h"
#include "../Engine/Mouse/MouseClass.h"
#include "../Engine/Keyboard/KeyboardClass.h"

namespace glitc
{
	class D3DApplication;

	class WindowCreation
	{
	public:
		WindowCreation();
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
		bool InitializeWindow(D3DApplication* d3dApp, HINSTANCE inst, std::string className, std::string windowName, int width, int height);
		bool Run();
	public:
		HWND GetWindowHandle() const;
		MouseClass* GetMouseClassRef() const;
		KeyboardClass* GetKeyboardClassRef() const;
		HINSTANCE GetApplicationInstance() const;
	private:
		static LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lParam);
		static LRESULT CALLBACK _HandleMessageRedirect(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara);
		MouseClass* mouse = new MouseClass();
		KeyboardClass* keyboard = new KeyboardClass();
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

