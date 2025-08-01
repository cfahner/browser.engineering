/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include <iostream>
#include <cairomm/context.h>

#include "DocumentDisplay.h"

DocumentDisplay::DocumentDisplay() {
	set_draw_func(sigc::mem_fun(*this, &DocumentDisplay::on_draw));
}

DocumentDisplay::~DocumentDisplay() = default;

void DocumentDisplay::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height) {
	cr->set_line_width(10.0);
	cr->set_source_rgb(1.0, 0.0, 0.0);
	cr->move_to(0, 0);
	cr->line_to(width / 2, height / 2);
	cr->stroke();
}
