#pragma once
#include "StringConverter.h"
namespace Rhine
{
	class ErrorLogger
	{
	public:
		static void Log(std::string message);
		static void Log(HRESULT hr, std::string message);
	};
}

