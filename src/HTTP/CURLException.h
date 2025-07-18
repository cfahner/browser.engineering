/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>
#include <curl/curl.h>

#include "NetworkException.h"

namespace HTTP {

class CURLException : public NetworkException {
public:
	const CURLcode curl_code;

	CURLException(CURLcode code);

};

}
