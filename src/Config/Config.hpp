#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <ostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include "../App/App.hpp"

#include <yaml-cpp/depthguard.h>
#include <yaml-cpp/parser.h>
#include <yaml-cpp/exceptions.h>
#include <yaml-cpp/yaml.h>

using YAML::Parser;

class Config {
	public:
		void LoadConfig();
		bool IsValidPath(std::string & path);
		const App& GetAppByName(const std::string& name);
	private:
		std::map<std::string, App> m_apps;
};