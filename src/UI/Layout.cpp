/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <memory>
#include <pangomm/layout.h>
#include <unicode/brkiter.h>

#include "Layout.h"

#define LINE_HEIGHT 20

namespace UI {

Layout::Layout(Gtk::Widget* widget, std::vector<HTML::Token>& tokens, int width, int height)
	: m_widget {widget}
	, m_width {width}
	, m_height {height}
{
	for (auto& token : tokens) {
		if (token.is_text()) {
			for (auto& span : text_to_spans(token.m_data, m_font)) {
				m_display_list.push_back(new DisplaySpan {0, 0, span});
			}
		} else if (token.is_tag()) {
			if (token.m_data == "i" || token.m_data.substr(0, 2) == "i ") {
				m_font.set_style(Pango::Style::ITALIC);
			} else if (token.m_data == "/i") {
				m_font.set_style(Pango::Style::NORMAL);
			} else if (token.m_data == "b" || token.m_data.substr(0, 2) == "b ") {
				m_font.set_weight(Pango::Weight::BOLD);
			} else if (token.m_data == "/b") {
				m_font.set_weight(Pango::Weight::NORMAL);
			}
		}
	}
	recalculate_positions();
}

Layout::~Layout() {
	clear_display_list();
}

void Layout::set_width(int width) {
	int old_width = m_width;
	m_width = width;
	if (old_width != m_width) {
		recalculate_positions();
	}
}

void Layout::set_height(int height) {
	int old_height = m_height;
	m_height = height;
	if (old_height != m_height) {
		recalculate_positions();
	}
}

void Layout::set_size(int width, int height) {
	int old_width = m_width;
	int old_height = m_height;
	m_width = width;
	m_height = height;
	if (old_width != m_width || old_height != m_height) {
		recalculate_positions();
	}
}

std::vector<Span*> Layout::text_to_spans(const std::string& text, const Pango::FontDescription font) {
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

		std::shared_ptr<Pango::Layout> pango_word {m_widget->create_pango_layout(word)};
		Span* span = new Span {pango_word};
		span->m_text_layout->set_font_description(font);
		spans.push_back(span);

		start = end;
		end = break_iterator->next();
	}
	return spans;
}

void Layout::recalculate_positions() {
	int cursor_x {0};
	int cursor_y {0};
	for (auto& item : m_display_list) {
		if (cursor_x + item->m_span->m_width > m_width) {
			cursor_x = 0;
			cursor_y += LINE_HEIGHT;
		}
		item->set_position(cursor_x, cursor_y);
		cursor_x += item->m_span->m_width;
	}
}

void Layout::clear_display_list() {
	for (auto& item : m_display_list) {
		delete item;
		item = nullptr;
	}
	m_display_list.clear();
}

}
