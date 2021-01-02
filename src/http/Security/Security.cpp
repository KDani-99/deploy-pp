#include "Security.hpp"

#include "openssl/sha.h"
#include "openssl/hmac.h"

#include <string>
#include <stdio.h>
#include <sstream>
#include <string_view>
#include <array>
#include <iomanip>
#include <openssl/bio.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <iostream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <assert.h>

bool Security::CompareSignatures(std::string body,std::string key,std::string received)
{
	std::string calculated = "sha256=" + Security::GetHMAC(key, body);

	return TimingSafeEqual(calculated.c_str(),received.c_str(),calculated.size()) == 0;
}
std::string Security::GetHMAC(std::string key, std::string message)
{
	std::array<unsigned char, EVP_MAX_MD_SIZE> hash;
	unsigned int hashLen;

	HMAC(
		EVP_sha256(),
		key.data(),
		static_cast<int>(key.size()),
		reinterpret_cast<unsigned char const*>(message.data()),
		static_cast<int>(message.size()),
		hash.data(),
		&hashLen
	);

	std::stringstream ss;
	ss << std::hex << std::setfill('0');

	for (int i = 0; i < 32; i++) // ?
	{
		ss << std::hex << std::setw(2) << (unsigned int)hash[i];
	}

	return (ss.str());
}
int Security::TimingSafeEqual(const void* a, const void* b, const size_t size)
{
	const unsigned char* _a = (const unsigned char*)a;
	const unsigned char* _b = (const unsigned char*)b;
	unsigned char result = 0;
	size_t i;

	for (i = 0; i < size; i++) {
		result |= _a[i] ^ _b[i];
	}

	return result; /* returns 0 if equal, nonzero otherwise */
}