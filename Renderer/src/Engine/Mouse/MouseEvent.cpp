#include "trpch.h"
#include "MouseEvent.h"


glitc::MouseEvent::MouseEvent(EventType type, int x, int y)
	: type(type), x(x), y(y)
{

}

glitc::MouseEvent::MouseEvent()
{

}

glitc::MousePoint glitc::MouseEvent::GetPos() const
{
	return { x, y };
}

int glitc::MouseEvent::GetPosX() const
{
	return x;
}

int glitc::MouseEvent::GetPosY() const
{
	return y;
}
