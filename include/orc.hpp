#pragma once

#include "npc.hpp"

struct Orc : public NPC {
  Orc(int x_, int y_);
  Orc(std::istream &is);
  
  bool accept(IVisitor& visitor) override;
  
  void print() const override;
  void save(std::ostream &os) const override;
};