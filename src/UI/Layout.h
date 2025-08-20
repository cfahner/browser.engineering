/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <gtkmm/widget.h>
#include <pangomm/fontdescription.h>
#include <string>
#include <vector>

#include "../HTML/Token.h"
#include "DisplaySpan.h"

namespace UI {

class Layout {
public:
	std::vector<DisplaySpan*> m_display_list {};

private:
	Gtk::Widget* m_widget;
	Pango::FontDescription m_font {};
	int m_width {-1};
	int m_height {-1};

public:
	Layout(Gtk::Widget* widget, std::vector<HTML::Token>& tokens);
	~Layout();

	void set_width(int width);
	void set_height(int height);
	void set_size(int width, int height);

private:
	std::vector<Span*> text_to_spans(const std::string& text, const Pango::FontDescription& font);
	void recalculate_positions();
	void clear_display_list();

};

}
