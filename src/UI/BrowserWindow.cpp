/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <string>

#include "BrowserWindow.h"
#include "../HTTP/Header.h"
#include "../HTTP/Method.h"
#include "../HTTP/NetworkException.h"
#include "../HTTP/Request.h"
#include "../HTTP/Response.h"
#include "../HTTP/URL.h"
#include "../HTTP/URLParseException.h"

namespace UI {

BrowserWindow::BrowserWindow() {
	maximize();
	set_child(m_document_view);
}

void BrowserWindow::visit(std::string_view url_string) {
	try {
		HTTP::Response response{fetch_url(url_string)};
		for (const HTTP::Header& header : response.headers) {
			std::cout << static_cast<std::string>(header) << std::endl;
		}
	} catch (HTTP::NetworkException& ne) {
		std::cout << "Network error: " << ne.what() << std::endl;
	} catch (HTTP::URLParseException& upe) {
		std::cout << "Could not parse URL: " << upe.what() << std::endl;
	}
}

HTTP::Response BrowserWindow::fetch_url(std::string_view url_string) {
	if (url_string.length() >= 5 && url_string.substr(0, 5) == "data:") {
		return HTTP::Response::from_data_uri(url_string);
	}
	HTTP::Request request = create_request(HTTP::Method::GET, HTTP::URL::parse_string(url_string));
	return request.send();
}

HTTP::Request BrowserWindow::create_request(HTTP::Method method, HTTP::URL url) {
	HTTP::Request request{method, url};
	request.headers.push_back(HTTP::Header{"user-agent", "CFahnerBrowser"});
	return request;
}

}
