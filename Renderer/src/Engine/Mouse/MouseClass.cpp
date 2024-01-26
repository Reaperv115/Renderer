#include "trpch.h"
#include "MouseClass.h"

void glitc::MouseClass::OnLeftButtonPressed(int x, int y)
{
	isleftPressed = true;
	MouseEvent me(MouseEvent::EventType::LPress, x, y);
	eventBuffer.push(me); 
}

void glitc::MouseClass::OnLeftButtonReleased(int x, int y)
{
	isleftPressed = false;
	MouseEvent me(MouseEvent::EventType::LRelease, x, y);
	eventBuffer.push(me);
}

void glitc::MouseClass::OnRightButtonPressed(int x, int y)
{
	isrightPressed = true;
	MouseEvent me(MouseEvent::EventType::RPress, x, y);
	eventBuffer.push(me);
}

void glitc::MouseClass::OnRightButtonReleased(int x, int y)
{
	isrightPressed = false;
	MouseEvent me(MouseEvent::EventType::RRelease, x, y);
	eventBuffer.push(me);
}

void glitc::MouseClass::OnMiddleButtonPressed(int x, int y)
{
	ismPressed = true;
	MouseEvent me(MouseEvent::EventType::MPress, x, y);
	eventBuffer.push(me);
}

void glitc::MouseClass::OnMiddleButtonReleased(int x, int y)
{
	ismPressed = false;
	MouseEvent me(MouseEvent::EventType::MRelease, x, y);
	eventBuffer.push(me);
}

void glitc::MouseClass::OnWheelUp(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void glitc::MouseClass::OnWheelDown(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void glitc::MouseClass::OnMouseMove(int x, int y)
{
	eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
}

bool glitc::MouseClass::EventBufferisEmpty()
{
	return eventBuffer.empty();
}

glitc::MouseEvent glitc::MouseClass::ReadEvent()
{
	if (eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent me = eventBuffer.front();
		eventBuffer.pop();
		return me;
	}
}
