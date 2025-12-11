#include "bear.hpp"
#include "BattleVisitor.hpp"
#include <memory>

Bear::Bear(int x_, int y_) : NPC(BearType, x_, y_) {}
Bear::Bear(std::istream &is) : NPC(BearType, is) {}

bool Bear::accept(IVisitor& visitor) {
  return visitor.visit(*this);
}

void Bear::print() const { 
  std::cout << "Bear at (" << x << ", " << y << ")" << std::endl; 
}

void Bear::save(std::ostream &os) const {
  os << BearType << std::endl;
  os << x << " " << y << std::endl;
}