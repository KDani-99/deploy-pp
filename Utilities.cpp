#include "Utilities.hpp"

std::string Utilities::GetProjectName(std::string fullPath)
{
	size_t x = fullPath.find_last_of("/");

	return fullPath.substr(x + 1, fullPath.length() - x);
}