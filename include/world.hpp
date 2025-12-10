#pragma once

#include <set>
#include <memory>
#include "npc.hpp"

struct World {
  using set_t = std::set<std::shared_ptr<NPC>>;
  set_t npcs;

  void add(std::shared_ptr<NPC> npc);
  void remove(std::shared_ptr<NPC> npc);
  
  // Функция для обработки боев
  set_t fight(size_t distance);
  
  void print() const;
};