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
		clock_t GetDeltaTtime() const;
	private:
		double clocktoMilliseconds(clock_t ticks);
	private:
		clock_t deltaTime = 0;
		unsigned int frames = 0;
		double frameRate = 30;
		double averageframetimeMilliseconds = 33.333;
		std::wstring mainwndCaption;
	private:
		WindowCreation windowCreation;
		Graphics gfx;
		
	};
}

