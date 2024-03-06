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

	double width = 800.0f;
	double height = 600.0f;
	glitc::Engine* engine = new glitc::Engine();
	engine->InitializeEngine(hInstance, "Engine", "Engine", width, height);
	engine->Run();
	delete engine;

	return 0;
}