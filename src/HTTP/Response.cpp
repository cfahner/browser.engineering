/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "Header.h"
#include "Message.h"
#include "Response.h"

namespace HTTP {

Response Response::from_message(std::string_view message) {
	std::vector<Header> headers{};
	std::string body{};

	size_t from = 0;
	size_t to = message.find(HTTP::LINE_DELIMITER, from);
	while (to != std::string::npos) {
		std::string_view line{message.substr(from, to - from)};
		if (line.length() == 0) {
			body = std::string{message.substr(from + HTTP::LINE_DELIMITER.length())};
			break;
		}
		if (from == 0) {
			headers.push_back(Header::from_response_status(line));
		} else {
			headers.push_back(Header::from_string(line));
		}
		from += line.length() + HTTP::LINE_DELIMITER.length();
		to = message.find(HTTP::LINE_DELIMITER, from);
	}
	return Response{headers, body};
}

Response Response::from_data_uri(std::string_view data_uri) {
	if (data_uri.length() < 5 || data_uri.substr(0, 5) != "data:") {
		throw std::runtime_error{"Expected a valid data-uri starting with `data:`"};
	}

	std::vector<HTTP::Header> headers{};
	std::string body{};

	size_t comma_position = data_uri.find(',');
	if (comma_position != std::string_view::npos) {
		std::string content_type{data_uri.substr(5, comma_position - 5)};
		headers.push_back(HTTP::Header{"content-type", content_type});
		if (data_uri.length() > comma_position + 1) {
			body = data_uri.substr(comma_position + 1);
		}
	} else {
		headers.push_back(HTTP::Header{"content-type", "text/plain"});
	}
	return HTTP::Response{headers, body};
}

}
