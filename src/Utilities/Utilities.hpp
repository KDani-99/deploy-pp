#pragma once
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cpprest/containerstream.h>    

#include <boost/uuid/uuid.hpp> 
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>

using namespace utility;

class Utilities
{
	public:
		static std::string GetProjectName(std::string fullPath);
		static string_t ToString_T(std::string input);
		static string_t ToString_T(unsigned short input);
		static std::string GenerateUUID();
		static int GetCurrentTimestamp();
};