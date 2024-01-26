#include "trpch.h"
#include "KeyboardClass.h"

glitc::KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++)
		this->keyStates[i] = false;
}

bool glitc::KeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool glitc::KeyboardClass::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();
}

bool glitc::KeyboardClass::CharBufferIsEmpty()
{
	return this->charBuffer.empty();
}

glitc::KeyboardEvent glitc::KeyboardClass::ReadKey()
{
	if (this->keyBuffer.empty())
	{
		return KeyboardEvent();
	}
	else
	{
		KeyboardEvent kbe = this->keyBuffer.front();
		this->keyBuffer.pop();
		return kbe;
	}
}

unsigned char glitc::KeyboardClass::ReadChar()
{
	if (this->charBuffer.empty())
	{
		return 0u;
	}
	else
	{
		unsigned char e = this->charBuffer.front();
		this->charBuffer.pop();
		return e;
	}

}

void glitc::KeyboardClass::OnKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void glitc::KeyboardClass::OnKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void glitc::KeyboardClass::OnChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

void glitc::KeyboardClass::EnableAutorepeatKeys()
{
	this->autorepeatKeys = true;
}

void glitc::KeyboardClass::DisableAutoRepeatKeys()
{
	this->autorepeatKeys = false;
}

void glitc::KeyboardClass::EnableAutorepeatChars()
{
	this->autorepeatChars = true;
}

void glitc::KeyboardClass::DisableAutoRepeatChars()
{
	this->autorepeatChars = false;
}

bool glitc::KeyboardClass::IsKeysAutoRepeats()
{
	return this->autorepeatKeys;
}

bool glitc::KeyboardClass::IsCharsAutoRepeats()
{
	return this->autorepeatChars;
}
