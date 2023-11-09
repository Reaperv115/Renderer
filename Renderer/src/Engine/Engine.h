#pragma once
#include "../WindowCreation/WindowCreation.h"
#include "../Graphics/Graphics.h"

namespace Rhine
{
	class Engine
	{
	public:
		bool InitEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height);
		void Run();
	private:
		WindowCreation windowCreation;
		Graphics gfx;
	};
}

