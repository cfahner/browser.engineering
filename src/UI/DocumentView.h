/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <gtkmm/drawingarea.h>
#include <string>
#include <vector>

#include "../HTML/Parser.h"
#include "DisplaySpan.h"

namespace UI {

class DocumentView : public Gtk::DrawingArea {
private:
	HTML::Parser m_parser {};
	std::vector<HTML::Token>* m_token_list {};
	bool m_layout_needed {false};
	std::vector<DisplaySpan*> m_display_list {};
	int m_scroll {0};

public:
	DocumentView();
	~DocumentView();
	void display_html(std::string& html);
	void scroll(int delta);

protected:
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
	void on_resize(int width, int height) override;

private:
	void layout();
	std::vector<Span*> text_to_spans(const std::string& text, const Pango::FontDescription font);
	void clear_display_list();

};

}
