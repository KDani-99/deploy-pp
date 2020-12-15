#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include <boost/filesystem.hpp>

#include "../Utilities/Utilities.hpp"

class Logger
{
	private:
		std::string m_path;
		void Log(std::string level,std::string label, std::string info);

		static std::string GetDate();

	public:
		Logger(std::string path);
		void Info(std::string label,std::string info);
		void Warning(std::string label, std::string info);
		void Error(std::string label, std::string info);
};