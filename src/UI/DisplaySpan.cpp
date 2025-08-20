/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include "DisplaySpan.h"

namespace UI {

DisplaySpan::DisplaySpan(int x, int y, Span* span)
	: m_x {x}
	, m_y {y}
	, m_span {span}
{
}

DisplaySpan::~DisplaySpan() {
	delete m_span;
	m_span = nullptr;
}

void DisplaySpan::set_position(int x, int y) {
	m_x = x;
	m_y = y;
}

}

std::ostream& operator<<(std::ostream& out, const UI::DisplaySpan& display_span) {
	return out << "DisplaySpan { "
		<< display_span.m_x << ", "
		<< display_span.m_y << ", "
		<< *display_span.m_span << " }";
}
