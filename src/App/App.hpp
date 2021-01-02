#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <boost/filesystem.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../Logger/Logger.hpp"
#include "../Step/Step.hpp"

class App
{
	private:
		std::string m_name;
		std::string m_branch;
		std::string m_repository;
		std::string m_local;
		std::string m_webhookSecret;
		bool m_force;
		std::vector<Step> m_steps;

		Logger* m_logger;

	public:
		App(std::string name, std::string repository, std::string local,std::string branch,std::string m_webhookSecret,bool force, std::vector<Step> steps,Logger * logger);
		std::string GetName();
		std::string GetRemoteRepository();
		std::string GetLocalRepositoryPath();
		std::string GetWebhookSecret();
		std::vector<Step> GetSteps(); // [deprecated]

		void Pull();
		void TriggerActions();
};