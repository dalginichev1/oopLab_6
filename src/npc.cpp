#include "npc.hpp"
#include "visitor.hpp"

NPC::NPC(NpcType t, int x0, int y0)
    : type(t), x(x0), y(y0) {}

NPC::NPC(NpcType t, std::istream& is): type(t)
{
    is >> x >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> obs)
{
    observers.push_back(obs);
}

void NPC::fight_notify(std::shared_ptr<NPC> defender, bool win)
{
    for (auto& obs: observers) obs->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC>& other, size_t distance) const
{
    return (std::abs(x - other->x) + std::abs(y - other->y)) <= (int) distance;
}

bool NPC::is_orc() const {return false;}
bool NPC::is_bear() const {return false;}
bool NPC::is_squirrel() const {return false;}

void NPC::print()
{
    std::cout << "NPC at (" << x << " , " << y << ")";
}

void NPC::save(std::ostream& os)
{
    os << (int)type << " " << x << " " << y << "\n";
}

std::ostream& operator<<(std::ostream& os, NPC& npc)
{
    npc.print();
    return os;
}

