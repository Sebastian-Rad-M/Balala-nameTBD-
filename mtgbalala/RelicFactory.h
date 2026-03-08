#pragma once
#include <map>
#include <string>
#include <memory>
#include <iostream>
#include "RelicEffects.h"

//i lied its a database 
class RelicDatabase {
private:
    std::map<std::string, std::shared_ptr<IRelic>> registry;

    // Private constructor for Singleton
    //singleton slop 
    RelicDatabase();

public:
    static RelicDatabase& getInstance();

    RelicDatabase(const RelicDatabase&) = delete;
    RelicDatabase& operator=(const RelicDatabase&) = delete;

    void loadAllRelics();

    // Hand out clones to the player!
    std::shared_ptr<IRelic> getRelic(const std::string& id);

    std::shared_ptr<IRelic> getRandomRelic();
};