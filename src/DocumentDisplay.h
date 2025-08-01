/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <gtkmm/drawingarea.h>

class DocumentDisplay : public Gtk::DrawingArea {
public:
	DocumentDisplay();
	~DocumentDisplay();

protected:
	void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height);

};
