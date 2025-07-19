/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>
#include <vector>

#include "Message.h"
#include "Method.h"
#include "Response.h"
#include "URL.h"

namespace HTTP {

struct Request : Message {
	Method method;
	URL url;

	Request(
		Method method,
		URL url,
		std::vector<Header> headers = std::vector<Header>(),
		std::string body = ""
	);

	Response send();

};

}
