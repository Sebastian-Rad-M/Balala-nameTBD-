#pragma once
#include <iostream>
#include <limits>
#include <memory>

#include "ActiveRun.h"
#include "Card.h"
#include "Deck.h"
#include "LightPool.h"
#include "RelicZone.h"

class RoundTracker {
   private:
	Deck deck;
	RelicZone relics;
	CardZone hand, graveyard, exile;
	ManaPool manaPool;
	const ActiveRun& currentRun;
	int currentScore;
	int targetScore;
	int stormCount;

   public:
	RoundTracker(const ActiveRun& runData);

	void drawCard();
	void drawCards(int amount);
	bool promptDiscard();
	// void tryPlayCard(Card& card); depreciated, replace with playCardFromHand(int index)

	bool isRoundWon() const;

	void startNewRound();

	void addScore(int amount);
	void addMana(int r, int b, int g);
	int getStormCount() const;

	ManaPool& getManaPool();

	CardZone& getGraveyard();

	CardZone& getHand();
	void setupDeck(const Deck& library, const RelicZone& startingRelics);
	void printStatus() const;
	bool playCardFromHand(int index);
};
