/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>
#include <vector>

#include "Header.h"
#include "Method.h"
#include "URL.h"

namespace HTTP {

struct Request {
	Method method;
	URL url;
	std::vector<Header> headers;
	std::string body;

	Request(
		Method method,
		URL url,
		std::vector<Header> headers = std::vector<Header>(),
		std::string body = ""
	);

};

}
