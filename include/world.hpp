#pragma once

#include <set>
#include <memory>
#include "npc.hpp"
#include "battle_visitor.hpp"

struct World
{
    using set_t = std::set<std::shared_ptr<NPC>>;

    set_t npcs;

    void add(std::shared_ptr<NPC> npc);
    void remove(std::shared_ptr<NPC> npc);
    void update(size_t fight_distance);
};