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

	/**
	 * Converts an HTTP response message string into a Response struct.
	 * @param message The full message (headers + `\r\n` + optionally followed by a body)
	 */
	static Response from_message(std::string_view message);

	/** @param data_uri The data-uri to create a pseudo-response for (prefixed with `data:`) */
	static Response from_data_uri(std::string_view data_uri);

	Response(std::vector<Header> headers, std::string body)
		: Message(headers, body)
	{
	}

};

}
