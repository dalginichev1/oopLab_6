#include <iostream>
#include "world.hpp"
#include "factory.hpp"
#include "observers.hpp"

int main() {
    World w;

    auto consoleObs = std::make_shared<ConsoleObserver>();

    auto orc = NPCFactory::create(NpcType::OrcType, 10, 10);
    auto bear = NPCFactory::create(NpcType::BearType, 14, 10);
    auto squirrel = NPCFactory::create(NpcType::SquirrelType, 100, 50);

    orc->subscribe(consoleObs);
    bear->subscribe(consoleObs);
    squirrel->subscribe(consoleObs);

    w.add(orc);
    w.add(bear);
    w.add(squirrel);

    w.update(10);

    return 0;
}
