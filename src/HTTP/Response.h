/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>
#include <vector>

#include "Header.h"
#include "Message.h"

namespace HTTP {

struct Response : Message {

	static Response from_message(std::string_view message);

	Response(std::vector<Header> headers, std::string body)
		: Message(headers, body)
	{
	}

};

}
