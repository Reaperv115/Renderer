#include "trpch.h"
#include "Engine.h"

bool Rhine::Engine::InitEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height)
{
	if (!windowCreation.InitializeWindow(hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to initialize window");
		return false;
	}
	if (!gfx.InitializeDirectX(width, height, windowCreation))
	{
		ErrorLogger::Log("Failed to initialize graphics");
		return false;
	}
}

void Rhine::Engine::Run()
{
	windowCreation.Run();
}
