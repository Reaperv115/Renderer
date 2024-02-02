#include "trpch.h"
#include "MouseClass.h"

void glitc::MouseClass::OnLeftButtonPressed(int x, int y)
{
	this->isleftPressed = true;
	MouseEvent me(MouseEvent::EventType::LPress, x, y);
	this->eventBuffer.push(me); 
}

void glitc::MouseClass::OnLeftButtonReleased(int x, int y)
{
	this->isleftPressed = false;
	MouseEvent me(MouseEvent::EventType::LRelease, x, y);
	this->eventBuffer.push(me);
}

void glitc::MouseClass::OnRightButtonPressed(int x, int y)
{
	this->isrightPressed = true;
	MouseEvent me(MouseEvent::EventType::RPress, x, y);
	this->eventBuffer.push(me);
}

void glitc::MouseClass::OnRightButtonReleased(int x, int y)
{
	this->isrightPressed = false;
	MouseEvent me(MouseEvent::EventType::RRelease, x, y);
	this->eventBuffer.push(me);
}

void glitc::MouseClass::OnMiddleButtonPressed(int x, int y)
{
	this->ismPressed = true;
	MouseEvent me(MouseEvent::EventType::MPress, x, y);
	this->eventBuffer.push(me);
}

void glitc::MouseClass::OnMiddleButtonReleased(int x, int y)
{
	this->ismPressed = false;
	MouseEvent me(MouseEvent::EventType::MRelease, x, y);
	this->eventBuffer.push(me);
}

void glitc::MouseClass::OnWheelUp(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelUp, x, y));
}

void glitc::MouseClass::OnWheelDown(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::WheelDown, x, y));
}

void glitc::MouseClass::OnMouseMove(int x, int y)
{
	this->x = x;
	this->y = y;
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::Move, x, y));
}

void glitc::MouseClass::OnMouseMoveRaw(int x, int y)
{
	this->eventBuffer.push(MouseEvent(MouseEvent::EventType::RAW_MOVE, x, y));
}

bool glitc::MouseClass::IsLeftButtonDown(int x, int y)
{
	return this->isleftPressed;
}

bool glitc::MouseClass::IsRightButtonDown(int x, int y)
{
	return this->isrightPressed;
}

int glitc::MouseClass::GetXPos() const
{
	return this->x;
}

int glitc::MouseClass::GetYPos() const
{
	return this->y;
}

glitc::MousePoint glitc::MouseClass::GetPos() const
{
	return { this->x, this->y };
}

bool glitc::MouseClass::EventBufferisEmpty()
{
	return this->eventBuffer.empty();
}

glitc::MouseEvent glitc::MouseClass::ReadEvent()
{
	if (this->eventBuffer.empty())
	{
		return MouseEvent();
	}
	else
	{
		MouseEvent me = eventBuffer.front();
		this->eventBuffer.pop();
		return me;
	}
}
