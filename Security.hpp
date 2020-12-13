#pragma once

#include <string>

class Security
{
	public:
		static bool CompareSignatures(std::string body,std::string key, std::string receive);
	private:
		static std::string GetHMAC(std::string key, std::string message);
		static int TimingSafeEqual(const void* a, const void* b, const size_t size);
};