#include "trpch.h"
#include "D3DApplication.h"



glitc::D3DApplication::D3DApplication()
{

}

bool glitc::D3DApplication::InitializeGraphicsAPI(float width, float height, HWND handle)
{
	if (!gfx->InitializeDirectX(width, height, handle))
	{
		ErrorLogger::Log("Failed to Initialize Graphics API");
		return false;
	}
	return true;
}

bool glitc::D3DApplication::InitializeRenderWindow(HINSTANCE hInst, std::string className, std::string windowName, float width, float height)
{
	if (!windowCreation->InitializeWindow(hInst, className, windowName, width, height))
	{
		ErrorLogger::Log("Failed to Initialize Render Window");
		return false;
	}
	return true;
}