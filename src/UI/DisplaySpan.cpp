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

}
