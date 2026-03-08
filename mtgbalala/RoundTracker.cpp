#include "RoundTracker.h"

RoundTracker::RoundTracker(const ActiveRun& runData)
    : currentRun(runData), currentScore(0), stormCount(0), manaPool(0, 0, 0) {
    targetScore = currentRun.run.targetScore();
    discardsLeft = currentRun.player.getMaxDiscards();
}

void RoundTracker::drawCard() {
    auto card = deck.popTopCard();
    if (card) {
        hand.addCard(card);
    } else {
        std::cout << "Deck is empty!\n";
    }  /// TODO: maybe lose? either way add an std exception later
}

bool RoundTracker::canDiscard() const { 
    return discardsLeft > 0; 
}

void RoundTracker::useDiscard() {
    if (discardsLeft > 0) {
        discardsLeft--;
    }
}

bool RoundTracker::isRoundWon() const { 
    return currentScore >= targetScore; 
}

void RoundTracker::startNewRound() {
    currentScore = 0;
    stormCount = 0;
    discardsLeft = currentRun.player.getMaxDiscards();
    targetScore = currentRun.run.targetScore();
}

void RoundTracker::addScore(int amount) { 
    currentScore += amount; 
}

int RoundTracker::getStormCount() const { 
    return stormCount; 
}

ManaPool& RoundTracker::getManaPool() { 
    return manaPool; 
}

CardZone& RoundTracker::getGraveyard() { 
    return graveyard; 
}
CardZone& RoundTracker::getHand() {
     return hand; 
}

void RoundTracker::printStatus() const {
    std::cout << "  Score : " << currentScore << " / " << targetScore << "\n"
              << "  Storm : " << stormCount << "\n"
              << "  Discards left: " << discardsLeft << "\n"
              << "  Mana  : " << manaPool << "\n";
}


void RoundTracker::setupDeck(const Deck& library) {
        deck.empty(); //add 
        for (const auto& card : library.getCards()) {
            deck.addCard(card); 
        }
        
        deck.shuffle(); 
        //draw 5
        for (int i = 0; i < 5; ++i) {
            drawCard();
        }
    }

bool RoundTracker::playCardFromHand(int index) {
        if (index < 0 || index >= hand.size()) return false;
        
        std::shared_ptr<Card> card = hand.getCards()[index];

        if (manaPool.canAfford(card->getRedCost(), card->getBlueCost(),
                               card->getGreenCost(), card->getGenericCost())) {
            
            manaPool.spendMana(card->getRedCost(), card->getBlueCost(),
                               card->getGreenCost(), card->getGenericCost());
            
            card->play(*this);
            stormCount++;
            
            // --- TEMPORARY: Give some score so we can actually win for testing! ---
            currentScore += 100; 
            
            std::cout << "  --> Successfully played " << card->getName() << "!\n";
            
            hand.moveCardTo(index, graveyard);
            
            return true;
        } else {
            std::cout << "  --> [!] Not enough mana to play " << card->getName() << "!\n";
            return false;
        }
    }