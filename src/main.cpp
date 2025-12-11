#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>

#include "factory.hpp"
#include "world.hpp"

using set_t = std::set<std::shared_ptr<NPC>>;

void save(const set_t& array, const std::string& filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto& n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string& filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(create(is));
        is.close();
    } else {
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    }
    return result;
}

int main() {
    std::srand(std::time(0));
    World world;

    std::cout << "Generating NPCs..." << std::endl;
    for (size_t i = 0; i < 10; ++i) {
        auto type = static_cast<NpcType>(std::rand() % 3 + 1);
        world.add(create(type, std::rand() % 100, std::rand() % 100));
    }

    std::cout << "Saving..." << std::endl;
    save(world.npcs, "npc.txt");

    std::cout << "Loading..." << std::endl;
    world.npcs = load("npc.txt");

    std::cout << "Initial state:" << std::endl;
    world.print();

    std::cout << "Fighting..." << std::endl;
    for (size_t distance = 20; (distance <= 100) && !world.npcs.empty(); distance += 10) {
        auto dead_list = world.fight(distance);
        for (auto& d : dead_list)
            world.remove(d);

        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << "survivors: " << world.npcs.size() << std::endl
                  << std::endl;
    }

    std::cout << "Survivors:" << std::endl;
    world.print();

    return 0;
}