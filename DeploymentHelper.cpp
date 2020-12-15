#include <iostream>
#include <chrono>
#include "src/Config/Config.hpp"
#include "src/HTTP/Server/Server.hpp"

int main()
{
	// Designed for reverse proxys, no ssl support (yet)

	Config config = Config();
	config.LoadConfig();

	string_t address = U("http://127.0.0.1:1011");
	HTTPServer server(config);

	std::string line;
	std::getline(std::cin, line);

    std::cout << "Hello World!\n";
	return 0;
}
