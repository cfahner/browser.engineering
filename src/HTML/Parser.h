/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <vector>

#include "Token.h"

namespace HTML {

class Parser {
public:
	/** Creates list of tokens on the heap from HTML. The caller gets ownership of the return value. */
	std::vector<Token>* lex(std::string& html);

};

}
