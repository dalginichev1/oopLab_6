#include "world.hpp"

#include <iostream>

void World::add(std::shared_ptr<NPC> npc) {
    npcs.insert(npc);
}

void World::remove(std::shared_ptr<NPC> npc) {
    npcs.erase(npc);
}

World::set_t World::fight(size_t distance) {
    set_t dead_list;

    for (const auto& attacker : npcs) {
        for (const auto& defender : npcs) {
            if ((attacker != defender) && attacker->is_close(defender, distance) &&
                !dead_list.count(defender)) {

                bool success = defender->accept(attacker);
                if (success) {
                    dead_list.insert(defender);
                }
            }
        }
    }

    return dead_list;
}

void World::print() const {
    for (auto& n : npcs)
        n->print();
}