// bear.cpp
#include "bear.hpp"
#include "orc.hpp"
#include "squirrel.hpp"
#include <memory>

Bear::Bear(int x_, int y_) : NPC(BearType, x_, y_) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

bool Bear::accept(const std::shared_ptr<NPC> &attacker) {
  return attacker->visit_bear(std::static_pointer_cast<Bear>(shared_from_this()));
}

bool Bear::visit_orc(const std::shared_ptr<Orc> &defender) {
  bool win = false;
  // Явное преобразование к базовому типу
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

bool Bear::visit_bear(const std::shared_ptr<Bear> &defender) {
  bool win = rand() % 2;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

bool Bear::visit_squirrel(const std::shared_ptr<Squirrel> &defender) {
  bool win = true;
  std::shared_ptr<NPC> npc_defender = std::static_pointer_cast<NPC>(defender);
  fight_notify(npc_defender, win);
  return win;
}

void Bear::print() const { 
  std::cout << "Bear at (" << x << ", " << y << ")" << std::endl; 
}

void Bear::save(std::ostream &os) const {
  os << BearType << std::endl;
  os << x << " " << y << std::endl;
}