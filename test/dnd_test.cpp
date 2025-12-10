#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include <memory>

#include "factory.hpp"
#include "world.hpp"
#include "orc.hpp"
#include "bear.hpp"
#include "squirrel.hpp"

// ==================== Тесты NPC ====================
TEST(NPCTest, ConstructionAndDistance) {
    auto orc = std::make_shared<Orc>(10, 20);
    EXPECT_EQ(orc->x, 10);
    EXPECT_EQ(orc->y, 20);
    EXPECT_EQ(orc->type, OrcType);
    
    auto bear = std::make_shared<Bear>(12, 22);
    EXPECT_TRUE(orc->is_close(bear, 10));  // |10-12|+|20-22| = 4 <= 10
    
    auto far_npc = std::make_shared<Squirrel>(50, 60);
    EXPECT_FALSE(orc->is_close(far_npc, 10));
}

// ==================== Тесты боевых взаимодействий ====================
TEST(FightTest, BasicFightRules) {
    // Орк всегда побеждает медведя
    auto orc = std::make_shared<Orc>(0, 0);
    auto bear = std::make_shared<Bear>(1, 1);
    EXPECT_TRUE(bear->accept(orc));
    
    // Орк всегда побеждает белку
    auto squirrel = std::make_shared<Squirrel>(2, 2);
    EXPECT_TRUE(squirrel->accept(orc));
    
    // Белка никогда не побеждает орка
    EXPECT_FALSE(orc->accept(squirrel));
    
    // Медведь всегда побеждает белку
    EXPECT_TRUE(squirrel->accept(bear));
}

TEST(FightTest, SameTypeRandom) {
    auto orc1 = std::make_shared<Orc>(0, 0);
    auto orc2 = std::make_shared<Orc>(1, 1);
    
    // Орк против орка - случайный результат
    // Проверяем что функция работает (не падает)
    bool result = orc2->accept(orc1);
    // Должно быть либо true, либо false, но не падать
    EXPECT_TRUE(result == true || result == false);
}

// ==================== Тесты Factory ====================
TEST(FactoryTest, CreateAllTypes) {
    auto orc = factory(OrcType, 10, 20);
    EXPECT_NE(orc, nullptr);
    EXPECT_EQ(orc->type, OrcType);
    
    auto bear = factory(BearType, 30, 40);
    EXPECT_NE(bear, nullptr);
    EXPECT_EQ(bear->type, BearType);
    
    auto squirrel = factory(SquirrelType, 50, 60);
    EXPECT_NE(squirrel, nullptr);
    EXPECT_EQ(squirrel->type, SquirrelType);
    
    auto unknown = factory(static_cast<NpcType>(999), 0, 0);
    EXPECT_EQ(unknown, nullptr);
}

TEST(FactoryTest, CreateFromStream) {
    std::stringstream ss("1 100 200");  // Orc
    auto orc = factory(ss);
    EXPECT_NE(orc, nullptr);
    EXPECT_EQ(orc->x, 100);
    EXPECT_EQ(orc->y, 200);
    
    // Неверный тип
    std::stringstream ss_bad("999 0 0");
    auto bad = factory(ss_bad);
    EXPECT_EQ(bad, nullptr);
}

// ==================== Тесты World ====================
TEST(WorldTest, AddRemoveAndFight) {
    World world;
    
    // Добавляем NPC
    auto orc = std::make_shared<Orc>(0, 0);
    auto squirrel = std::make_shared<Squirrel>(2, 2);  // Близко к орку
    
    world.add(orc);
    world.add(squirrel);
    EXPECT_EQ(world.npcs.size(), 2);
    
    // Бой на небольшой дистанции - белка должна погибнуть
    auto dead = world.fight(10);
    EXPECT_EQ(dead.size(), 1);
    EXPECT_TRUE(dead.find(squirrel) != dead.end());
    
    // Удаляем убитых
    for (auto& d : dead) {
        world.remove(d);
    }
    EXPECT_EQ(world.npcs.size(), 1);
}

TEST(WorldTest, NoFightWhenFar) {
    World world;
    
    auto orc = std::make_shared<Orc>(0, 0);
    auto squirrel = std::make_shared<Squirrel>(100, 100);  // Далеко
    
    world.add(orc);
    world.add(squirrel);
    
    // На расстоянии 10 не должны сражаться
    auto dead = world.fight(10);
    EXPECT_EQ(dead.size(), 0);
}

// ==================== Тесты сохранения ====================
TEST(SaveTest, SaveAndLoadNPC) {
    // Тест сохранения NPC
    auto orc = std::make_shared<Orc>(123, 456);
    std::stringstream ss;
    orc->save(ss);
    
    int type, x, y;
    ss >> type >> x >> y;
    
    EXPECT_EQ(type, OrcType);
    EXPECT_EQ(x, 123);
    EXPECT_EQ(y, 456);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}