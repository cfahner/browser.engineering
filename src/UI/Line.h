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

	int get_line_height();

	void finalize();

};

}
