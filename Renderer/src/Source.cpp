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

	float width = 800.0f;
	float height = 600.0f;
	glitc::Engine engine;
	engine.InitializeEngine(hInstance, "Engine", "Engine", width, height);
	engine.Run();

	return 0;
}