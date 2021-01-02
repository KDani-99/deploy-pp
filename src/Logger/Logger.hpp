#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

#include <boost/filesystem.hpp>

#include <yaml-cpp/depthguard.h>
#include <yaml-cpp/parser.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/yaml.h>

#include "../Utilities/Utilities.hpp"

using YAML::Parser;

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
		void Success(std::string delivery, std::string event, int hookId,std::string before, std::string after);
};