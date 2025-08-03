/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>

namespace HTML {

class Parser {
public:
	std::string lex(std::string& html);

};

}
