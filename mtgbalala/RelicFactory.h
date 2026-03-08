#pragma once
#include <map>
#include <string>
#include <memory>
#include "RelicEffects.h"
//i lied its a database 
class RelicDatabase {
private:
    std::map<std::string, std::shared_ptr<IRelic>> registry;

    // Private constructor for Singleton
    //singleton slop 
    RelicDatabase() { loadAllRelics(); }

public:
    static RelicDatabase& instance() {
        static RelicDatabase inst;
        return inst;
    }

    void loadAllRelics() {
        //here we go again
        registry["r_kinnan"] = std::make_shared<OnManaRelic>("Kinnan, Bonder Prodigy", 2);
        registry["r_birgi"] = std::make_shared<OnCastTriggerRelic>(
            "Birgi, God of Storytelling",
            "Whenever you cast a spell, add 1 Red mana.",
            std::make_unique<AddManaEffect>(1, 0, 0)
        );
    }

    // Hand out clones to the player!
    std::shared_ptr<IRelic> getRelic(const std::string& id) {
        auto it = registry.find(id);
        if (it != registry.end()) {
            return it->second->clone(); // Stamp out a fresh copy!
        }
        std::cerr << "  [!] Relic Database Error: Unknown ID '" << id << "'\n";
        return nullptr;
    }
};