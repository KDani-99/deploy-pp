#include "ServerConfig.hpp"

ServerConfig::ServerConfig(std::string address, unsigned short port, bool log)
{
	this->m_address = address;
	this->m_port = port;
	this->m_log = log;
}
bool ServerConfig::IsLoggingEnabled()
{
	return this->m_log;
}
unsigned short ServerConfig::GetPort()
{
	return this->m_port;
}
std::string ServerConfig::GetAddress()
{
	return this->m_address;
}