#include "npc.hpp"

NPC::NPC(NpcType t, int x_, int y_) : type(t), x(x_), y(y_) {}

NPC::NPC(NpcType t, std::istream &is) : type(t) {
  is >> x >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer) {
  observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> &defender, bool win) {
  for (auto &o : observers)
    if (o)
      o->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const {
  return (std::abs(x - other->x) + std::abs(y - other->y)) <= static_cast<int>(distance);
}

void NPC::save(std::ostream &os) const {
  os << x << " " << y;
}

std::ostream &operator<<(std::ostream &os, const NPC &npc) {
  os << "(" << npc.x << ", " << npc.y << ")";
  return os;
}