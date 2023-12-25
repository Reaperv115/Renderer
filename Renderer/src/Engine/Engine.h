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
		double time = 0.0;
		double deltaTime = 0;
		std::chrono::steady_clock::time_point lastUpdate;
		unsigned int frameTime = 0;
		long diff;
	private:
		WindowCreation windowCreation;
		Graphics gfx;
		
	};
}

