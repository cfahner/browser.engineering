/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <string>
#include <unicode/brkiter.h>

#include "HTMLEntities.h"
#include "Token.h"

namespace HTML {

Token::Token(TokenType type, std::string data)
	: m_type {type}
	, m_data {is_text() ? decode_entities(data) : data}
{
}

Token::~Token() = default;

bool Token::is_text() const {
	return m_type == TokenType::Text;
}

bool Token::is_tag() const {
	return m_type == TokenType::Tag;
}

std::string Token::decode_entities(std::string& input) {
	icu::UnicodeString u_input {icu::UnicodeString::fromUTF8(icu::StringPiece{input.c_str()})};

	UErrorCode status {U_ZERO_ERROR};
	std::unique_ptr<icu::BreakIterator> break_iterator {
		icu::BreakIterator::createCharacterInstance(icu::Locale::getDefault(), status)
	};
	assert(U_SUCCESS(status));
	break_iterator->setText(u_input);

	std::string result {};
	bool in_entity {false};
	std::string entity_buffer {};

	int32_t start = break_iterator->first();
	int32_t end = break_iterator->next();
	while (end != icu::BreakIterator::DONE) {
		icu::UnicodeString u_character {u_input, start, end - start};
		std::string character {};
		u_character.toUTF8String(character);

		if (character == "&") {
			in_entity = true;
			entity_buffer = std::string {};
		} else if (in_entity && character == ";") {
			in_entity = false;
			result += HTMLEntities::decode_entity(entity_buffer);
			entity_buffer = std::string {};
		} else if (in_entity) {
			entity_buffer += character;
		} else {
			result += character;
		}

		start = end;
		end = break_iterator->next();
	}
	return result + entity_buffer;
}

}
