#include "trpch.h"
#include "WindowCreation.h"

	bool Rhine::WindowCreation::InitializeWindow(HINSTANCE inst, std::string className, std::string windowName, int width, int height)
	{
		// creating console window to debug
		CreateDebugConsoleWindow();

		// catching instance to application
		applicationInstance = inst;

		// naming the window class and window itself
		this->className = Rhine::StringConverter::StringtoWideString(className);
		this->windowName = Rhine::StringConverter::StringtoWideString(windowName);

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
			Rhine::ErrorLogger::Log("Failed to initialize window handle");
			return false;
		}
		else
		{
			ShowWindow(this->windowHandle, SW_SHOW);
			UpdateWindow(this->windowHandle);
		}
		return true;
	}

	void Rhine::WindowCreation::CalculateFrameStats()
	{
		
		frameCnt++;
		
		if ((timer.TotalTime() - timeelapsed) >= 1.0f)
		{
			float fps = (float)frameCnt;
			float mspf = 1000.0f / fps;

			std::wostringstream outs;
			outs.precision(6);
			outs << mainwndCaption << L" "
				<< L"FPS: " << fps << L" "
				<< L"Frame Time: " << mspf << L" (ms)";
			SetWindowText(windowHandle, outs.str().c_str());

			timeelapsed += 1.0f;
		}
		else
		{
			frameCnt = 0;
			
		}
	}
	

	void Rhine::WindowCreation::CreateDebugConsoleWindow()
	{
		AllocConsole();
		auto obj = freopen("CONIN$", "r", stdin);
		auto obj2 = freopen("CONOUT$", "w", stdout);
		auto obj3 = freopen("CONOUT$", "w", stderr);
	}

	void Rhine::WindowCreation::RegisterWindowClass()
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

	HWND Rhine::WindowCreation::GetWindowHandle()
	{
		return this->windowHandle;
	}

	bool Rhine::WindowCreation::Run()
	{
		// running the application
		MSG msg = { 0 };
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			timer.Tick();
			if (!appPaused)
			{
				CalculateFrameStats();
			}
		}

		
		if (msg.message == WM_QUIT)
		{
			UnregisterClass(className.c_str(), applicationInstance);
			return false;
		}
		
		return true;
	}

	LRESULT CALLBACK Rhine::WindowCreation::WindowProcedures(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		case WM_ACTIVATE:
			if (LOWORD(wParam) == WA_INACTIVE)
			{
				Rhine::appPaused = true;
				timer.Stop();
			}
			else
			{
				Rhine::appPaused = false;
				timer.Start();
			}
		}
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}


