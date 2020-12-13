#pragma once
#include <string>
#include <vector>
#include "Step.hpp"
/*#ifndef __UNIX__
	#include<unistd.h>  
#endif*/
#include <iostream>
#include <filesystem>

class App
{
	private:
		const std::string &m_name;
		const std::string &m_repository;
		const std::string &m_local;
		const std::string& m_webhookSecret;
		const std::vector<Step> &m_steps;
	public:
		App(std::string name, std::string repository, std::string local,std::string m_webhookSecret, std::vector<Step> steps);
		std::string GetName();
		std::string GetRemoteRepository();
		std::string GetLocalRepositoryPath();
		std::string GetWebhookSecret();
		std::vector<Step> GetSteps(); // [deprecated]

		void TriggerActions();
};