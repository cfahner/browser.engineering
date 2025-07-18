/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <string>
#include <curl/curl.h>

#include "CURLException.h"

namespace HTTP {

CURLException::CURLException(CURLcode curl_code)
	: NetworkException("")
	, curl_code{curl_code}
{
	curl_code = curl_code;
	std::string error{"Network exception (CURL): "};
	switch (curl_code) {
		case CURLE_UNSUPPORTED_PROTOCOL:
			error += "unsupported protocol";
			break;
		case CURLE_URL_MALFORMAT: // 3
			error += "malformed URL";
			break;
		case CURLE_COULDNT_RESOLVE_HOST: // 6
			error += "failed to resolve host";
			break;
		case CURLE_COULDNT_CONNECT:
			error += "failed to connect";
			break;
		case CURLE_OPERATION_TIMEDOUT:
			error += "timeout";
			break;
		case CURLE_SSL_CONNECT_ERROR:
			error += "failed SSL/TLS handshake";
			break;
		case CURLE_TOO_MANY_REDIRECTS:
			error += "too many redirects";
			break;
		default:
			error += "unknown";
	};
	m_message = error;
}

}
