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
	std::string error{"CURL exception ("};
	switch (curl_code) {
		case CURLE_UNSUPPORTED_PROTOCOL: // 1
			error += "protocol not supported or disallowed";
			break;
		case CURLE_URL_MALFORMAT: // 3
			error += "malformed URL";
			break;
		case CURLE_COULDNT_RESOLVE_HOST: // 6
			error += "failed to resolve host";
			break;
		case CURLE_COULDNT_CONNECT: // 7
			error += "failed to connect";
			break;
		case CURLE_OPERATION_TIMEDOUT: // 28
			error += "timeout";
			break;
		case CURLE_SSL_CONNECT_ERROR: // 35
			error += "failed SSL/TLS handshake";
			break;
		case CURLE_TOO_MANY_REDIRECTS: // 47
			error += "too many redirects";
			break;
		case CURLE_PEER_FAILED_VERIFICATION: // 60
			error += "failed to verify certificate";
			break;
		default:
			error += "unknown";
	};
	m_message = error + ")";
}

}
