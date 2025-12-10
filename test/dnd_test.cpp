#include <gtest/gtest.h>
#include <fstream>

#include "npc.hpp"
#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"
#include "factory.hpp"
#include "world.hpp"
#include "observers.hpp"
#include "battle_visitor.hpp"

TEST(NPC, CreateOrc)
{
    auto o = std::make_shared<Orc>(10, 20);

    EXPECT_TRUE(o->is_orc());
    EXPECT_FALSE(o->is_bear());
    EXPECT_FALSE(o->is_squirrel());

    EXPECT_EQ(o->x, 10);
    EXPECT_EQ(o->y, 20);
}

TEST(NPC, DistanceCheck)
{
    auto o1 = std::make_shared<Orc>(0, 0);
    auto o2 = std::make_shared<Orc>(3, 3);

    EXPECT_TRUE(o1->is_close(o2, 10));
    EXPECT_FALSE(o1->is_close(o2, 3)); 
}

TEST(NPCFactory, Create)
{
    auto o = NPCFactory::create(NpcType::OrcType, 1, 2);
    auto b = NPCFactory::create(NpcType::BearType, 3, 4);
    auto s = NPCFactory::create(NpcType::SquirrelType, 5, 6);

    EXPECT_TRUE(o->is_orc());
    EXPECT_TRUE(b->is_bear());
    EXPECT_TRUE(s->is_squirrel());
}

TEST(Observer, FileObserverLogging)
{
    {
        std::ofstream clear("log.txt");
        clear << "";
    }

    auto orc = std::make_shared<Orc>(10, 10);
    auto bear = std::make_shared<Bear>(11, 10);

    auto fileObs = std::make_shared<FileObserver>();
    orc->subscribe(fileObs);

    orc->fight(bear);

    std::ifstream in("log.txt");
    ASSERT_TRUE(in.is_open());

    std::string line;
    std::getline(in, line);

    EXPECT_NE(line.find("Fight:"), std::string::npos);
}

TEST(Visitor, BattleVisitorCallsFight)
{
    auto o = std::make_shared<Orc>(0, 0);
    auto b = std::make_shared<Bear>(0, 1);

    auto obs = std::make_shared<ConsoleObserver>();
    o->subscribe(obs);

    BattleVisitor v;

    o->accept(v, b);

    SUCCEED(); 
}

TEST(World, UpdateTriggersVisitor)
{
    World w;

    auto o = std::make_shared<Orc>(10, 10);
    auto b = std::make_shared<Bear>(11, 10);

    auto obs = std::make_shared<ConsoleObserver>();
    o->subscribe(obs);

    w.add(o);
    w.add(b);

    w.update(5);

    SUCCEED();
}
