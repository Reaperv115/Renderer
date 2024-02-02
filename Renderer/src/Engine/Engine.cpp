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
	if (!this->InitializeRenderWindow(hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to Initialize Engine");
		return false;
	}

	// initialize graphics API
	if (!this->InitializeGraphicsAPI(width, height, this->windowCreation->GetWindowHandle()))
	{
		ErrorLogger::Log("Failed to initialize graphics");
		return false;
	}
	
	return true;
}

void glitc::Engine::Update()
{
	
	while (!keyboard->CharBufferIsEmpty())
	{
		keyStroke = keyboard->ReadChar();
		std::string outmsg = "Char: ";
		outmsg += keyStroke;
		outmsg += '\n';
		std::cout << outmsg;
	}
	while (!keyboard->KeyBufferIsEmpty())
	{
		KeyboardEvent kbe = keyboard->ReadKey();
		unsigned char keycode = kbe.GetKeyCode();
		std::string outmsg = "Key: ";
		outmsg += keycode;
		outmsg += '\n';
		std::cout << outmsg;
	}

	// processing window event buffer for mouse
	while (!mouse->EventBufferisEmpty())
	{
		MouseEvent me = mouse->ReadEvent();
		std::string msg = "X: ";
		msg += std::to_string(me.GetPosX());
		msg += " ";
		msg += "Y: ";
		msg += std::to_string(me.GetPosY());
		std::cout << msg << std::endl;
	}

	// camera movement
	if (this->keyboard->KeyIsPressed('W'))
	{
		std::cout << "moving forwards" << std::endl;
		this->gfx->camera.AdjustPosition(this->gfx->camera.GetForwardVector() * this->timer.SmoothDelta() * cameraspeed);
	}
	if (keyboard->KeyIsPressed('A'))
	{
		std::cout << "moving left" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetLeftVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (keyboard->KeyIsPressed('S'))
	{
		std::cout << "moving backwards" << std::endl;
		gfx->camera.AdjustPosition(gfx->camera.GetBackwardsVector() * timer.SmoothDelta() * cameraspeed);
	}
	if (keyboard->KeyIsPressed('D'))
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
