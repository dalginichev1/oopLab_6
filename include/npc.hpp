#pragma once

#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

struct Orc;
struct Bear;
struct Squirrel;
struct IVisitor;

enum NpcType { UnknownType = 0, OrcType = 1, BearType = 2, SquirrelType = 3 };

struct NPC;

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC>& attacker,
                          const std::shared_ptr<NPC>& defender, bool win) = 0;
    virtual ~IFightObserver() = default;
};

struct NPC : public std::enable_shared_from_this<NPC> {
    int x{0};
    int y{0};
    NpcType type{UnknownType};
    std::vector<std::shared_ptr<IFightObserver>> observers;

    NPC(NpcType t, int x_, int y_);
    NPC(NpcType t, std::istream& is);
    virtual ~NPC() = default;

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC>& defender, bool win);
    bool is_close(const std::shared_ptr<NPC>& other, size_t distance) const;

    virtual bool accept(IVisitor& visitor) = 0;

    virtual void print() const = 0;
    virtual void save(std::ostream& os) const;

    friend std::ostream& operator<<(std::ostream& os, const NPC& npc);
};