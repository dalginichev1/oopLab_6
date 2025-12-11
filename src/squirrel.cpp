#include "squirrel.hpp"
#include "BattleVisitor.hpp"
#include <memory>

Squirrel::Squirrel(int x_, int y_) : NPC(SquirrelType, x_, y_) {}
Squirrel::Squirrel(std::istream &is) : NPC(SquirrelType, is) {}

bool Squirrel::accept(IVisitor& visitor) {
  return visitor.visit(*this);
}

void Squirrel::print() const { 
  std::cout << "Squirrel at (" << x << ", " << y << ")" << std::endl; 
}

void Squirrel::save(std::ostream &os) const {
  os << SquirrelType << std::endl;
  os << x << " " << y << std::endl;
}