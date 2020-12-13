#include <iostream>
#include "config/Config.hpp"
#include <chrono>
int main()
{
	/* Optimized for Ubuntu/Windows */

	Config config = Config();
	auto t1 = std::chrono::high_resolution_clock::now();
	config.LoadConfig();
	auto t2 = std::chrono::high_resolution_clock::now();

	std::cout << ::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;

    std::cout << "Hello World!\n";
}
