/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <gtkmm/drawingarea.h>

namespace UI {

class DocumentView : public Gtk::DrawingArea {
public:
	DocumentView();
	~DocumentView();

protected:
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

};

}
