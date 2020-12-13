#include "Server.hpp"


HTTPServer::HTTPServer(string_t& address)
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
	http_response response;
	try
	{
		auto headers = request.headers();

		if (!headers.has(U("x-hub-signature")))
		{
			json::value jResponse = json::value::object();
			jResponse[U("status")] = json::value(U("failed"));
			jResponse[U("error")] = json::value(U("unauthorized"));

			this->SendJSONResponse(401, request, jResponse);

			return;
		}

		auto signature = request.headers().find(U("x-hub-signature"));
		
		auto body = request.extract_json(true).get();

		//ucout << body.at(U("x-hub-signature")).as_string();

		Secu

		//ucout << signature->first << std::endl << signature->second;

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
void HTTPServer::HandlePost(http_request request)
{
	ucout << request.to_string();
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