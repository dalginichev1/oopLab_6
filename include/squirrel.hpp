#pragma once

#include "npc.hpp"

struct Squirrel : public NPC {
    Squirrel(int x_, int y_);
    Squirrel(std::istream& is);

    bool accept(IVisitor& visitor) override;

    void print() const override;
    void save(std::ostream& os) const override;
};