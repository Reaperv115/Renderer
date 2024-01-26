#include "trpch.h"
#include "KeyboardEvent.h"

glitc::KeyboardEvent::KeyboardEvent()
	: type(EventType::Invalid), key(0u)
{

}

glitc::KeyboardEvent::KeyboardEvent(EventType type, const unsigned char key)
	: type(EventType::Invalid), key(0u)
{

}

bool glitc::KeyboardEvent::IsPress() const
{
	return this->type == EventType::Press;
}

bool glitc::KeyboardEvent::IsRelease() const
{
	return this->type == EventType::Release;
}

bool glitc::KeyboardEvent::IsValid() const
{
	return this->type != EventType::Invalid;
}

unsigned char glitc::KeyboardEvent::GetKeyCode() const
{
	return this->key;
}
