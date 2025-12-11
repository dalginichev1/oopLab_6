#include "world.hpp"
#include "BattleVisitor.hpp"
#include "factory.hpp"
#include <iostream>

void World::add(std::shared_ptr<NPC> npc) {
    npcs.insert(npc);
}

void World::remove(std::shared_ptr<NPC> npc) {
    npcs.erase(npc);
}

World::set_t World::fight(size_t distance) {
    set_t dead_list;

    for (auto& attacker: npcs)
    {
        try{
            auto visitor = create_visitors(attacker);

            for (auto& defender : npcs)
            {
                if ((attacker != defender) && attacker->is_close(defender, distance) && !dead_list.count(defender))
                {
                    bool success = defender->accept(*visitor);
                    if (success)
                    {
                        dead_list.insert(defender);
                    }
                }
            }
        }
        catch (const std::invalid_argument& e)
        { 
            continue;
        }
    }

    return dead_list;
}

void World::print() const {
    for (auto& n : npcs)
        n->print();
}