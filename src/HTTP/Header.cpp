/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <algorithm>
#include <cctype>
#include <string>

#include "Header.h"

namespace HTTP {

namespace {

void string_to_lowercase(std::string& input) {
	auto tolower_callback = [](unsigned char c) { return std::tolower(c); };
	std::transform(input.begin(), input.end(), input.begin(), tolower_callback);
}

}

Header::operator std::string() const {
	return std::string{name} + ": " + value;
}

Header Header::from_response_status(std::string_view status_line) {
	std::string parsed{};
	size_t space_position = status_line.find(' ');
	if (space_position != std::string_view::npos) {
		size_t next_space_position = status_line.find(' ', space_position + 1);
		size_t status_length = next_space_position != std::string_view::npos
			? next_space_position - space_position
			: std::string_view::npos;
		parsed = status_line.substr(space_position + 1, status_length);
	}
	return Header{":status", parsed};
}

Header Header::from_string(std::string_view header_line) {
	std::string name{};
	std::string value{};
	size_t colon_position = header_line.find(':');
	if (colon_position != std::string_view::npos) {
		name = header_line.substr(0, colon_position);
		value = header_line.substr(colon_position + 1);
		if (value[0] == ' ') {
			value = value.substr(1);
		}
	}
	return Header{name, value};
}

Header::Header(std::string name, std::string value)
	: name{name}
	, value{value}
{
	string_to_lowercase(name);
}

}
