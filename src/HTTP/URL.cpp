/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <algorithm>
#include <iostream>
#include <string>

#include "URL.h"
#include "URLParseException.h"

namespace HTTP {

// based on https://stackoverflow.com/questions/2616011/easy-way-to-parse-a-url-in-c-cross-platform
URL URL::parse_string(std::string_view url_string) {
	if (url_string.length() == 0) {
		throw URLParseException{"URL can't be an empty string"};
	}
	std::string scheme{};
	std::string hostname{};
	uint_fast16_t port{80};
	std::string path{};
	std::string query{};

	typedef std::string_view::const_iterator iterator_t;

	iterator_t url_end{url_string.cend()};

	iterator_t query_start{std::find(url_string.cbegin(), url_end, '?')};

	iterator_t scheme_start{url_string.cbegin()};
	iterator_t scheme_end{std::find(scheme_start, url_end, ':')};

	if (scheme_end != url_end) {
		std::string temp_scheme{&*(scheme_end)};
		if (temp_scheme.length() >= 3 && temp_scheme.substr(0, 3) == "://") {
			scheme = std::string(scheme_start, scheme_end);
			scheme_end += 3;
		} else {
			scheme_end = url_string.cbegin();
		}
	} else {
		scheme_end = url_string.cbegin(); // no protocol
	}

	iterator_t host_start{scheme_end};
	iterator_t path_start{std::find(host_start, url_string.cend(), '/')};
	iterator_t host_end{std::find(
		scheme_end,
		(path_start != url_string.cend()) ? path_start : query_start,
		':'
	)};
	hostname = std::string(host_start, host_end);

	if (host_end != url_string.end() && ((&*(host_end))[0] == ':')) {
		host_end++;
		iterator_t port_end{(path_start != url_string.end()) ? path_start : query_start};
		try {
			port = std::stoi(std::string(host_end, port_end));
		} catch (std::invalid_argument& ia) {
			throw URLParseException{"Port could not be converted to a number"};
		}
	}

	if (path_start != url_string.cend()) {
		path = std::string(path_start, query_start);
	}

	if (query_start != url_string.cend()) {
		query = std::string(query_start, url_string.cend());
	}
	return URL{scheme, hostname, port, path, query};
}

URL::operator std::string() const {
	std::string result{};
	if (scheme.length() > 0) {
		result += scheme + "://";
	}
	if (hostname.length() > 0) {
		result += hostname;
		if (port != 80) {
			result += ":" + port;
		}
	}
	if (path.length() > 0) {
		result += path;
	}
	if (query.length() > 0) {
		result += query;
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, URL& url) {
	os << const_cast<const URL&>(url);
	return os;
}

std::ostream& operator<<(std::ostream& os, const URL& url) {
	os << static_cast<std::string>(url);
	return os;
}

}
