#include "trpch.h"
#include "WindowCreation.h"
#include "D3DApplication.h"


glitc::WindowCreation::WindowCreation()
	: windowHandle(nullptr), applicationInstance(nullptr),
	  className(L"Engine"), windowName(L"Engine"),
	  xPosition(300), yPosition(100)
{

}


bool glitc::WindowCreation::InitializeWindow(D3DApplication* d3dApp, HINSTANCE inst, std::string className, std::string windowName, int width, int height)
	{
		// creating console window to debug
		this->CreateDebugConsoleWindow();

		// catching instance to application
		this->applicationInstance = inst;

		// naming the window class and window itself
		this->className = glitc::StringConverter::StringtoWideString(className);
		this->windowName = glitc::StringConverter::StringtoWideString(windowName);

		// registering window class
		this->RegisterWindowClass();

		// creating render window
		this->windowHandle = CreateWindowEx(0, 
			this->className.c_str(), 
			this->windowName.c_str(), 
			WS_OVERLAPPEDWINDOW, 
			this->xPosition,
			this->yPosition,
			width,
			height,
			NULL,
			NULL,
			this->applicationInstance,
			d3dApp);

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
		wc.lpszClassName = this->className.c_str();
		wc.lpszMenuName = this->windowName.c_str();
		wc.hInstance = this->applicationInstance;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.lpfnWndProc = HandleMessageSetup;
		RegisterClassEx(&wc);
	}

	HWND glitc::WindowCreation::GetWindowHandle() const
	{
		return this->windowHandle;
	}

	glitc::MouseClass* glitc::WindowCreation::GetMouseClassRef() const
	{
		return this->mouse;
	}

	glitc::KeyboardClass* glitc::WindowCreation::GetKeyboardClassRef() const
	{
		return this->keyboard;
	}

	HINSTANCE glitc::WindowCreation::GetApplicationInstance() const
	{
		return this->applicationInstance;
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
			UnregisterClass(this->className.c_str(), this->applicationInstance);
			return false;
		}
		
		return true;
	}

	// windows message processing functions
	// WindowProc will handle input from mouse and keyboard
	LRESULT CALLBACK glitc::WindowCreation::HandleMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara)
	{
		// use create parameter passed in from CreateWindow() to store window class pointer at WinAPI side
		if (msg == WM_NCCREATE)
		{
			// extract ptr to window from class from creation data
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lPara);
			D3DApplication* const pWnd = reinterpret_cast<D3DApplication*>(pCreate->lpCreateParams);
			//sanity check
			assert(pWnd != nullptr);
			// set WinAPI-managed user data to store ptr to window class
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
			// set message proc to normal handler now that setup is finished
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(_HandleMessageRedirect));
			// forward message to window class handler
			return pWnd->WindowProc(hwnd, msg, wPara, lPara);
		}
		// if we get a message before the WM_NCCREATE message, handle with default handler
		return DefWindowProc(hwnd, msg, wPara, lPara);
	}
	LRESULT CALLBACK glitc::WindowCreation::_HandleMessageRedirect(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara)
	{
		// retrieve ptr to window class
		D3DApplication* const pWnd = reinterpret_cast<D3DApplication*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
		// forward message to window class handler
		return pWnd->WindowProc(hwnd, msg, wPara, lPara);
	}