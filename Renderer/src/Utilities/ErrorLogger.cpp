#include "trpch.h"
#include "ErrorLogger.h"

namespace glitc
{
	void ErrorLogger::Log(std::string message)
	{
		std::string error_msg = "Error: " + message;
		MessageBoxA(NULL, error_msg.c_str(), "Error", MB_ICONERROR);
	}
	void ErrorLogger::Log(HRESULT hr, std::string message)
	{
		std::wstring error_message = L"Error: " + hr + StringConverter::StringtoWideString(message) +
			L"\n";
		MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
	}

}
