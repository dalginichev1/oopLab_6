#include "orc.hpp"
#include "BattleVisitor.hpp"
#include <memory>

Orc::Orc(int x_, int y_) : NPC(OrcType, x_, y_) {}
Orc::Orc(std::istream &is) : NPC(OrcType, is) {}

bool Orc::accept(IVisitor& visitor) {
  return visitor.visit(*this);
}

void Orc::print() const { 
  std::cout << "Orc at (" << x << ", " << y << ")" << std::endl; 
}

void Orc::save(std::ostream &os) const {
  os << OrcType << std::endl;
  os << x << " " << y << std::endl;
}