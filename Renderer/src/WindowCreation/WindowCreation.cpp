#include "trpch.h"
#include "WindowCreation.h"

	bool glitc::WindowCreation::InitializeWindow(HINSTANCE inst, std::string className, std::string windowName, int width, int height)
	{
		// creating console window to debug
		CreateDebugConsoleWindow();

		// catching instance to application
		applicationInstance = inst;

		// naming the window class and window itself
		this->className = glitc::StringConverter::StringtoWideString(className);
		this->windowName = glitc::StringConverter::StringtoWideString(windowName);

		// registering window class
		RegisterWindowClass();

		// creating render window
		this->windowHandle = CreateWindowEx(0, 
			this->className.c_str(), 
			this->windowName.c_str(), 
			WS_OVERLAPPEDWINDOW, 
			300,
			100,
			width,
			height,
			NULL,
			NULL,
			applicationInstance,
			NULL);

		// checking to see if it was created successfully
		if (this->windowHandle == NULL)
		{
			glitc::ErrorLogger::Log("Failed to initialize window handle");
			return false;
		}
		else
		{
			ShowWindow(this->windowHandle, SW_SHOW);
			UpdateWindow(this->windowHandle);
		}
		return true;
	}

	

	void glitc::WindowCreation::CreateDebugConsoleWindow()
	{
		AllocConsole();
		auto obj = freopen("CONIN$", "r", stdin);
		auto obj2 = freopen("CONOUT$", "w", stdout);
		auto obj3 = freopen("CONOUT$", "w", stderr);
	}

	void glitc::WindowCreation::RegisterWindowClass()
	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.lpszClassName = className.c_str();
		wc.lpszMenuName = windowName.c_str();
		wc.hInstance = applicationInstance;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = (WNDPROC)WindowProcedures;
		RegisterClassEx(&wc);
	}

	HWND glitc::WindowCreation::GetWindowHandle()
	{
		return this->windowHandle;
	}

	bool glitc::WindowCreation::Run()
	{
		// running the application
		MSG msg = { 0 };
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			/*timer.Tick();
			if (!appPaused)
			{
				CalculateFrameStats();
			}*/
		}

		
		if (msg.message == WM_QUIT)
		{
			UnregisterClass(className.c_str(), applicationInstance);
			return false;
		}
		
		return true;
	}

	LRESULT CALLBACK glitc::WindowCreation::WindowProcedures(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
	{
		switch (Msg)
		{
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);
			RECT rect;
			GetClientRect(hwnd, &rect);
			HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
			FillRect(hdc, &rect, brush);
			EndPaint(hwnd, &ps);
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		}
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}


