/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <vector>

#include "DisplaySpan.h"

namespace UI {

class Line {
private:
	int m_width;
	std::vector<DisplaySpan*> m_display_spans {};

public:
	Line(int width);
	~Line();

	/**
	 * Tries to add a display span to this line.
	 * @return `TRUE` if it was added, `FALSE` if the line is full
	 */
	bool try_add(DisplaySpan* display_span);

	/** Returns the line height in pixels */
	int get_line_height();

	/** Returns the baseline from the top of the line in pixels */
	int get_baseline();

	/**
	 * Aligns all items in the line along the baseline and clears the line
	 * @param cursor_y The y-position of the top of the line
	 */
	void finalize(int cursor_y);

};

}
