#pragma once
#include <string>

class Step {
	private:
		std::string m_cmd;
		std::string m_name;		
	public:
		Step(std::string cmd, std::string name);
		std::string GetCommand();
		std::string GetStepName();
};