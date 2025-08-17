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
#include "Layout.h"

namespace UI {

class DocumentView : public Gtk::DrawingArea {
private:
	HTML::Parser m_parser {};
	Layout* m_layout {nullptr};
	int m_scroll {0};

public:
	DocumentView();
	~DocumentView();
	void display_html(std::string& html);
	void scroll(int delta);

protected:
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);
	void on_resize(int width, int height) override;

};

}
