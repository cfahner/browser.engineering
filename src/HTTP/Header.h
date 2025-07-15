/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>

namespace HTTP {

struct Header {
	const std::string name;
	const std::string value;
};

}
