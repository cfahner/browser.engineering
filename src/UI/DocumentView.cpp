/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <pangomm/layout.h>
#include <string>
#include <unicode/brkiter.h>

#include "DocumentView.h"

namespace UI {

DocumentView::DocumentView() {
	set_draw_func(sigc::mem_fun(*this, &DocumentView::on_draw));
}

DocumentView::~DocumentView() {
	clear_display_list();
}

void DocumentView::display_html(std::string& html) {
	m_parsed_html = m_parser.lex(html);
	m_layout_needed = true;
	queue_draw();
}

void DocumentView::on_draw(
	const Cairo::RefPtr<Cairo::Context>& cr,
	[[maybe_unused]] int width,
	[[maybe_unused]] int height
) {
	if (m_layout_needed) {
		layout();
	}
	for (auto& item : m_display_list) {
		cr->move_to(item->m_x, item->m_y - m_scroll);
		item->m_text_layout->show_in_cairo_context(cr);
	}
}

void DocumentView::layout() {
	clear_display_list();

	Pango::FontDescription font{};
	font.set_family("Monospace");

	icu::UnicodeString u_html {icu::UnicodeString::fromUTF8(icu::StringPiece {m_parsed_html.c_str()})};

	UErrorCode u_error{U_ZERO_ERROR};
	std::unique_ptr<icu::BreakIterator> break_iterator {
		icu::BreakIterator::createCharacterInstance(icu::Locale::getDefault(), u_error)
	};
	assert(U_SUCCESS(u_error));
	break_iterator->setText(u_html);

	int cursor_x = 0;
	int cursor_y = 0;
	int line_height = 20;
	int32_t start = break_iterator->first();
	int32_t end = break_iterator->next();
	while (end != icu::BreakIterator::DONE) {
		icu::UnicodeString unicode_char {u_html, start, end - start};

		std::string std_string;
		unicode_char.toUTF8String(std_string);

		DisplayCharacter* display_character = new DisplayCharacter {
			cursor_x, cursor_y, create_pango_layout(std_string)
		};
		display_character->m_text_layout->set_font_description(font);
		int text_width;
		int text_height;
		display_character->m_text_layout->get_pixel_size(text_width, text_height);
		m_display_list.push_back(display_character);

		cursor_x += text_width;
		if (cursor_x > get_width()) {
			cursor_x = 0;
			cursor_y += line_height;
		}

		start = end;
		end = break_iterator->next();
	}
}

void DocumentView::clear_display_list() {
	for (auto& item : m_display_list) {
		delete item;
	}
	m_display_list.clear();
}

}
