#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include "visitor.hpp"

Bear::Bear(int x, int y): NPC(NpcType::BearType, x, y) {}
Bear::Bear(std::istream& is): NPC(NpcType::BearType, is) {}

bool Bear::is_bear() const {return true;}

bool Bear::fight(std::shared_ptr<Bear> other)
{
    bool win = rand() % 2;
    fight_notify(other, win);
    return win;
}

bool Bear::fight(std::shared_ptr<Orc> other)
{
    bool win = false;
    fight_notify(other, win);
    return win;
}

bool Bear::fight(std::shared_ptr<Squirrel> other)
{
    bool win = true;
    fight_notify(other, win);
    return win;
}

void Bear::accept(Visitor& vis, std::shared_ptr<NPC> other)
{
    vis.visit(std::static_pointer_cast<Bear>(shared_from_this()), other);
}

void Bear::print()
{
    std::cout << "Bear at (" << x << " , " << y << ")";
}

void Bear::save(std::ostream& os)
{
    os << (int)type << " " << x << " " << y << "\n";
}