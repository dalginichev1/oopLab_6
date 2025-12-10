#pragma once

#include "npc.hpp"

std::shared_ptr<NPC> factory(NpcType type, int x, int y);
std::shared_ptr<NPC> factory(std::istream &is);