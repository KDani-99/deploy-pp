#include "Utilities.hpp"

std::string Utilities::GetProjectName(std::string fullPath)
{
	size_t x = fullPath.find_last_of("/");

	return fullPath.substr(x + 1, fullPath.length() - x);
}
string_t Utilities::ToString_T(std::string input)
{
	std::wstring result(input.length(), L' '); 

	std::copy(input.begin(), input.end(), result.begin());

	return result;
}
string_t Utilities::ToString_T(unsigned short input)
{
	return ToString_T(std::to_string(input));
}
std::string Utilities::GenerateUUID()
{
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	return boost::lexical_cast<std::string>(uuid);
}
int Utilities::GetCurrentTimestamp()
{
	return time(NULL);
}