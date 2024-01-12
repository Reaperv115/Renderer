#pragma once
#include "../WindowCreation/WindowCreation.h"
#include "../Graphics/Graphics.h"
#include "XTime.h"

namespace glitc
{
	class Engine
	{
	public:
		bool InitEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height);
		void Run();
	private:
		WindowCreation windowCreation;
		Graphics gfx;
		XTime timer;
	private:
		float cameraspeed = 5.0f;
	};
}

