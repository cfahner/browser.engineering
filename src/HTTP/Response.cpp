/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <algorithm>
#include <string>
#include <vector>

#include "Header.h"
#include "Message.h"
#include "Response.h"

namespace HTTP {

/**
 * Converts an HTTP response message string into a Response struct.
 * @param message The full message (headers, optionally followed by a body)
 */
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

}
