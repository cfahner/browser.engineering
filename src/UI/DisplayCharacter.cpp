/*
 * Copyright (c) 2025, C. Fahner
 * MIT License
 */
#include "DisplayCharacter.h"

std::ostream& operator<<(std::ostream& out, const UI::DisplayCharacter& display_character) {
	return out << "DisplayCharacter { " << display_character.m_x << ", " << display_character.m_y << " }";
}
