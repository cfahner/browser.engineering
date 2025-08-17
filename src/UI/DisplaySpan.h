/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include "Span.h"

namespace UI {

class DisplaySpan {
public:
	int m_x;
	int m_y;
	Span* m_span;

public:
	DisplaySpan(int x, int y, Span* span);
	~DisplaySpan();

	void set_position(int x, int y);

};

}
