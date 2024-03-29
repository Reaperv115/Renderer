#include "trpch.h"
#include "WindowCreation.h"
#include "D3DApplication.h"


glitc::WindowCreation::WindowCreation()
	: applicationInstance(nullptr), windowHandle(nullptr),
	  className(L"Engine"), windowName(L"Engine"),
	  xPosition(300), yPosition(100)
{
	
}


glitc::WindowCreation::~WindowCreation()
{
	if (this->windowHandle != NULL)
	{
		UnregisterClass(this->className.c_str(), this->applicationInstance);
		DestroyWindow(windowHandle);
	}
}

bool glitc::WindowCreation::InitializeWindow(D3DApplication* application, HINSTANCE inst, std::string className, std::string windowName, int width, int height)
{

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
			application);

		

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
			SetFocus(this->windowHandle);
		}
		return true;
}

	







	void glitc::WindowCreation::RegisterWindowClass()
	{
		WNDCLASSEX wc;
		ZeroMemory(&wc, sizeof(WNDCLASSEX));
		wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
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
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		
		if (msg.message == WM_NULL)
		{
			if (!IsWindow(this->windowHandle))
			{
				this->windowHandle = NULL;
				UnregisterClass(this->className.c_str(), this->applicationInstance);
				return false;
			}
		}
		
		return true;
	}

	// windows message processing functions
	// WindowProc will handle input from mouse and keyboard
	LRESULT CALLBACK glitc::WindowCreation::HandleMessageSetup(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara)
	{
		switch (msg)
		{
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lPara);
			D3DApplication* pWindow = reinterpret_cast<D3DApplication*>(pCreate->lpCreateParams);
			if (pWindow == nullptr) //Sanity check
			{
				ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
				exit(-1);
			}
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMessageRedirect));
			return pWindow->WindowProc(hwnd, msg, wPara, lPara);
		}
		default:
		    // if we get a message before the WM_NCCREATE message, handle with default handler
		    return DefWindowProc(hwnd, msg, wPara, lPara);
		}
	}
	LRESULT CALLBACK glitc::WindowCreation::HandleMessageRedirect(HWND hwnd, UINT msg, WPARAM wPara, LPARAM lPara)
	{
		switch (msg)
		{
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		default:
		{
			// retrieve ptr to window class
			D3DApplication* pWnd = reinterpret_cast<D3DApplication*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			// forward message to window class handler
			return pWnd->WindowProc(hwnd, msg, wPara, lPara); 
		}
		}
		
	}
