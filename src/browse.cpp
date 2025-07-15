/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */

#include <iostream>
#include <string>

#include "HTTP/Method.h"
#include "HTTP/Request.h"
#include "HTTP/URL.h"
#include "HTTP/URLParseException.h"

int main(void) {
	std::cout << "Type URL: ";
	std::string url_string;
	std::getline(std::cin, url_string);
	try {
		HTTP::Request request{
			HTTP::Method::GET,
			HTTP::URL::parse_string(url_string)
		};
		std::cout << "Parsed: " << request.url << "\n";
	} catch (HTTP::URLParseException& upe) {
		std::cout << "Could not parse URL: " << upe.what() << "\n";
	}
	return 0;
}
