#pragma once
#include "npc.hpp"
#include <fstream>

struct ConsoleObserver : public IFightObserver
{
    void on_fight(std::shared_ptr<NPC> attacker,
                  std::shared_ptr<NPC> defender,
                  bool win) override
    {
        std::cout << "Fight: ";
        attacker->print();
        std::cout << (win ? " wins vs " : " loses to ");
        defender->print();
        std::cout << "\n";
    }
};

struct FileObserver : public IFightObserver
{
    std::ofstream file;

    FileObserver()
    {
        file.open("log.txt", std::ios::app);  
    }

    ~FileObserver()
    {
        if (file.is_open())
            file.close();
    }

    void on_fight(std::shared_ptr<NPC> attacker,
                  std::shared_ptr<NPC> defender,
                  bool win) override
    {
        if (!file.is_open()) return;

        file << "Fight: ";

        file << "Attacker(" << attacker->x << "," << attacker->y << ", type=" << (int)attacker->type << ")";
        file << (win ? " wins vs " : " loses to ");
        file << "Defender(" << defender->x << "," << defender->y << ", type=" << (int)defender->type << ")";

        file << "\n";
        file.flush();
    }
};
