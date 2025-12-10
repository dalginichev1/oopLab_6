#pragma once

#include "npc.hpp"

struct Orc: public NPC
{
    Orc(int x, int y);
    Orc(std::istream& is);

    bool is_orc() const override;

    bool fight(std::shared_ptr<Orc> other) override;
    bool fight(std::shared_ptr<Bear> other) override;
    bool fight(std::shared_ptr<Squirrel> other) override;

    void accept(Visitor& vis, std::shared_ptr<NPC> other) override;

    void print() override;
    void save(std::ostream& os) override;
};