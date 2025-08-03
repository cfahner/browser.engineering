/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <memory>
#include <string>
#include <unicode/brkiter.h>
#include <iostream>

#include "Parser.h"

namespace HTML {

std::string Parser::lex(std::string& html) {
	icu::UnicodeString html_unicode{icu::UnicodeString::fromUTF8(icu::StringPiece{html.c_str()})};

	UErrorCode u_error{U_ZERO_ERROR};
	std::unique_ptr<icu::BreakIterator> break_iterator{
		icu::BreakIterator::createCharacterInstance(icu::Locale::getDefault(), u_error)
	};
	assert(U_SUCCESS(u_error));
	break_iterator->setText(html_unicode);

	int32_t start = break_iterator->first();
	int32_t end = break_iterator->next();
	while (end != icu::BreakIterator::DONE) {
		icu::UnicodeString unicode_char{html_unicode, start, end - start};

		std::string std_string;
		unicode_char.toUTF8String(std_string);
		std::cout << std_string;

		start = end;
		end = break_iterator->next();
	}
	return {};
}

}
