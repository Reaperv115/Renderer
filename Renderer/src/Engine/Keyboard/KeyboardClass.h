#pragma once
#include "KeyboardEvent.h"

namespace glitc
{
	class KeyboardClass
	{
	public:
		KeyboardClass();
		bool KeyIsPressed(const unsigned char keycode);
		bool KeyBufferIsEmpty();
		bool CharBufferIsEmpty();
		KeyboardEvent ReadKey();
		unsigned char ReadChar();
		void OnKeyPressed(const unsigned char key);
		void OnKeyReleased(const unsigned char key);
		void OnChar(const unsigned char key);
		void EnableAutorepeatKeys();
		void DisableAutoRepeatKeys();
		void EnableAutorepeatChars();
		void DisableAutoRepeatChars();
		bool IsKeysAutoRepeats();
		bool IsCharsAutoRepeats();
	private:
		bool autorepeatKeys = false;
		bool autorepeatChars = false;
		bool keyStates[256];
		std::queue<KeyboardEvent> keyBuffer;
		std::queue<unsigned char> charBuffer;
	};
}

