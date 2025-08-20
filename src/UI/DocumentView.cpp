/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

#include "DocumentView.h"

namespace UI {

DocumentView::DocumentView() {
	set_draw_func(sigc::mem_fun(*this, &DocumentView::on_draw));
}

DocumentView::~DocumentView() = default;

void DocumentView::display_html(std::string& html) {
	std::vector<HTML::Token>* tokens {m_parser.lex(html)};
	delete m_layout;
	m_layout = new Layout {this, *tokens};
	delete tokens;
	queue_draw();
}

void DocumentView::scroll(int delta) {
	m_scroll += delta;
	if (m_scroll < 0) {
		m_scroll = 0;
	}
	queue_draw();
}

void DocumentView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
	if (m_layout != nullptr) {
		m_layout->set_size(width, height);
	}

	auto fn_start = std::chrono::high_resolution_clock::now();

	for (auto& item : m_layout->m_display_list) {
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
	queue_draw();
}

}
