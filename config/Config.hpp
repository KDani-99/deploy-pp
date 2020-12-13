#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <ostream>
#include <fstream>

#include "../App.hpp"

#include <yaml-cpp/depthguard.h>
#include "yaml-cpp/parser.h"
#include "yaml-cpp/exceptions.h"
#include "yaml-cpp/yaml.h"

using namespace std;
using YAML::Parser;


class Config {
	public:
		void LoadConfig();
		bool IsValidPath(std::string & path);
	private:
		std::map<std::string, App> m_apps;
};