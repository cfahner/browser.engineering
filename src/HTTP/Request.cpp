/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <string>
#include <vector>
#include <curl/curl.h>

#include "CURLException.h"
#include "Method.h"
#include "Response.h"
#include "NetworkException.h"
#include "Request.h"
#include "URL.h"

namespace HTTP {

namespace {

static size_t write_callback_for_curl(void *contents, size_t size, size_t nmemb, void *userp) {
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

}

Request::Request(Method method, URL url, std::vector<Header> headers, std::string body)
	: Message(headers, body)
	, method{method}
	, url{url}
{
}

Response Request::send() {
	if (url.scheme.length() != 0 && url.scheme != "http" && url.scheme != "https") {
		throw NetworkException{"Protocol not allowed (" + url.scheme + ")"};
	}
	// based on https://gist.github.com/alghanmi/c5d7b761b2c9ab199157
	CURL* curl = curl_easy_init();
	if (curl) {
		std::string response_buffer;
		curl_easy_setopt(curl, CURLOPT_URL, static_cast<std::string>(url).c_str());
		curl_easy_setopt(curl, CURLOPT_HEADER, true);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback_for_curl);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_buffer);
		CURLcode result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if (result == CURLE_OK) {
			return Response::from_message(response_buffer);
		}
		throw CURLException{result};
	}
	throw NetworkException{"Failed to initialize CURL handle"};
}

}
