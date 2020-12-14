#pragma once
#include <string>
#include <stdlib.h>
#include <cpprest/containerstream.h>    

using namespace utility;

class Utilities
{
	public:
		static std::string GetProjectName(std::string fullPath);
		static string_t ToString_T(std::string input);
		static string_t ToString_T(unsigned short input);
};