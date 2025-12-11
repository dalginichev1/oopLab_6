#include "observer.hpp"

std::shared_ptr<IFightObserver> TextObserver::get() {
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) {
    if (win) {
        std::cout << std::endl << "Fight result --------" << std::endl;
        attacker->print();
        std::cout << " wins vs ";
        defender->print();
    }
}

FileObserver::FileObserver() {
    logfile.open("log.txt", std::ios::app);
}

FileObserver::~FileObserver() {
    if (logfile.is_open())
        logfile.close();
}

std::shared_ptr<IFightObserver> FileObserver::get() {
    static FileObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver*) {});
}

void FileObserver::on_fight(const std::shared_ptr<NPC>& attacker, const std::shared_ptr<NPC>& defender, bool win) {
    if (!logfile.is_open())
        return;

    if (win) {
        logfile << "Fight result --------" << std::endl;
        logfile << "Attacker (";
        attacker->save(logfile);
        logfile << ") vs Defender (";
        defender->save(logfile);
        logfile << ") - Attacker wins" << std::endl;
    }
    logfile.flush();
}