#include "trpch.h"
#include "MouseEvent.h"


glitc::MouseEvent::MouseEvent(EventType type, int x, int y)
	: type(type),
	  x(x), y(y)
{

}

glitc::MouseEvent::MouseEvent()
    : type(EventType::Invalid),
      x(0), y(0)
{

}

glitc::MousePoint glitc::MouseEvent::GetPos() const
{
	return { this->x, this->y };
}

bool glitc::MouseEvent::IsValid() const
{
	return this->type != EventType::Invalid;
}

glitc::MouseEvent::EventType glitc::MouseEvent::GetType() const
{
	return this->type;
}

int glitc::MouseEvent::GetPosX() const
{
	return this->x;
}

int glitc::MouseEvent::GetPosY() const
{
	return this->y;
}
