#include "trpch.h"
#include "ErrorLogger.h"

namespace Rhine
{
	void ErrorLogger::Log(std::string message)
	{
		std::string error_msg = "Error: " + message;
		MessageBoxA(NULL, error_msg.c_str(), "Error", MB_ICONERROR);
	}
	void ErrorLogger::Log(HRESULT hr, std::string message)
	{
		std::wstring error_message = L"Error: " + StringConverter::StringtoWideString(message) +
			L"\n";
		MessageBoxW(NULL, error_message.c_str(), L"Error", MB_ICONERROR);
	}

	void ErrorLogger::Log(HRESULT hr, std::wstring message)
	{
		MessageBoxW(NULL, message.c_str(), L"Error", MB_ICONERROR);
	}

}
