// squirrel.cpp
#include "squirrel.hpp"
#include "orc.hpp"
#include "bear.hpp"
#include <memory>

Squirrel::Squirrel(int x_, int y_) : NPC(SquirrelType, x_, y_) {}
Squirrel::Squirrel(std::istream &is) : NPC(SquirrelType, is) {}

bool Squirrel::accept(const std::shared_ptr<NPC> &attacker) {
  return attacker->visit_squirrel(std::static_pointer_cast<Squirrel>(shared_from_this()));
}

bool Squirrel::visit_orc(const std::shared_ptr<Orc> &defender) {
  bool win = false;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

bool Squirrel::visit_bear(const std::shared_ptr<Bear> &defender) {
  bool win = false;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

bool Squirrel::visit_squirrel(const std::shared_ptr<Squirrel> &defender) {
  bool win = rand() % 2;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

void Squirrel::print() const { 
  std::cout << "Squirrel at (" << x << ", " << y << ")" << std::endl; 
}

void Squirrel::save(std::ostream &os) const {
  os << SquirrelType << std::endl;
  os << x << " " << y << std::endl;
}