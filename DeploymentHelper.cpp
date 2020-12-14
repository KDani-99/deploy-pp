#include <iostream>

#include <chrono>
#include "src/Config/Config.hpp"
#include "src/HTTP/Server/Server.hpp"

int main()
{
	// Designed for reverse proxys, no ssl support (yet)

	Config config = Config();
	auto t1 = std::chrono::high_resolution_clock::now();
	config.LoadConfig();
	auto t2 = std::chrono::high_resolution_clock::now();

	std::cout << ::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

	string_t address = U("http://127.0.0.1:1011");
	HTTPServer server(config);

	std::string line;
	std::getline(std::cin, line);

    std::cout << "Hello World!\n";
	return 0;
}
