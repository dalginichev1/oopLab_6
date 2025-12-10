#pragma once

#include "npc.hpp"

struct Bear: public NPC
{
    Bear(int x, int y);
    Bear(std::istream& is);

    bool is_bear() const override;

    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;

    void accept(Visitor& vis, std::shared_ptr<NPC> other) override;

    void print() override;
    void save(std::ostream& os) override;
};