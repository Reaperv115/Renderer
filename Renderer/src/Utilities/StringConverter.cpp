#include "trpch.h"
#include "StringConverter.h"
namespace glitc
{
	std::wstring StringConverter::StringtoWideString(std::string str)
	{
		std::wstring wide_string(str.begin(), str.end());
		return wide_string;
	}
}
