/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include "Line.h"
#include <iostream>
namespace UI {

Line::Line(int width)
	: m_width {width}
{
}

Line::~Line() = default;

bool Line::try_add(DisplaySpan* display_span) {
	// always allow at least one item on a line (which is allowed to overflow the desired width)
	if (m_display_spans.empty()) {
		display_span->m_x = 0;
		m_display_spans.push_back(display_span);
		return true;
	}
	DisplaySpan* end_span = m_display_spans.back();
	int end_x = end_span->m_x + end_span->m_span->m_width;
	if (end_x + display_span->m_span->m_width > m_width) {
		return false;
	}
	display_span->m_x = end_x;
	m_display_spans.push_back(display_span);
	return true;
}

int Line::get_line_height() {
	int max = 0;
	for (auto& display_span : m_display_spans) {
		if (display_span->m_span->m_height > max) {
			max = display_span->m_span->m_height;
		}
	}
	return max;
}

void Line::finalize() {
	m_display_spans.clear();
}

}
