#pragma once
#include "StringConverter.h"
namespace glitc
{
	class ErrorLogger
	{
	public:
		static void Log(std::string message);
		static void Log(HRESULT hr, std::string message);
	};

	class DebugLogger
	{
	public:
		static void Log(std::wstring debugmessage);
	};
}

