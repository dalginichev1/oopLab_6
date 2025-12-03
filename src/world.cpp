#include "world.hpp"

void World::add(std::shared_ptr<NPC> npc)
{
    npcs.insert(npc);
}

void World::remove(std::shared_ptr<NPC> npc)
{
    npcs.erase(npc);
}

void World::update(size_t fight_distance)
{
    BattleVisitor visitor;

    std::vector<std::shared_ptr<NPC>> dead;

    for (auto& a: npcs)
    {
        for (auto& b: npcs)
        {
            if (a != b && a->is_close(b, fight_distance))
            {
                a->accept(visitor, b);
            }
        }
    }
}