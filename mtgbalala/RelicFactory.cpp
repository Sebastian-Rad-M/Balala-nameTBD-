#include "RelicFactory.h"

RelicDatabase::RelicDatabase() { 
    loadAllRelics(); 
}

RelicDatabase& RelicDatabase::getInstance() {
    static RelicDatabase inst;
    return inst;
}

void RelicDatabase::loadAllRelics() {
    //here we go again
    registry["r_kinnan"] = std::make_shared<OnManaRelic>("Kinnan, Bonder Prodigy", "+1 to all mana ",'R',2);
    registry["r_birgi"] = std::make_shared<OnCastTriggerRelic>("Birgi, God of Storytelling","Whenever you cast a spell, add 1 Red mana.",'R',std::make_unique<AddManaEffect>(1, 0, 0)
    );
}

std::shared_ptr<IRelic> RelicDatabase::getRelic(const std::string& id) {
    auto it = registry.find(id);
    if (it != registry.end()) {
        return it->second->clone(); // Stamp out a fresh copy!
    }
    std::cerr << "  [!] Relic Database Error: Unknown ID '" << id << "'\n";
    return nullptr;
}

std::shared_ptr<IRelic> RelicDatabase::getRandomRelic() {
    if (registry.empty()) {
        return nullptr;
    }

    int totalWeight = 0;
    for (const auto& pair : registry) {
        char r = pair.second->getRarity();
        if (r == 'B') {
            continue;  
        } else if (r == 'C') {
            totalWeight += 60;  // Commons = 60%
        } else if (r == 'U') {
            totalWeight += 30;  // Uncommons = 30%
        } else if (r == 'R') {
            totalWeight += 10;  // Rares = 10%
        } else if (r == 'L') {
            totalWeight += 1;   // Legendaries = 1%
        }
    }

    if (totalWeight == 0) {
        std::cerr << "  [!] Error: No draftable relics in the database!\n";
        return nullptr;
    }

    int winningTicket = RNG::range(1, totalWeight);
    
    int currentWeight = 0;
    for (const auto& pair : registry) {
        char r = pair.second->getRarity();

        if (r == 'B') {
            continue;
        } else if (r == 'C') {
            currentWeight += 60;
        } else if (r == 'U') {
            currentWeight += 30;
        } else if (r == 'R') {
            currentWeight += 10;
        } else if (r == 'L') {
            currentWeight += 1;
        }

        if (currentWeight >= winningTicket) {
            return pair.second->clone();
        }
    }

    return nullptr;
}