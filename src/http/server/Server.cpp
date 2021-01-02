#include "Server.hpp"
#include "../../Utilities/Utilities.hpp"

const string_t HTTPServer::HEADER_NAME = U("x-hub-signature-256"); // sh256 instead of sha1

HTTPServer::HTTPServer(Config& config) : m_config(config)
{
	this->m_serverConfig = nullptr;

	this->m_logger = new Logger("logs/"); // Folder path (current dir)
	
	LoadServerConfig();

	InitServer();
}
HTTPServer::~HTTPServer()
{
	this->m_listener.close().wait();

	delete this->m_serverConfig;
	delete this->m_logger;
}
void HTTPServer::LoadServerConfig()
{
	try
	{
		YAML::Node config = YAML::LoadFile("config.yaml");

		std::string ip = config["ip"].as<std::string>();
		unsigned short port = config["port"].as<unsigned short>();
		bool log = config["enableLogging"].as<bool>();

		this->m_serverConfig = new ServerConfig(ip, port, log);
	}
	catch (const std::exception& ex)
	{
		this->m_logger->Error("HTTP_SERVER_CTOR", ex.what());
	}

}
void HTTPServer::InitServer()
{
	try
	{
		string_t address = U("http://") + Utilities::ToString_T(this->m_serverConfig->GetAddress()); // TODO: http/https
		address += U(":") + Utilities::ToString_T(this->m_serverConfig->GetPort());

		uri_builder uri(address);

		auto addr = uri.to_uri().to_string();

		this->m_listener = http_listener(addr);

		m_listener.support(methods::GET, std::bind(&HTTPServer::HandleGet, this, std::placeholders::_1));
		m_listener.support(methods::POST, std::bind(&HTTPServer::HandlePost, this, std::placeholders::_1));

		m_listener.open().wait();

		ucout << utility::string_t(U("Server started ")) << addr << std::endl;
	}
	catch (const std::exception& ex)
	{
		this->m_logger->Error("HTTP_SERVER_INIT", ex.what());
	}
}
void HTTPServer::HandleGet(http_request request)
{
	// TODO: 
}
void HTTPServer::HandlePost(http_request request)
{
	http_response response;

	for(auto & header : request.headers())
		ucout << header.first << std::endl;

	try
	{
		if (request.headers().content_type() != U("application/json"))
		{
			json::value jResponse = json::value::object();
			jResponse[U("status")] = json::value(U("failed"));
			jResponse[U("error")] = json::value(U("json_required"));

			this->SendJSONResponse(400, request, jResponse);

			return;
		}

		auto headers = request.headers();

		if (!headers.has(HTTPServer::HEADER_NAME))
		{
			json::value jResponse = json::value::object();
			jResponse[U("status")] = json::value(U("failed"));
			jResponse[U("error")] = json::value(U("unauthorized"));

			this->SendJSONResponse(401, request, jResponse);

			return;
		}

		auto signature = request.headers().find(HTTPServer::HEADER_NAME);

		auto stringifiedBody = request.extract_string().get();

		auto body = json::value::parse(stringifiedBody);//request.extract_json(false).get();

		auto repository = body.at(U("repository")).as_object();

		auto project = repository.at(U("url")).as_string();

		std::string projectName = Utilities::GetProjectName(std::string(project.begin(), project.end()));

		// Get secret from Apps map

		auto app = this->m_config.GetAppByName(projectName);

		if (!Security::CompareSignatures(std::string(stringifiedBody.begin(), stringifiedBody.end()), app.GetWebhookSecret(), std::string(signature->second.begin(), signature->second.end())))
		{
			json::value jResponse = json::value::object();
			jResponse[U("status")] = json::value(U("failed"));
			jResponse[U("error")] = json::value(U("signature_mismatch"));

			this->SendJSONResponse(401, request, jResponse);

			return;
		}

		// Trigger and await the action(s)

		app.TriggerActions();

		json::value jResponse = json::value::object();
		jResponse[U("status")] = json::value(U("successful"));
		this->SendJSONResponse(200, request, jResponse);

		return;
	}
	catch (const std::exception& ex)
	{
		// Generate a random GUID 
		std::string uuidStr = Utilities::GenerateUUID();

		this->m_logger->Error(uuidStr, ex.what());
		
		// If it ever gets here, throw an error

		json::value jResponse = json::value::object();
		jResponse[U("status")] = json::value(U("failed"));
		jResponse[U("error")] = json::value(U("request_failed"));
		jResponse[U("unique_error_code")] = json::value(Utilities::ToString_T(uuidStr));

		this->SendJSONResponse(400, request, jResponse);
	}
}
void HTTPServer::SendJSONResponse(int code,const http_request& request,const json::value& jsonObject)
{
	// Create HTTP response 

	http_response response;

	// Set response content

	response.set_status_code(code);
	response.headers().set_content_type(U("application/json"));;
	response.set_body(jsonObject);

	// Send reply

	request.reply(response).wait();
}