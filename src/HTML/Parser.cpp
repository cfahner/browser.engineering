/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <memory>
#include <string>
#include <unicode/brkiter.h>
#include <vector>

#include "Parser.h"
#include "Token.h"
#include "TokenType.h"

namespace HTML {

std::vector<Token>* Parser::lex(std::string& html) {
	icu::UnicodeString html_unicode{icu::UnicodeString::fromUTF8(icu::StringPiece{html.c_str()})};

	UErrorCode u_error{U_ZERO_ERROR};
	std::unique_ptr<icu::BreakIterator> break_iterator{
		icu::BreakIterator::createCharacterInstance(icu::Locale::getDefault(), u_error)
	};
	assert(U_SUCCESS(u_error));
	break_iterator->setText(html_unicode);

	int32_t start = break_iterator->first();
	int32_t end = break_iterator->next();
	std::vector<Token>* token_list {new std::vector<Token>()};
	std::string buffer {};
	bool in_tag {false};
	while (end != icu::BreakIterator::DONE) {
		icu::UnicodeString unicode_char{html_unicode, start, end - start};

		std::string std_string;
		unicode_char.toUTF8String(std_string);
		if (std_string == "<") {
			in_tag = true;
			if (!buffer.empty()) {
				token_list->push_back(Token {TokenType::Text, buffer});
			}
			buffer = std::string {};
		} else if (std_string == ">") {
			in_tag = false;
			token_list->push_back(Token {TokenType::Tag, buffer});
			buffer = std::string {};
		} else {
			buffer += std_string;
		}

		start = end;
		end = break_iterator->next();
	}
	if (!in_tag && !buffer.empty()) {
		token_list->push_back(Token {TokenType::Text, buffer});
	}
	return token_list;
}

}
