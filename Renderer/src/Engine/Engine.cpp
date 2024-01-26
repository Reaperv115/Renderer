#include "trpch.h"
#include "Engine.h"

bool glitc::Engine::InitializeEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height)
{
	// initialize render window
	if (!InitializeRenderWindow(hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to Initialize Engine");
		return false;
	}

	// initialize graphics API
	if (!InitializeGraphicsAPI(width, height, windowCreation->GetWindowHandle()))
	{
		ErrorLogger::Log("Failed to initialize graphics");
		return false;
	}
	
	return true;
}

void glitc::Engine::Update()
{
	// camera movement
	if (GetAsyncKeyState(0x57))
	{
		std::cout << "moving forwards" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetForwardVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (GetAsyncKeyState(0x53))
	{
		std::cout << "moving backwards" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetBackwardsVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (GetAsyncKeyState(0x41))
	{
		std::cout << "moving to the left" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetLeftVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (GetAsyncKeyState(0x44))
	{
		std::cout << "moving to the right" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetRightVector() * timer.SmoothDelta() * cameraspeed);
	}

	while (!windowCreation->GetKeyboardClassRef()->CharBufferIsEmpty())
	{
		unsigned char ch = windowCreation->GetKeyboardClassRef()->ReadChar();
		std::string outmsg = "Char: ";
		outmsg += ch;
		outmsg += '\n';
		std::cout << outmsg;
	}

	// extracting and printing mouse position
	while (!windowCreation->GetMouseClassRef()->EventBufferisEmpty())
	{
		MouseEvent me = windowCreation->GetMouseClassRef()->ReadEvent();
		std::string msg = "X: ";
		msg += std::to_string(me.GetPosX());
		msg += " ";
		msg += "Y: ";
		msg += std::to_string(me.GetPosY());
		std::cout << msg << std::endl;
	}
}

void glitc::Engine::Run()
{
	gfx->InitializeScene();

	// run the application
	while (windowCreation->Run())
	{
		timer.Signal();
		Update();
		gfx->Render();
	}
}
