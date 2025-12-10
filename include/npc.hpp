#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <set>
#include <vector>
#include <cmath>

struct Visitor;

struct NPC;
struct Orc;
struct Bear;
struct Squirrel;

enum class NpcType
{
    Unknown = 0,
    OrcType = 1,
    BearType = 2,
    SquirrelType = 3
};

struct IFightObserver
{
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

struct NPC: std::enable_shared_from_this<NPC>
{
    NpcType type{NpcType::Unknown};
    int x = 0;
    int y = 0;

    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int x0, int y0);
    NPC(NpcType t, std::istream& is);

    void subscribe(std::shared_ptr<IFightObserver> obs);
    void fight_notify(std::shared_ptr<NPC> defender, bool win);

    bool is_close(const std::shared_ptr<NPC>& other, size_t distance) const;

    virtual bool is_orc() const;
    virtual bool is_bear() const;
    virtual bool is_squirrel() const;

    virtual bool fight(std::shared_ptr<Orc> other) = 0;
    virtual bool fight(std::shared_ptr<Bear> other) = 0;
    virtual bool fight(std::shared_ptr<Squirrel> other) = 0;

    virtual void accept(Visitor& vis, std::shared_ptr<NPC> other) = 0;

    virtual void print();
    virtual void save(std::ostream& os);

    friend std::ostream& operator<<(std::ostream& os, NPC& npc);
};