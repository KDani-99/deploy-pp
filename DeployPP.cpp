#include <iostream>
#include <string>
#include <chrono>
#include "src/Config/Config.hpp"
#include "src/HTTP/Server/Server.hpp"

int main()
{
	auto initialTs = std::chrono::high_resolution_clock::now();

	Config config = Config("logs/");
	config.LoadConfig();

	HTTPServer server(config);

	auto startedTs = std::chrono::high_resolution_clock::now();

	auto ts = std::chrono::duration_cast<std::chrono::milliseconds>(startedTs - initialTs).count();

	std::string info = "Server start process took: ";
	info += std::to_string(ts);
	info += " ms.";
	config.GetLogger()->Info("Server",info);

	std::string line;
	while (line != "exit")
		std::getline(std::cin, line);
	
	return 0;
}
