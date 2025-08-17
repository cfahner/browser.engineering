/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include "Span.h"

namespace UI {

Span::Span(std::shared_ptr<Pango::Layout> text_layout)
	: m_text_layout {text_layout}
{
	text_layout->get_pixel_size(m_width, m_height);
}

Span::~Span() = default;

}

std::ostream& operator<<(std::ostream& out, const UI::Span& span) {
	return out << "Span { " << span.m_width << ", " << span.m_height << " }";
}
