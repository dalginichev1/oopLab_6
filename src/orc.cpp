#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include "visitor.hpp"

Orc::Orc(int x, int y): NPC(NpcType::OrcType, x, y) {}
Orc::Orc(std::istream& is): NPC(NpcType::OrcType, is) {}

bool Orc::is_orc() const {return true;}

bool Orc::fight(std::shared_ptr<Orc> other)
{
    bool win = rand() % 2;
    fight_notify(other, win);
    return win;
}

bool Orc::fight(std::shared_ptr<Bear> other)
{
    bool win = true;
    fight_notify(other, win);
    return win;
}

bool Orc::fight(std::shared_ptr<Squirrel> other)
{
    bool win = true;
    fight_notify(other, win);
    return win;
}

void Orc::accept(Visitor& vis, std::shared_ptr<NPC> other)
{
    vis.visit(std::static_pointer_cast<Orc>(shared_from_this()), other);
}

void Orc::print()
{
    std::cout << "Orc at (" << x << " , " << y << ")";
}

void Orc::save(std::ostream& os)
{
    os << (int)type << " " << x << " " << y << "\n";
}