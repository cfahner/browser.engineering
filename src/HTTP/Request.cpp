/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <string>
#include <vector>

#include "Method.h"
#include "Request.h"

namespace HTTP {

Request::Request(const Method method, const URL url, const std::vector<Header> headers, const std::string body)
	: method{method}
	, url{url}
	, headers{headers}
	, body{body}
{
}

}
