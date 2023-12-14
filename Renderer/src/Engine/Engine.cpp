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
		clock_t beginFrame = clock();
		gfx.Render();
		clock_t endFrame = clock();

		deltaTime += endFrame - beginFrame;
		frames++;

		if (clocktoMilliseconds(deltaTime) > 1000.0)
		{
			frameRate = (double)frames * 0.5 + frameRate * 0.5;
			frames = 0;
			deltaTime -= CLOCKS_PER_SEC;
			averageframetimeMilliseconds = 1000.0 / (frameRate == 0 ? 0.001 : frameRate);
		}

		std::wostringstream outs;
		outs.precision(6);
		outs << mainwndCaption << L" "
			<< L"FPS: " << averageframetimeMilliseconds;
		SetWindowText(windowCreation.GetWindowHandle(), outs.str().c_str());
	}
}

double Rhine::Engine::clocktoMilliseconds(clock_t ticks)
{
	return (ticks / (double)CLOCKS_PER_SEC) * 1000.0;
}
