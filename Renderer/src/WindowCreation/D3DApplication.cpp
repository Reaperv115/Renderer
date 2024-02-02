#include "trpch.h"
#include "D3DApplication.h"



glitc::D3DApplication::D3DApplication()
	: windowCreation(new WindowCreation()),
	  keyboard(new KeyboardClass()),
	  mouse(new MouseClass()),
	  gfx(new Graphics()),
	  fWidth(600.0f),
	  fHeight(800.0f)
{
	static bool rawinputInitialized = false;
	if (rawinputInitialized == false)
	{
		RAWINPUTDEVICE riD;
		riD.usUsagePage = 0x01; // mouse
		riD.usUsage = 0x02;
		riD.dwFlags = 0;
		riD.hwndTarget = NULL;

		if (RegisterRawInputDevices(&riD, 1, sizeof(riD)) == FALSE)
		{
			ErrorLogger::Log(GetLastError(), "Failed to register raw input device");
			exit(-1);
		}

		rawinputInitialized = true;
	}
}

LRESULT CALLBACK glitc::D3DApplication::WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
		// keyboard messages
	case WM_KEYDOWN:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		if (keyboard->IsKeysAutoRepeats())
		{
			keyboard->OnKeyPressed(keycode);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				keyboard->OnKeyPressed(keycode);
			}
		}
		break;
	}
	case WM_KEYUP:
	{
		unsigned char keycode = static_cast<unsigned char>(wParam);
		keyboard->OnKeyReleased(keycode);
		break;
	}
	case WM_CHAR:
	{
		unsigned char ch = static_cast<unsigned char>(wParam);
		if (keyboard->IsCharsAutoRepeats())
		{
			keyboard->OnChar(ch);
		}
		else
		{
			const bool wasPressed = lParam & 0x40000000;
			if (!wasPressed)
			{
				keyboard->OnChar(ch);
			}
		}
		break;
	}
	// mouse messages
	case WM_MOUSEMOVE:
	{
		int x = GET_X_LPARAM(lParam);
		int y = GET_Y_LPARAM(lParam);
		mouse->OnMouseMove(x, y);
		break;
	}
	case WM_INPUT:
	{
		UINT dataSize = 0;
		GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, NULL, &dataSize, sizeof(RAWINPUTHEADER));

		if (dataSize > 0)
		{
			std::unique_ptr<BYTE[]> rawdata = std::make_unique<BYTE[]>(dataSize);
			if (GetRawInputData(reinterpret_cast<HRAWINPUT>(lParam), RID_INPUT, rawdata.get(), &dataSize, sizeof(RAWINPUTHEADER)) == dataSize)
			{
				RAWINPUT* raw = reinterpret_cast<RAWINPUT*>(rawdata.get());
				if (raw->header.dwType == RIM_TYPEMOUSE)
				{
					mouse->OnMouseMoveRaw(raw->data.mouse.lLastX, raw->data.mouse.lLastY);
				}
			}
		}
		return DefWindowProc(hwnd, Msg, wParam, lParam);
	}
	// other messages
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	}
	return DefWindowProc(hwnd, Msg, wParam, lParam);
}

bool glitc::D3DApplication::InitializeGraphicsAPI(float width, float height, HWND handle)
{
	if (!this->gfx->InitializeDirectX(width, height, handle))
	{
		ErrorLogger::Log("Failed to Initialize Graphics API");
		return false;
	}
	return true;
}

bool glitc::D3DApplication::InitializeRenderWindow(HINSTANCE hInst, std::string className, std::string windowName, float width, float height)
{
	if (!this->windowCreation->InitializeWindow(this, hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to Initialize Render Window");
		return false;
	}
	return true;
}