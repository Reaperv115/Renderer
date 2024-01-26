#pragma once
#include "MouseEvent.h"

namespace glitc
{
	class MouseClass
	{
	public:
		void OnLeftButtonPressed(int x, int y);
		void OnLeftButtonReleased(int x, int y);
		void OnRightButtonPressed(int x, int y);
		void OnRightButtonReleased(int x, int y);
		void OnMiddleButtonPressed(int x, int y);
		void OnMiddleButtonReleased(int x, int y);
		void OnWheelUp(int x, int y);
		void OnWheelDown(int x, int y);
		void OnMouseMove(int x, int y);
		void OnMouseMoveRaw(int x, int y);
		bool IsLeftButtonDown(int x, int y);
		bool IsRightButtonDown(int x, int y);
		int GetXPos() const;
		int GetYPos() const;
		MousePoint GetPos() const;

		bool EventBufferisEmpty();
		MouseEvent ReadEvent();
	private:
		std::queue<MouseEvent> eventBuffer;
		bool isleftPressed, isrightPressed, ismPressed;
		int x, y;
	};
}

