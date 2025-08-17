/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <chrono>
#include <iostream>
#include <memory>
#include <pangomm/layout.h>
#include <string>
#include <unicode/brkiter.h>
#include <vector>

#include "DocumentView.h"

#define LINE_HEIGHT 20

namespace UI {

DocumentView::DocumentView() {
	set_draw_func(sigc::mem_fun(*this, &DocumentView::on_draw));
}

DocumentView::~DocumentView() {
	clear_display_list();
}

void DocumentView::display_html(std::string& html) {
	m_token_list = m_parser.lex(html);
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
		if (item->m_y > m_scroll + height || item->m_y + item->m_span->m_height < m_scroll) {
			continue;
		}
		// https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-drawing-text.html
		cr->move_to(item->m_x, item->m_y - m_scroll);
		item->m_span->m_text_layout->show_in_cairo_context(cr);
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

	Pango::FontDescription font {};

	int viewport_width = get_width();

	int cursor_x = 0;
	int cursor_y = 0;
	for (auto& token : *m_token_list) {
		if (token.is_text()) {
			for (auto& span : text_to_spans(token.m_data, font)) {
				if (cursor_x + span->m_width > viewport_width) {
					cursor_x = 0;
					cursor_y += LINE_HEIGHT;
				}
				m_display_list.push_back(new DisplaySpan {cursor_x, cursor_y, span});
				cursor_x += span->m_width;
			}
		} else if (token.is_tag()) {
			if (token.m_data == "<i>" || token.m_data.substr(0, 3) == "<i ") {
				font.set_style(Pango::Style::ITALIC);
			} else if (token.m_data == "</i>") {
				font.set_style(Pango::Style::NORMAL);
			} else if (token.m_data == "<b>" || token.m_data.substr(0, 3) == "<b ") {
				font.set_weight(Pango::Weight::BOLD);
			} else if (token.m_data == "</b>") {
				font.set_weight(Pango::Weight::NORMAL);
			}
		}
	}
}

std::vector<Span*> DocumentView::text_to_spans(const std::string& text, const Pango::FontDescription font) {
	icu::UnicodeString unicode_text {icu::UnicodeString::fromUTF8(icu::StringPiece {text.c_str()})};

	UErrorCode u_error{U_ZERO_ERROR};
	std::unique_ptr<icu::BreakIterator> break_iterator {
		icu::BreakIterator::createWordInstance(icu::Locale::getDefault(), u_error)
	};
	assert(U_SUCCESS(u_error));
	break_iterator->setText(unicode_text);

	int32_t start = break_iterator->first();
	int32_t end = break_iterator->next();
	std::vector<Span*> spans {};
	while (end != icu::BreakIterator::DONE) {
		icu::UnicodeString unicode_word {unicode_text, start, end - start};

		std::string word;
		unicode_word.toUTF8String(word);

		std::shared_ptr<Pango::Layout> pango_word {create_pango_layout(word)};
		Span* span = new Span {pango_word};
		span->m_text_layout->set_font_description(font);
		spans.push_back(span);

		start = end;
		end = break_iterator->next();
	}
	return spans;
}

void DocumentView::clear_display_list() {
	for (auto& item : m_display_list) {
		delete item;
	}
	m_display_list.clear();
}

}
