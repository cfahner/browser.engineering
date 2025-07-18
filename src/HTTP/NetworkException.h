/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>

namespace HTTP {

class NetworkException : public std::exception {
protected:
	std::string m_message;

public:
	NetworkException(std::string message);

	virtual const char* what() const noexcept final;

};

}
