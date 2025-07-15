/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <iostream>
#include <string>

namespace HTTP {

struct URL {
	std::string scheme{};
	std::string hostname{};
	uint_fast16_t port{80};
	std::string path{};
	std::string query{};

	/** Parse a URL-string into a URL struct. */
	static URL parse_string(std::string_view url_string);

};

std::ostream& operator<<(std::ostream& os, URL& url);
std::ostream& operator<<(std::ostream& os, const URL& url);

}
