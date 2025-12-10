#pragma once

#include <memory>
#include "npc.hpp"
#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"

struct NPCFactory
{
    static std::shared_ptr<NPC> create(NpcType T, int x, int y);
};