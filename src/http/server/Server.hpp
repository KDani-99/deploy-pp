#pragma once

#include <cpprest/http_listener.h>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>                       // JSON library
#include <cpprest/uri.h>                        // URI library
#include <cpprest/containerstream.h>            // Async streams backed by STL containers
#include <cpprest/interopstream.h>              // Bridges for integrating Async streams with STL and WinRT streams
#include <cpprest/rawptrstream.h>               // Async streams backed by raw pointer to memory
#include <cpprest/producerconsumerstream.h>     // Async streams for producer consumer scenarios

using namespace web;
using namespace http;
using namespace utility;
using namespace http::experimental::listener;
using namespace web::http::experimental::listener;          // HTTP server client
using namespace web::json;                                  // JSON library

class HTTPServer
{
	public:
		HTTPServer(string_t &address);
		pplx::task<void> open() { return m_listener.open(); }
		pplx::task<void> close() { return m_listener.close(); }
	private:
		void InitServer(string_t& address);
		void HandleGet(http_request request);
		void HandlePost(http_request request);
		void SendJSONResponse(int code, const http_request& request,const json::value& jsonObject);
		http_listener m_listener;
};