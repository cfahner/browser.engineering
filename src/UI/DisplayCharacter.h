/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <iostream>
#include <memory>
#include <pangomm/layout.h>
#include <stdint.h>

namespace UI {

struct DisplayCharacter {
	int m_x;
	int m_y;
	std::shared_ptr<Pango::Layout> m_text_layout;
};

}

std::ostream& operator<<(std::ostream& out, const UI::DisplayCharacter& display_character);
