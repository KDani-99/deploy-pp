#pragma once

#include <string>

struct ServerConfig
{
	private:
		std::string m_address;
		unsigned short m_port;
		bool m_log;
	public:
		ServerConfig(std::string address,unsigned short port,bool log);
		bool IsLoggingEnabled();
		unsigned short GetPort();
		std::string GetAddress();
};