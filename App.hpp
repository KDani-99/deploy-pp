#pragma once
#include <string>
#include <vector>
#include "Step.hpp"

class App
{
	private:
		const std::string &m_name;
		const std::string &m_repository;
		const std::string &m_local;
		const std::vector<Step> &m_steps;
	public:
		App(std::string name, std::string repository, std::string local, std::vector<Step> steps);
		std::string GetName();
		std::string GetRemoteRepository();
		std::string GetLocalRepositoryPath();
		std::vector<Step> GetSteps();
};