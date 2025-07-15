/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>

namespace HTTP {

class URLParseException : public std::exception {
protected:
	std::string message;

public:
	URLParseException(const std::string message);

	virtual const char* what() const noexcept;

};

}
