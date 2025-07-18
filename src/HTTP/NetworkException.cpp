/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <string>
#include <curl/curl.h>

#include "NetworkException.h"

namespace HTTP {

NetworkException::NetworkException(std::string message)
	: m_message{message}
{
}

const char* NetworkException::what() const noexcept {
	return m_message.c_str();
}

}
