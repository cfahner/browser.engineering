/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cassert>
#include <memory>
#include <pangomm/layout.h>
#include <unicode/brkiter.h>

#include "Layout.h"
#include "Line.h"

#define DEFAULT_FONT_SIZE 16

namespace UI {

Layout::Layout(Gtk::Widget* widget, std::vector<HTML::Token>& tokens)
	: m_widget {widget}
{
	m_font.set_size(DEFAULT_FONT_SIZE * PANGO_SCALE);
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
			} else if (token.m_data == "small" || token.m_data.substr(0, 6) == "small ") {
				m_font.set_size(m_font.get_size() - 2 * PANGO_SCALE);
			} else if (token.m_data == "/small") {
				m_font.set_size(m_font.get_size() + 2 * PANGO_SCALE);
			} else if (token.m_data == "big" || token.m_data.substr(0, 4) == "big ") {
				m_font.set_size(m_font.get_size() + 4 * PANGO_SCALE);
			} else if (token.m_data == "/big") {
				m_font.set_size(m_font.get_size() - 4 * PANGO_SCALE);
			} else if (token.m_data == "h1" || token.m_data.substr(0, 3) == "h1 ") {
				m_font.set_size(m_font.get_size() * 2);
			} else if (token.m_data == "/h1") {
				m_font.set_size(m_font.get_size() / 2);
			} else if (token.m_data == "h2" || token.m_data.substr(0, 3) == "h2 ") {
				m_font.set_size(m_font.get_size() * 1.5);
			} else if (token.m_data == "/h2") {
				m_font.set_size(m_font.get_size() / 1.5);
			} else if (token.m_data == "h3" || token.m_data.substr(0, 3) == "h3 ") {
				m_font.set_size(m_font.get_size() * 1.17);
			} else if (token.m_data == "/h3") {
				m_font.set_size(m_font.get_size() / 1.17);
			} else if (token.m_data == "h5" || token.m_data.substr(0, 3) == "h5 ") {
				m_font.set_size(m_font.get_size() * 0.83);
			} else if (token.m_data == "/h5") {
				m_font.set_size(m_font.get_size() / 0.83);
			} else if (token.m_data == "h6" || token.m_data.substr(0, 3) == "h6 ") {
				m_font.set_size(m_font.get_size() * 0.67);
			} else if (token.m_data == "/h6") {
				m_font.set_size(m_font.get_size() / 0.67);
			}
		}
	}
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

std::vector<Span*> Layout::text_to_spans(const std::string& text, const Pango::FontDescription& font) {
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

		if (word.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
			word = std::string {" "};
		}

		std::shared_ptr<Pango::Layout> pango_word {m_widget->create_pango_layout(word)};
		pango_word->set_font_description(font);
		spans.push_back(new Span {pango_word});

		start = end;
		end = break_iterator->next();
	}
	return spans;
}

void Layout::recalculate_positions() {
	Line line {m_width};
	int cursor_y {0};
	for (auto& item : m_display_list) {
		if (!line.try_add(item)) {
			int line_height = static_cast<int>(line.get_line_height() * 1.25);
			line.finalize(cursor_y); // line_height is zero after this call
			cursor_y += line_height;
			line.try_add(item); // guaranteed to work for empty lines
		}
	}
	line.finalize(cursor_y);
}

void Layout::clear_display_list() {
	for (auto& item : m_display_list) {
		delete item;
		item = nullptr;
	}
	m_display_list.clear();
}

}
