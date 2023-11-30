#include "trpch.h"
#include "Utilities/ErrorLogger.h"
#include "Engine/Engine.h"



int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPTSTR lpCmdLine, int nCmdShow)
{

	Rhine::Engine engine;
	engine.InitEngine(hInstance, "Engine", "Engine", 800, 600);
	engine.Run();

	return 0;
}