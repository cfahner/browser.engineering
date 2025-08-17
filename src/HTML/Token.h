/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>

#include "TokenType.h"

namespace HTML {

struct Token {
	const TokenType m_type;
	const std::string m_data;

	Token(TokenType type, std::string data);
	~Token();

	bool is_text() const;
	bool is_tag() const;

};

}
