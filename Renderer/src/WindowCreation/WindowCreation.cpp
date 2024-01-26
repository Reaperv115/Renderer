#include "trpch.h"
#include "WindowCreation.h"



LRESULT CALLBACK glitc::WindowCreation::WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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
	case WM_MOUSEMOVE:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mc->OnMouseMove(x, y);
		break;
	}
	}
	return DefWindowProc(hwnd, Msg, wParam, lParam);
}

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
		windowHandle = CreateWindowEx(0, 
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
			(LPVOID)this);

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

	

LRESULT CALLBACK glitc::WindowCreation::ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
	if (msg == WM_NCCREATE)
	{
		// extract ptr to window from class from creation data
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lPara);
		WindowCreation* const pWnd = reinterpret_cast<WindowCreation*>(pCreate->lpCreateParams);
		//sanity check
		assert(pWnd != nullptr);
		// set WinAPI-managed user data to store ptr to window class
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		// set message proc to normal handler now that setup is finished
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&WindowCreation::_ProcessMessageSetup));
		// forward message to window class handler
		return pWnd->WindowProc(hwnd, msg, wPara, lPara);
	}
	// if we get a message before the WM_NCCREATE message, handle with default handler
	return DefWindowProc(hwnd, msg, wPara, lPara);
}

LRESULT CALLBACK glitc::WindowCreation::_ProcessMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara)
{
	// retrieve ptr to window class
	WindowCreation* const pWnd = reinterpret_cast<WindowCreation*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
	// forward message to window class handler
	return pWnd->WindowProc(hwnd, msg, wPara, lPara);
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
		wc.lpfnWndProc = ProcessMessageSetup;
		RegisterClassEx(&wc);
	}

	HWND glitc::WindowCreation::GetWindowHandle()
	{
		return this->windowHandle;
	}

	glitc::MouseClass* glitc::WindowCreation::GetMouseClassRef()
	{
		return mc;
	}

	bool glitc::WindowCreation::Run()
	{
		// running the application
		MSG msg = { 0 };
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		
		if (msg.message == WM_QUIT)
		{
			UnregisterClass(className.c_str(), applicationInstance);
			return false;
		}
		
		return true;
	}