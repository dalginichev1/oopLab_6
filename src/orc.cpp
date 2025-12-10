// orc.cpp
#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include <memory>

Orc::Orc(int x_, int y_) : NPC(OrcType, x_, y_) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

bool Orc::accept(const std::shared_ptr<NPC> &attacker) {
  return attacker->visit_orc(std::static_pointer_cast<Orc>(shared_from_this()));
}

bool Orc::visit_orc(const std::shared_ptr<Orc> &defender) {
  bool win = rand() % 2;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

bool Orc::visit_bear(const std::shared_ptr<Bear> &defender) {
  bool win = true;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

bool Orc::visit_squirrel(const std::shared_ptr<Squirrel> &defender) {
  bool win = true;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

void Orc::print() const { 
  std::cout << "Orc at (" << x << ", " << y << ")" << std::endl; 
}

void Orc::save(std::ostream &os) const {
  os << OrcType << std::endl;
  os << x << " " << y << std::endl;
}