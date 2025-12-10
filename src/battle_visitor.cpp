#include "battle_visitor.hpp"
#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"

void BattleVisitor::visit(std::shared_ptr<Orc> orc, std::shared_ptr<NPC> other)
{
    if (other->is_orc()) orc->fight(std::static_pointer_cast<Orc>(other));
    else if (other->is_bear()) orc->fight(std::static_pointer_cast<Bear>(other));
    else if (other->is_squirrel()) orc->fight(std::static_pointer_cast<Squirrel>(other));
}

void BattleVisitor::visit(std::shared_ptr<Bear> bear, std::shared_ptr<NPC> other)
{
    if (other->is_orc()) bear->fight(std::static_pointer_cast<Orc>(other));
    else if (other->is_bear()) bear->fight(std::static_pointer_cast<Bear>(other));
    else if (other->is_squirrel()) bear->fight(std::static_pointer_cast<Squirrel>(other));
}

void BattleVisitor::visit(std::shared_ptr<Squirrel> squirrel, std::shared_ptr<NPC> other)
{
    if (other->is_orc()) squirrel->fight(std::static_pointer_cast<Orc>(other));
    else if (other->is_bear()) squirrel->fight(std::static_pointer_cast<Bear>(other));
    else if (other->is_squirrel()) squirrel->fight(std::static_pointer_cast<Squirrel>(other));
}