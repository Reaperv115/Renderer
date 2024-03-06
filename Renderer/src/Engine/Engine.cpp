#include "trpch.h"
#include "Engine.h"

glitc::Engine::Engine()
	: keyStroke(0u),
	  cameraspeed(0.2f)
{

}

bool glitc::Engine::InitializeEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height)
{
	// initialize render window
	if (!windowCreation.InitializeWindow(this, hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to Initialize Engine");
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

void glitc::Engine::Update()
{
	// keyboard events
	while (!keyboard.CharBufferIsEmpty())
	{
		keyStroke = keyboard.ReadChar();
	}
	while (!keyboard.KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard.ReadKey();
		keyStroke = kbe.GetKeyCode();
	}

	// processing window event buffer for mouse
	while (!mouse.EventBufferisEmpty())
	{
		MouseEvent me = mouse.ReadEvent();
		if (me.GetType() == MouseEvent::EventType::RAW_MOVE)
		{
			if (mouse.IsRightButtonDown())
			{
				gfx.camera.AdjustRotation((float)me.GetPosY() * 0.01f, (float)me.GetPosX() * 0.01f, 0);
			}
		}
	}

	// camera movement
	if (keyboard.KeyIsPressed('W'))
	{
		std::cout << "moving forwards" << std::endl;
		gfx.camera.AdjustPosition(gfx.camera.GetForwardVector() * timer.SmoothDelta() * (double)cameraspeed);
	}
	if (keyboard.KeyIsPressed('A'))
	{
		std::cout << "moving Left" << std::endl;
		gfx.camera.AdjustPosition(gfx.camera.GetLeftVector() * timer.SmoothDelta() * (double)cameraspeed);
	}
	if (keyboard.KeyIsPressed('S'))
	{
		std::cout << "moving backwards" << std::endl;
		gfx.camera.AdjustPosition(gfx.camera.GetBackwardsVector() * timer.SmoothDelta() * (double)cameraspeed);
	}
	if (keyboard.KeyIsPressed('D'))
	{
		std::cout << "moving right" << std::endl;
		gfx.camera.AdjustPosition(gfx.camera.GetRightVector() * timer.SmoothDelta() * (double)cameraspeed);
	}

	if (keyboard.KeyIsPressed('R'))
	{
		gfx.camera.ResetCamera();
	}

	// "sprinting"
	if (GetAsyncKeyState(VK_SHIFT))
		cameraspeed = 10.0;
	else
		cameraspeed = 5.0;
}

void glitc::Engine::Run()
{
	gfx.InitializeScene();

	// run the application
	while (windowCreation.Run())
	{
		timer.Signal();
		Update();
		gfx.Render();
	}
}
