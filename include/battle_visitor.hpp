#pragma once

#include "visitor.hpp"

struct BattleVisitor: public Visitor
{
    virtual void visit(std::shared_ptr<Orc> orc, std::shared_ptr<NPC> other) override;
    virtual void visit(std::shared_ptr<Bear> bear, std::shared_ptr<NPC> other) override;
    virtual void visit(std::shared_ptr<Squirrel> squirrel, std::shared_ptr<NPC> other) override;
};