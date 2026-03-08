#include "CardDatabase.h"
#include "effectsRed.h"
#include <cstdlib>
#include <random>
CardDatabase& CardDatabase::getInstance() {
    static CardDatabase instance;
    return instance;
}

CardDatabase::CardDatabase() { 
    loadAllCards(); 
}

void CardDatabase::loadAllCards() {
    // --- STARTER CARDS ---
    Card basicRed("Basic Red", 0, 0, 0, 0, 'B');
    basicRed.addEffect(std::make_unique<AddManaEffect>(1, 0, 0));
    library["c_basic_red"] = basicRed;

    Card basicBlue("Basic Blue", 0, 0, 0, 0, 'B');
    basicBlue.addEffect(std::make_unique<AddManaEffect>(0, 1, 0));
    library["c_basic_blue"] = basicBlue;

    Card basicGreen("Basic Green", 0, 0, 0, 0, 'B');
    basicGreen.addEffect(std::make_unique<AddManaEffect>(0, 0, 1));
    library["c_basic_green"] = basicGreen;
    
    // --- COMMON CARDS ---
    Card brainstorm("Brainstorm", 0, 1, 0);
    library["c_brainstorm"] = brainstorm;

    Card riteOfFlame("Rite of Flame", 0, 1, 0, 0, 'C');
    riteOfFlame.addEffect(std::make_unique<RiteOfFlameEffect>());
    library["c_rite_of_flame"] = riteOfFlame;
}

std::shared_ptr<Card> CardDatabase::createCard(const std::string& cardID) {
    if (library.find(cardID) != library.end()) {
        return std::make_shared<Card>(library[cardID]);
    }
    std::cerr << "Error: Card ID " << cardID << " not found!\n";
    return nullptr;
}

std::shared_ptr<Card> CardDatabase::getTrueRandomCard() {
    if (library.empty()) return nullptr;
    
    auto rCard = library.begin();
    std::advance(rCard, rand() % library.size());
    return std::make_shared<Card>(rCard->second);
}
std::shared_ptr<Card> CardDatabase::getRandomCard() {
   if (library.empty()) return nullptr;
   ///Sexy randomness 
    std::random_device rd;
    std::mt19937 gen(rd());
    ///we use weight to det distribution
    int totalWeight = 0;
    for (const auto& pair : library) {
        char r = pair.second.getRarity();
        
        if (r == 'B') continue; // Basics = 0 
        else if (r == 'C') totalWeight += 60; // Commons = 60% 
        else if (r == 'U') totalWeight += 30; // Uncommons = 30%
        else if (r == 'R') totalWeight += 10; // Rares = 10%
        else if (r == 'L') totalWeight += 1;  // Legendaries = 1%
    }

    // prevent a crash
    if (totalWeight == 0) {
        std::cerr << "  [!] Error: No draftable cards in the database!\n";
        return nullptr;
    }

    std::uniform_int_distribution<> dist(1, totalWeight);
    int winningTicket = dist(gen);

    ///yes, we recalc this, so is life
    int currentWeight = 0;
    for (const auto& pair : library) {
        char r = pair.second.getRarity();
        
        if (r == 'B') continue;        
        if (r == 'C') currentWeight += 60;
        else if (r == 'U') currentWeight += 30;
        else if (r == 'R') currentWeight += 10;
        else if (r == 'L') currentWeight += 1;
        if (currentWeight >= winningTicket) {
            return std::make_shared<Card>(pair.second);
        }
    }

    return nullptr; // Fallback (should never actually be reached) 
    ///TODO: error handling here, but for now, just return null
}