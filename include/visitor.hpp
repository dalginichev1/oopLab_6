#pragma once

#include <memory>

struct Orc;
struct Bear;
struct Squirrel;
struct NPC;

struct Visitor
{
    virtual ~Visitor() = default;

    virtual void visit(std::shared_ptr<Orc> orc, std::shared_ptr<NPC> other) = 0;
    virtual void visit(std::shared_ptr<Bear> bear, std::shared_ptr<NPC> other) = 0;
    virtual void visit(std::shared_ptr<Squirrel> squirrel, std::shared_ptr<NPC> other) = 0;
};