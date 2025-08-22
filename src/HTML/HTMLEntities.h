/* Copyright (c) 2025, C. Fahner
 * MIT License
 */
#pragma once

#include <string>

namespace HTML::HTMLEntities {

/** @param entity_name The "name" part of an entity, i.e. `amp` or `#38` would decode to `&` */
std::string decode_entity(std::string& entity_name);

std::string decode_entity(int entity_number);

}
