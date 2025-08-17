/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <memory>
#include <pangomm/layout.h>

namespace UI {

class Span {
public:
	int m_width;
	int m_height;
	std::shared_ptr<Pango::Layout> m_text_layout;

public:
	Span(std::shared_ptr<Pango::Layout> text_layout);
	~Span();

};

}

std::ostream& operator<<(std::ostream& out, const UI::Span& span);
