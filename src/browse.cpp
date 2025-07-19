/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */

#include <iostream>
#include <string>

#include "HTTP/Method.h"
#include "HTTP/NetworkException.h"
#include "HTTP/Request.h"
#include "HTTP/Response.h"
#include "HTTP/URL.h"
#include "HTTP/URLParseException.h"

int main(void) {
	std::cout << "Type URL: ";
	std::string url_string{""};
	std::getline(std::cin, url_string);
	try {
		HTTP::Request request{
			HTTP::Method::GET,
			HTTP::URL::parse_string(url_string)
		};
		HTTP::Response response{request.send()};
		for (const HTTP::Header& header : response.headers) {
			std::cout << static_cast<std::string>(header) << std::endl;
		}
		std::cout << response.body.substr(0, response.body.length() >= 100 ? 100 : response.body.length());
		std::cout << "..." << std::endl;
	} catch (HTTP::NetworkException& ne) {
		std::cout << "Network error: " << ne.what() << std::endl;
	} catch (HTTP::URLParseException& upe) {
		std::cout << "Could not parse URL: " << upe.what() << std::endl;
	}
	return 0;
}
