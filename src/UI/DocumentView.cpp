/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <chrono>
#include <iostream>
#include <pangomm/layout.h>
#include <string>
#include <unicode/brkiter.h>

#include "DocumentView.h"

#define LINE_HEIGHT 20

#include <iostream>
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

void DocumentView::scroll(int delta) {
	m_scroll += delta;
	if (m_scroll < 0) {
		m_scroll = 0;
	}
	queue_draw();
}

void DocumentView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int) {
	auto fn_start = std::chrono::high_resolution_clock::now();
	if (m_layout_needed) {
		layout();
	}
	int height = get_height();
	for (auto& item : m_display_list) {
		if (item->m_y > m_scroll + height || item->m_y + LINE_HEIGHT < m_scroll) {
			continue;
		}
		// https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-drawing-text.html
		cr->move_to(item->m_x, item->m_y - m_scroll);
		item->m_text_layout->show_in_cairo_context(cr);
	}
	auto fn_end = std::chrono::high_resolution_clock::now();
	std::cout
		<< "Draw duration: "
		<< std::chrono::duration_cast<std::chrono::microseconds>(fn_end - fn_start).count() / 1000.0L
		<< "ms"
		<< std::endl;
}

void DocumentView::on_resize(int, int) {
	m_layout_needed = true;
	queue_draw();
}

void DocumentView::layout() {
	clear_display_list();

	Pango::FontDescription font{};

	icu::UnicodeString u_html {icu::UnicodeString::fromUTF8(icu::StringPiece {m_parsed_html.c_str()})};

	UErrorCode u_error{U_ZERO_ERROR};
	std::unique_ptr<icu::BreakIterator> break_iterator {
		icu::BreakIterator::createWordInstance(icu::Locale::getDefault(), u_error)
	};
	assert(U_SUCCESS(u_error));
	break_iterator->setText(u_html);

	int cursor_x = 0;
	int cursor_y = 0;
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
		if (cursor_x + text_width > get_width()) {
			cursor_x = 0;
			cursor_y += LINE_HEIGHT;
			display_character->m_x = cursor_x;
			display_character->m_y = cursor_y;
		}
		m_display_list.push_back(display_character);
		cursor_x += text_width;

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
