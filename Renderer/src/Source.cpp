#include "trpch.h"

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, int nCmdShow)
{
	HINSTANCE hInst;
	HWND hwnd;

	int width = 1920;
	int height = 1080;

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
		std::cout << "failed to create handle" << std::endl;
	ShowWindow(hwnd, SW_SHOW);

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, Msg, wParam, lParam);
}