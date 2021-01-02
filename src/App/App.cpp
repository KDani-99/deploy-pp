#include "App.hpp"

App::App(std::string name, std::string repository, std::string local,std::string branch,std::string webhookSecret,bool force, std::vector<Step> steps,Logger * logger) : m_name(name), m_repository(repository), m_local(local),m_branch(branch),m_webhookSecret(webhookSecret),m_force(force), m_steps(steps), m_logger(logger)
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
void App::Pull()
{
	std::string cmd = "git pull origin ";
	cmd += this->m_branch;

	if (this->m_force) cmd += " --force";

	int result = system(cmd.c_str());

	if (result != 0)
	{
		throw "Git pull failed (origin). Returned a non-zero code.";
	}
}
void App::TriggerActions()
{
	auto currentDirectory = boost::filesystem::current_path();

	// Default: CD to directory
		
	boost::filesystem::current_path(this->GetLocalRepositoryPath().c_str());

	this->Pull();
		
	for (auto& action : this->m_steps)
	{
		// TODO: Log execution (if enabled)

		std::string msg = "Executing step: ";
		msg += action.GetStepName();

		this->m_logger->Info("Action", msg);

		int result = system(action.GetCommand().c_str());
		if (result != 0)
		{
			std::string err = "Execution failed for step: ";
			err += action.GetStepName();
			err += " ( ";
			err += "command: ";
			err += action.GetCommand();
			err += " ). Returned a non-zero code.";

			throw err;
		}
	}

	// Change back to default dir

	boost::filesystem::current_path(currentDirectory);

}