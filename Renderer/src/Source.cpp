#include "trpch.h"
#include "Utilities/ErrorLogger.h"
#include "Engine/Engine.h"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		glitc::ErrorLogger::Log(hr, "Failed to successfully call coinitialize");
		return -1;
	}


	glitc::Engine engine;
	engine.InitEngine(hInstance, "Engine", "Engine", 800.0f, 600.0f);
	engine.Run();

	return 0;
}