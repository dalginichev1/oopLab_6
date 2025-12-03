#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include "visitor.hpp"

Squirrel::Squirrel(int x, int y): NPC(NpcType::SquirrelType, x, y) {}
Squirrel::Squirrel(std::istream& is): NPC(NpcType::SquirrelType, is) {}

bool Squirrel::is_squirrel() const {return true;}

bool Squirrel::fight(std::shared_ptr<Squirrel> other)
{
    bool win = rand() % 2;
    fight_notify(other, win);
    return win;
}

bool Squirrel::fight(std::shared_ptr<Bear> other)
{
    bool win = false;
    fight_notify(other, win);
    return win;
}

bool Squirrel::fight(std::shared_ptr<Orc> other)
{
    bool win = false;
    fight_notify(other, win);
    return win;
}

void Squirrel::accept(Visitor& vis, std::shared_ptr<NPC> other)
{
    vis.visit(std::static_pointer_cast<Squirrel>(shared_from_this()), other);
}

void Squirrel::print()
{
    std::cout << "Squirrel at (" << x << " , " << y << ")";
}

void Squirrel::save(std::ostream& os)
{
    os << (int)type << " " << x << " " << y << "\n";
}