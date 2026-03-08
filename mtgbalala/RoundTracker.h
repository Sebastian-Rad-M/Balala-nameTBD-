#pragma once
#include <iostream>
#include <memory>

#include "ActiveRun.h"
#include "Card.h"
#include "Deck.h"
#include "LightPool.h"

class RoundTracker {
   private:
    Deck deck;
    CardZone hand, graveyard, exile;
    ManaPool manaPool;
    const ActiveRun& currentRun;
    int currentScore;
    int targetScore;
    int stormCount;
    int discardsLeft;

   public:
    RoundTracker(const ActiveRun& runData);

    void drawCard();

   // void tryPlayCard(Card& card); depreciated, replace with playCardFromHand(int index)
 
    bool canDiscard() const;

    void useDiscard();

    bool isRoundWon() const;

    void startNewRound();
    
    void addScore(int amount);
    
    int getStormCount() const;
    
    ManaPool& getManaPool();
    
    CardZone& getGraveyard();
    
	CardZone& getHand() ;
	void setupDeck(const Deck& library);
    void printStatus() const;
	bool playCardFromHand(int index);
};