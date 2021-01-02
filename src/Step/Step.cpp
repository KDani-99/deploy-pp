#include "Step.hpp"

Step::Step(std::string cmd, std::string name)
{
	this->m_cmd = cmd;
	this->m_name = name;
}
std::string Step::GetCommand()
{
	return this->m_cmd;
}
std::string Step::GetStepName()
{
	return this->m_name;
}