/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <string>

#include "Token.h"

namespace HTML {

Token::Token(TokenType type, std::string data)
	: m_type {type}
	, m_data {data}
{
}

Token::~Token() = default;

bool Token::is_text() const {
	return m_type == TokenType::Text;
}

bool Token::is_tag() const {
	return m_type == TokenType::Tag;
}

}
