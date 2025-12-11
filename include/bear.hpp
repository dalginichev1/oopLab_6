#pragma once

#include "npc.hpp"

struct Bear : public NPC {
    Bear(int x_, int y_);
    Bear(std::istream& is);

    bool accept(IVisitor& visitor) override;

    void print() const override;
    void save(std::ostream& os) const override;
};