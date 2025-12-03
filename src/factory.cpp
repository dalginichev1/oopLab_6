#include "factory.hpp"

std::shared_ptr<NPC> NPCFactory::create(NpcType t, int x, int y)
{
    switch (t)
    {
        case NpcType::OrcType:
            return std::make_shared<Orc>(x, y);
        case NpcType::BearType:
            return std::make_shared<Bear>(x, y);
        case NpcType::SquirrelType:
            return std::make_shared<Squirrel>(x, y);
        default: return nullptr;
    }
}