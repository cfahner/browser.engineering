/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>

namespace HTTP {

struct Header {
	std::string name;
	std::string value;

	operator std::string() const;

	static Header from_response_status(std::string_view status_line);

	static Header from_string(std::string_view header_line);

	Header(std::string name, std::string value);

};

}
