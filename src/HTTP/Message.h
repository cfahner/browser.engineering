/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>
#include <vector>

#include "Header.h"

namespace HTTP {

const std::string LINE_DELIMITER{"\r\n"};

struct Message {
	std::vector<Header> headers;
	std::string body;

protected:
	Message(std::vector<Header> headers, std::string body)
		: headers{headers}
		, body{body}
	{
	}

};

}
