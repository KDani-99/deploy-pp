#include "App.hpp"

App::App(std::string name, std::string repository, std::string local,std::string webhookSecret, std::vector<Step> steps) : m_name(name), m_repository(repository), m_local(local),m_webhookSecret(webhookSecret), m_steps(steps)
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
std::string App::GetWebhookSecret()
{
	return this->m_webhookSecret;
}
void App::TriggerActions()
{
	auto currentDirectory = std::filesystem::current_path();
	/*try
	{
		// Default: CD to directory
		_wchdir(this->GetLocalRepositoryPath().c_str());

		for (auto& action : this->m_steps)
		{
			// TODO: Log execution (if enabled)
			action.
		}

		//
	}
	catch (const std::exception& ex)
	{

	}*/

	// TODO: Change back to default dir
}