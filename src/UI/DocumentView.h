/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <gtkmm/drawingarea.h>
#include <string>

#include "../HTML/Parser.h"

namespace UI {

class DocumentView : public Gtk::DrawingArea {
private:
	HTML::Parser m_parser{};
	std::string m_text_to_draw{};

public:
	DocumentView();
	~DocumentView();
	void display_html(std::string& html);

protected:
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

};

}
