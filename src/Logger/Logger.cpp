#pragma once
#include "Logger.hpp"

std::string Logger::GetDate()
{
	std::time_t time = std::time(0);

	std::tm* time_tm = std::gmtime(&time);

	char buffer[42];
	std::strftime(buffer, 42, "%m/%d/%Y %X", time_tm);

	return buffer;
}

Logger::Logger(std::string path)
{
	if (!boost::filesystem::is_directory(path) || !boost::filesystem::exists(path))
		boost::filesystem::create_directory(path);

	this->m_path = path + "log_" + std::to_string(Utilities::GetCurrentTimestamp()) + ".log"; // Each run should have it's own log file
}

void Logger::Log(std::string level,std::string label, std::string info)
{
	std::string date = Logger::GetDate();
	try
	{
		
		std::string formatted = "[ " + date + " ] " + "[ " + level + " ] " + "[ " + label + " ]: " + info + "\n";

		printf(formatted.c_str());

		std::ofstream log = std::ofstream(this->m_path, std::ofstream::app);

		log << formatted;
		
		log.close();
	}
	catch (const std::exception& ex)
	{
		std::string failed = date + " [ ERROR ] [ LOGGER ]: Failed to save log. Exception: "+ex.what()+"\n";
		printf(failed.c_str());
	}
}
void Logger::Info(std::string label, std::string info)
{
	this->Log("INFO",label,info);
}
void Logger::Warning(std::string label, std::string info)
{
	this->Log("WARNING", label, info);
}
void Logger::Error(std::string label, std::string info)
{
	this->Log("ERROR", label, info);
}
void Logger::Success(std::string delivery, std::string event, int hookId, std::string before, std::string after)
{
	std::string date = Logger::GetDate();
	try
	{
		YAML::Emitter yamlLog;
		yamlLog << YAML::BeginMap;
		yamlLog << YAML::Key << "X-GitHub-Delivery";
		yamlLog << YAML::Value << delivery;
		yamlLog << YAML::Key << "X-GitHub-Event";
		yamlLog << YAML::Value << event;
		yamlLog << YAML::Key << "X-GitHub-Hook-ID";
		yamlLog << YAML::Value << hookId;
		yamlLog << YAML::Key << "Before";
		yamlLog << YAML::Value << before;
		yamlLog << YAML::Key << "After";
		yamlLog << YAML::Value << after;
		yamlLog << YAML::Key << "Timestamp";
		yamlLog << YAML::Value << date;
		yamlLog << YAML::EndMap;

		std::cout << yamlLog.c_str() << std::endl;

		std::string fileName = std::to_string(hookId);
		fileName += ".yaml";

		if (!boost::filesystem::exists("success_logs"))
			boost::filesystem::create_directory("success_logs");

		std::ofstream log = std::ofstream("success_logs/"+fileName, std::ofstream::app);
		
		log << yamlLog.c_str();

		log.close();

	}
	catch (const std::exception& ex)
	{
		std::string failed = date + " [ ERROR ] [ LOGGER ]: Failed to save success log. Exception: " + ex.what() + "\n";
		printf(failed.c_str());
	}
}