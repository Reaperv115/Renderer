#include "trpch.h"
#include "Engine.h"

bool Rhine::Engine::InitEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height)
{
	// initialize rendering window
	if (!windowCreation.InitializeWindow(hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to initialize window");
		return false;
	}

	// initialize graphics API
	if (!gfx.InitializeDirectX(width, height, windowCreation.GetWindowHandle()))
	{
		ErrorLogger::Log("Failed to initialize graphics");
		return false;
	}
	
	return true;
}

void Rhine::Engine::Run()
{
	gfx.InitializeScene();

	// run the application
	while (windowCreation.Run())
	{
		gfx.Render();
	}
}
