#include "trpch.h"
#include "Utilities/ErrorLogger.h"
#include "Engine/Engine.h"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		Rhine::ErrorLogger::Log(hr, "Failed to successfully call coinitialize");
		return -1;
	}


	Rhine::Engine engine;
	engine.InitEngine(hInstance, "Engine", "Engine", 800, 600);
	engine.Run();

	return 0;
}