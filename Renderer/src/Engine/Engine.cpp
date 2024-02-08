#include "trpch.h"
#include "Engine.h"

glitc::Engine::Engine()
	: keyStroke(0u),
	  cameraspeed(0.02f)
{

}

bool glitc::Engine::InitializeEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height)
{
	// initialize render window
	if (!this->windowCreation->InitializeWindow(this, hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to Initialize Engine");
		return false;
	}

	// initialize graphics API
	if (!this->gfx->InitializeDirectX(width, height, windowCreation->GetWindowHandle()))
	{
		ErrorLogger::Log("Failed to initialize graphics");
		return false;
	}
	
	return true;
}

void glitc::Engine::Update()
{
	// keyboard events
	while (!keyboard->CharBufferIsEmpty())
	{
		keyStroke = keyboard->ReadChar();
	}
	while (!keyboard->KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard->ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
	}

	// processing window event buffer for mouse
	while (!mouse->EventBufferisEmpty())
	{
		MouseEvent me = mouse->ReadEvent();
	}

	 //camera movement
	if (GetAsyncKeyState(0x57))
	{
		std::cout << "moving forwards" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetForwardVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (GetAsyncKeyState(0x44))
	{
		std::cout << "moving left" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetLeftVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (GetAsyncKeyState(0x53))
	{
		std::cout << "moving backwards" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetBackwardsVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (GetAsyncKeyState(0x41))
	{
		std::cout << "moving right" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetRightVector() * timer.SmoothDelta() * cameraspeed);
	}
}

void glitc::Engine::Run()
{
	this->gfx->InitializeScene();

	// run the application
	while (this->windowCreation->Run())
	{
		this->timer.Signal();
		this->Update();
		this->gfx->Render();
	}
}
