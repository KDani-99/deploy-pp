#include <iostream>
#include <chrono>
#include "src/Config/Config.hpp"
#include "src/HTTP/Server/Server.hpp"

int main()
{
	// Designed for reverse proxy, it has no ssl support (yet)

	Config config = Config("logs/");
	config.LoadConfig();

	HTTPServer server(config);

	std::string line;
	std::getline(std::cin, line);

	return 0;
}
