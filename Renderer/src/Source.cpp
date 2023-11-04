#include "trpch.h"
#include "Utilities/ErrorLogger.h"

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;
	HWND hwnd;

	int width = 1000;
	int height = 800;

	AllocConsole();
	auto obj = freopen("CONIN$", "r", stdin);
	auto obj2 = freopen("CONOUT$", "w", stdout);
	auto obj3 = freopen("CONOUT$", "w", stderr);

	hInst = hInstance;
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.lpszClassName = L"Renderer";
	wc.lpszMenuName = L"Renderer";
	wc.hInstance = hInst;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = WindowProcedure;
	RegisterClassEx(&wc);

	hwnd = CreateWindowEx(0, L"Renderer", L"Renderer", WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, hInst, NULL);
	if (hwnd == NULL)
		Rhine::ErrorLogger::Log("Failed to create window handle");
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	MSG msg = { 0 };
	
#pragma region application loops
	/*while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}*/
	
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
#pragma endregion working app loops using both GetMessage and PeekMessage

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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