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
		~WindowCreation();
		bool InitializeWindow(D3DApplication* application, HINSTANCE inst, std::string className, std::string windowName, int width, int height);
		bool Run();
	public:
		HWND GetWindowHandle() const;
		MouseClass* GetMouseClassRef() const;
		KeyboardClass* GetKeyboardClassRef() const;
		HINSTANCE GetApplicationInstance() const;
	private:
		static LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lParam);
		static LRESULT CALLBACK HandleMessageRedirect(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara);
		void RegisterRawInput();
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

