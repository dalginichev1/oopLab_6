#pragma once

#include "npc.hpp"

struct Bear : public NPC {
    Bear(int x_, int y_);
    Bear(std::istream& is);

    bool accept(const std::shared_ptr<NPC>& attacker) override;
    bool visit_orc(const std::shared_ptr<Orc>& defender) override;
    bool visit_bear(const std::shared_ptr<Bear>& defender) override;
    bool visit_squirrel(const std::shared_ptr<Squirrel>& defender) override;

    void print() const override;
    void save(std::ostream& os) const override;
};