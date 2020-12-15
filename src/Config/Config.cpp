#include "Config.hpp"

bool Config::IsValidPath(std::string & path)
{
	struct stat buffer;
	return (stat(path.c_str(), &buffer) == 0);
}

void Config::LoadConfig()
{
	try
	{
		YAML::Node config = YAML::LoadFile("deploy.yaml");

		auto apps = config["apps"].as<YAML::Node>();

		for (YAML::Node::iterator it = apps.begin(); it != apps.end(); ++it)
		{
			auto node = it->as<YAML::Node>();

			// Load application data

			std::string name = node["name"].as<std::string>();
			std::string repository = node["repository"].as<std::string>();
			std::string local = node["local"].as<std::string>();
			std::string branch = node["branch"].as<std::string>();
			std::string webhookSecret = node["secret"].as<std::string>();
			bool force = node["force"].as<bool>();
			/*if (!this->IsValidPath(local))
			{
				// show warning, skip this app

				continue;
			}*/

			// Load steps

			YAML::Node stepsNode = node["steps"].as<YAML::Node>();

			std::vector<Step> steps;

			for (YAML::Node::iterator stepIt = stepsNode.begin(); stepIt != stepsNode.end(); ++stepIt)
			{
				auto stepNode = stepIt->as<YAML::Node>();
				std::string stepName = stepNode["name"].as<std::string>();
				std::string stepCmd = stepNode["cmd"].as<std::string>();

				steps.push_back(Step(stepCmd, stepName));
			}

			App tempApp = App(name, repository, local,branch, webhookSecret,force, steps);

			// Insert app

			this->m_apps.insert(std::pair<std::string,App>(name, tempApp));
		}

		std::cout << "Apps size: " << this->m_apps.size() << std::endl;
	}
	catch (std::exception& ex)
	{
		std::cout << ex.what();
	}
	catch (...)
	{
		std::cout << "Global exception" << std::endl;
		// log
	}
}
const App& Config::GetAppByName(const std::string& name)
{
	return this->m_apps.at(name);
}