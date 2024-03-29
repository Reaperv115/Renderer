#pragma once
#include "../WindowCreation/D3DApplication.h"
#include "Camera.h"
#include "XTime.h"

namespace glitc
{
	class Engine : public D3DApplication
	{
	public:
		Engine();
		bool InitializeEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height);
		void Update();
		void Run();
	private:
		XTime timer;
		Camera camera;
		unsigned char keyStroke;
	private:
		double cameraspeed = 5.0;
	};
}

