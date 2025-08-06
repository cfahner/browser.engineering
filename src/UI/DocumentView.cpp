/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cairomm/context.h>
#include <cassert>
#include <string>
#include <unicode/brkiter.h>

#include "DocumentView.h"

namespace UI {

DocumentView::DocumentView() {
	set_draw_func(sigc::mem_fun(*this, &DocumentView::on_draw));
}

DocumentView::~DocumentView() = default;

void DocumentView::display_html(std::string& html) {
	m_text_to_draw = m_parser.lex(html);
	queue_draw();
}

// https://gnome.pages.gitlab.gnome.org/gtkmm-documentation/sec-drawing-text.html
void DocumentView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, [[maybe_unused]] int height) {
	Pango::FontDescription font{};
	font.set_family("Monospace");
	font.set_weight(Pango::Weight::BOLD);

	icu::UnicodeString unicode_text{icu::UnicodeString::fromUTF8(icu::StringPiece{m_text_to_draw.c_str()})};

	UErrorCode u_error{U_ZERO_ERROR};
	std::unique_ptr<icu::BreakIterator> break_iterator{
		icu::BreakIterator::createCharacterInstance(icu::Locale::getDefault(), u_error)
	};
	assert(U_SUCCESS(u_error));
	break_iterator->setText(unicode_text);

	int cursor_h = 0;
	int cursor_v = 0;
	int line_height = 20;

	int32_t start = break_iterator->first();
	int32_t end = break_iterator->next();
	while (end != icu::BreakIterator::DONE) {
		icu::UnicodeString unicode_char{unicode_text, start, end - start};

		std::string std_string;
		unicode_char.toUTF8String(std_string);

		auto layout = create_pango_layout(std_string);
		layout->set_font_description(font);

		int text_width;
		int text_height;
		layout->get_pixel_size(text_width, text_height);

		cr->move_to(cursor_h, cursor_v);
		layout->show_in_cairo_context(cr);
		cursor_h += text_width;
		if (cursor_h > width) {
			cursor_h = 0;
			cursor_v += line_height;
		}

		start = end;
		end = break_iterator->next();
	}
}

}
