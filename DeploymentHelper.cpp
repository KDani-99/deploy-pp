#include <iostream>
#include <chrono>
#include "src/Config/Config.hpp"
#include "src/HTTP/Server/Server.hpp"

int main()
{
	// Designed for reverse proxys, no ssl support (yet)

	// Load config.yaml

	Config config = Config();
	config.LoadConfig();

	// Instantiate the server (using the config instance)

	HTTPServer server(config);

	// Keep the app running (should be started from a process manager)

	std::string line;
	std::getline(std::cin, line);

	return 0;
}
