#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <sstream>

#include "BattleVisitor.hpp"
#include "bear.hpp"
#include "factory.hpp"
#include "npc.hpp"
#include "observer.hpp"
#include "orc.hpp"
#include "squirrel.hpp"
#include "world.hpp"

TEST(NPCCreationTest, CreateNPCs) {
    auto orc = create(OrcType, 10, 20);
    auto bear = create(BearType, 30, 40);
    auto squirrel = create(SquirrelType, 50, 60);

    EXPECT_NE(orc, nullptr);
    EXPECT_NE(bear, nullptr);
    EXPECT_NE(squirrel, nullptr);

    EXPECT_EQ(orc->type, OrcType);
    EXPECT_EQ(bear->type, BearType);
    EXPECT_EQ(squirrel->type, SquirrelType);

    EXPECT_EQ(orc->x, 10);
    EXPECT_EQ(orc->y, 20);
}

TEST(NPCSerializationTest, SaveAndLoad) {
    auto orc = create(OrcType, 10, 20);
    auto bear = create(BearType, 30, 40);
    auto squirrel = create(SquirrelType, 50, 60);

    std::stringstream ss;
    orc->save(ss);
    bear->save(ss);
    squirrel->save(ss);

    ss.seekg(0);

    auto orc2 = create(ss);
    auto bear2 = create(ss);
    auto squirrel2 = create(ss);

    EXPECT_NE(orc2, nullptr);
    EXPECT_NE(bear2, nullptr);
    EXPECT_NE(squirrel2, nullptr);

    EXPECT_EQ(orc2->type, OrcType);
    EXPECT_EQ(bear2->type, BearType);
    EXPECT_EQ(squirrel2->type, SquirrelType);
}

TEST(NPCDistanceTest, IsClose) {
    auto npc1 = create(OrcType, 0, 0);
    auto npc2 = create(OrcType, 5, 5);
    auto npc3 = create(OrcType, 20, 20);

    EXPECT_TRUE(npc1->is_close(npc2, 10));
    EXPECT_FALSE(npc1->is_close(npc2, 9));

    EXPECT_FALSE(npc1->is_close(npc3, 30));
    EXPECT_TRUE(npc1->is_close(npc3, 40));
}

TEST(WorldFightTest, FightMechanics) {
    World world;

    world.add(create(OrcType, 0, 0));
    world.add(create(BearType, 1, 1));       
    world.add(create(SquirrelType, 100, 100)); 

    auto dead_list = world.fight(10);

    EXPECT_NO_THROW(world.fight(10));
}

TEST(VisitorTest, VisitorCreation) {
    auto orc = create(OrcType, 0, 0);
    auto bear = create(BearType, 0, 0);
    auto squirrel = create(SquirrelType, 0, 0);

    EXPECT_NO_THROW(auto visitor1 = create_visitors(orc));
    EXPECT_NO_THROW(auto visitor2 = create_visitors(bear));
    EXPECT_NO_THROW(auto visitor3 = create_visitors(squirrel));

    auto orc_visitor = create_visitors(orc);
    auto bear_visitor = create_visitors(bear);
    auto squirrel_visitor = create_visitors(squirrel);

    EXPECT_NE(orc_visitor, nullptr);
    EXPECT_NE(bear_visitor, nullptr);
    EXPECT_NE(squirrel_visitor, nullptr);
}

TEST(ObserverTest, ObserverSubscription) {
    auto npc = create(OrcType, 0, 0);

    auto text_observer = TextObserver::get();
    auto file_observer = FileObserver::get();

    EXPECT_NE(text_observer, nullptr);
    EXPECT_NE(file_observer, nullptr);

    auto defender = create(BearType, 1, 1);
    EXPECT_NO_THROW(npc->fight_notify(defender, true));
}

TEST(WorldRemoveTest, RemoveNPC) {
    World world;

    auto npc1 = create(OrcType, 0, 0);
    auto npc2 = create(BearType, 10, 10);

    world.add(npc1);
    world.add(npc2);

    EXPECT_EQ(world.npcs.size(), 2);

    world.remove(npc1);
    EXPECT_EQ(world.npcs.size(), 1);

    world.remove(npc2);
    EXPECT_EQ(world.npcs.size(), 0);
}

TEST(AcceptMethodTest, AcceptVisitor) {
    auto orc = std::make_shared<Orc>(0, 0);
    auto bear = std::make_shared<Bear>(0, 0);
    auto squirrel = std::make_shared<Squirrel>(0, 0);

    auto orc_visitor = std::make_unique<OrcVisitor>(orc);
    auto bear_visitor = std::make_unique<BearVisitor>(bear);
    auto squirrel_visitor = std::make_unique<SquirrelVisitor>(squirrel);

    EXPECT_NO_THROW(orc->accept(*orc_visitor));
    EXPECT_NO_THROW(bear->accept(*bear_visitor));
    EXPECT_NO_THROW(squirrel->accept(*squirrel_visitor));
}

TEST(FileLoadTest, LoadFromFile) {
    World world;
    world.add(create(OrcType, 10, 20));
    world.add(create(BearType, 30, 40));
    world.add(create(SquirrelType, 50, 60));

    std::stringstream ss;
    ss << world.npcs.size() << std::endl;
    for (auto& n : world.npcs) {
        n->save(ss);
    }

    ss.seekg(0);
    int count;
    ss >> count;

    World loadedWorld;
    for (int i = 0; i < count; ++i) {
        loadedWorld.add(create(ss));
    }

    EXPECT_EQ(loadedWorld.npcs.size(), world.npcs.size());
}

TEST(BattleLogicTest, SpecificBattles) {
    std::srand(42); 

    auto orc = std::make_shared<Orc>(0, 0);
    auto bear = std::make_shared<Bear>(1, 1);
    auto squirrel = std::make_shared<Squirrel>(2, 2);

    auto orc_visitor = std::make_unique<OrcVisitor>(orc);
    auto bear_visitor = std::make_unique<BearVisitor>(bear);
    auto squirrel_visitor = std::make_unique<SquirrelVisitor>(squirrel);

    bool orc_vs_bear = orc_visitor->visit(*bear);
    EXPECT_TRUE(orc_vs_bear);

    bool bear_vs_orc = bear_visitor->visit(*orc);
    EXPECT_FALSE(bear_vs_orc);

    bool squirrel_vs_bear = squirrel_visitor->visit(*bear);
    EXPECT_FALSE(squirrel_vs_bear);
}