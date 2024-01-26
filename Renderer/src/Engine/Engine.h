#pragma once
#include "../WindowCreation/D3DApplication.h"
#include "../Graphics/Graphics.h"
#include "XTime.h"

namespace glitc
{
	class Engine : public D3DApplication
	{
	public:
		bool InitializeEngine(HINSTANCE hInst, std::string className, std::string windowName, int width, int height);
		void Update();
		void Run();
	private:
		XTime timer;
	private:
		float cameraspeed = 5.0f;
	};
}

