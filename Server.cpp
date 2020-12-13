#include "Server.hpp"
#include "Utilities.hpp"

const string_t HTTPServer::HEADER_NAME = U("x-hub-signature");

HTTPServer::HTTPServer(string_t& address, Config& config) : m_config(config)
{
	InitServer(address);
}
void HTTPServer::InitServer(string_t& address)
{
	try
	{

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
		ucout <<ex.what();
	}
}
void HTTPServer::HandleGet(http_request request)
{
	
}
void HTTPServer::HandlePost(http_request request)
{
	http_response response;
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

		auto body = request.extract_json(true).get();

		auto project = body.at(U("url")).as_string();

		std::string projectName = Utilities::GetProjectName(std::string(project.begin(), project.end()));

		// Get secret from Apps map

		auto app = this->m_config.GetAppByName(projectName);

		auto stringifiedBody = request.extract_string(true).get();

		if (!Security::CompareSignatures(string(stringifiedBody.begin(), stringifiedBody.end()), app.GetWebhookSecret(), string(signature->second.begin(), signature->second.end())))
		{
			json::value jResponse = json::value::object();
			jResponse[U("status")] = json::value(U("failed"));
			jResponse[U("error")] = json::value(U("signature_mismatch"));

			this->SendJSONResponse(401, request, jResponse);

			return;
		}

		//ucout << body.at(U("x-hub-signature")).as_string();


		//ucout << signature->first << std::endl << signature->second;

		// Trigger action

		json::value jResponse = json::value::object();
		jResponse[U("status")] = json::value(U("successful"));
		this->SendJSONResponse(200, request, jResponse);
		return;
	}
	catch (const std::exception& ex)
	{

	}
	catch (...)
	{

	}

	// If it ever gets here, throw an error

	json::value jResponse = json::value::object();
	jResponse[U("status")] = json::value(U("failed"));
	jResponse[U("error")] = json::value(U("request_failed"));

	this->SendJSONResponse(400, request, jResponse);
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