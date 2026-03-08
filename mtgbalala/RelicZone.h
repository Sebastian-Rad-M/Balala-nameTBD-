#pragma once
#include <vector>
#include <memory>
#include <iostream>
#include "Relic.h" 
class RoundTracker; // Forward declaration

class RelicZone {
private:
    std::vector<std::shared_ptr<IRelic>> relics;
    int capacity;
public:
    RelicZone(int maxCapacity = 5) ;
    bool addRelic(std::shared_ptr<IRelic> relic) ;
    
    void triggerOnManaAdded(int& r, int& b, int& g, RoundTracker& state);
    void triggerOnCardPlayed(RoundTracker& state);
    void triggerOnCardDrawn(RoundTracker& state);
    void triggerOnDamageDealt(int& scoredPts, RoundTracker& state);

    std::vector<std::shared_ptr<IRelic>>& getRelicZone() { return relics; }
};