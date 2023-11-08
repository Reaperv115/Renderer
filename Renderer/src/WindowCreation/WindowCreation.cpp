#include "trpch.h"
#include "WindowCreation.h"

namespace Rhine
{
	bool Rhine::WindowCreation::InitializeWindow(HINSTANCE inst, std::string className, std::string windowName)
	{
		CreateConsoleWindow();
		applicationInstance = inst;
		this->className = Rhine::StringConverter::StringtoWideString(className);
		this->windowName = Rhine::StringConverter::StringtoWideString(windowName);
		RegisterWindowClass();
		windowHandle = CreateWindowEx(0, 
			this->className.c_str(), 
			this->windowName.c_str(), 
			WS_OVERLAPPEDWINDOW, 
			0,
			0,
			width,
			height,
			NULL,
			NULL,
			applicationInstance,
			NULL);

		if (windowHandle == NULL)
		{
			Rhine::ErrorLogger::Log("Failed to initialize window handle");
			return false;
		}
		else
		{
			ShowWindow(windowHandle, SW_SHOW);
			UpdateWindow(windowHandle);
		}
		return true;
	}

	void Rhine::WindowCreation::CreateConsoleWindow()
	{
		AllocConsole();
		auto obj = freopen("CONIN$", "r", stdin);
		auto obj2 = freopen("CONOUT$", "w", stdout);
		auto obj3 = freopen("CONOUT$", "w", stderr);
	}

	void WindowCreation::RegisterWindowClass()
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

	bool WindowCreation::Run()
	{
		MSG msg = { 0 };
		while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			std::cout << "Application running" << std::endl;
		}
		return true;
	}

	LRESULT CALLBACK WindowCreation::WindowProcedures(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
		default:
			return DefWindowProc(hwnd, Msg, wParam, lParam);
		}
	}

}
