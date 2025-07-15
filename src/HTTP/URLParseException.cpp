/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <string>

#include "URLParseException.h"

namespace HTTP {

URLParseException::URLParseException(const std::string message)
	: message{message}
{
}

const char* URLParseException::what() const noexcept {
	return message.c_str();
}

}
