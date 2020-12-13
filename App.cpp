#include "App.hpp"

App::App(std::string name, std::string repository, std::string local, std::vector<Step> steps) : m_name(name), m_repository(repository), m_local(local), m_steps(steps)
{
}
std::string App::GetName() 
{
	return this->m_name;
}
std::string App::GetRemoteRepository()
{
	return this->m_repository;
}
std::string App::GetLocalRepositoryPath()
{
	return this->m_local;
}
std::vector<Step> App::GetSteps()
{
	return this->m_steps;
}