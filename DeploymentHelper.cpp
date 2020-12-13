#include <iostream>

#include <chrono>
#include "config/Config.hpp"
#include "Server.hpp"

#include "Security.hpp"

int main()
{

	Config config = Config();
	auto t1 = std::chrono::high_resolution_clock::now();
	config.LoadConfig();
	auto t2 = std::chrono::high_resolution_clock::now();

	std::cout << ::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

	string_t address = U("http://127.0.0.1:1011");
	HTTPServer server(address,config);

	std::string line;
	std::getline(std::cin, line);

    std::cout << "Hello World!\n";
	return 0;
}
