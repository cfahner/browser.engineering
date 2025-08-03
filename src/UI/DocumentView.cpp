/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <cairomm/context.h>
#include <iostream>

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

void DocumentView::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
	std::cout << "on_draw" << std::endl;
	cr->set_line_width(10.0);
	cr->set_source_rgb(1.0, 0.0, 0.0);
	cr->move_to(0, 0);
	cr->line_to(width / 2, height / 2);
	cr->stroke();
}

}
