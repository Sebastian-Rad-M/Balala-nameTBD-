#pragma once
#include <iostream>

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
	RoundTracker(const ActiveRun& runData)
		: currentRun(runData), currentScore(0), stormCount(0), manaPool(0, 0, 0) {
		targetScore = currentRun.run.targetScore();
		discardsLeft = currentRun.player.getMaxDiscards();
	}

	void drawCard() {
		auto card = deck.popTopCard();
		if (card) {
			hand.addCard(card);
		} else {
			std::cout << "Deck is empty!\n";
		}  /// TODO: maybe lose? either way add an std exception later
	}

	void tryPlayCard(Card& card) {
		if (manaPool.canAfford(card.getRedCost(), card.getBlueCost(), card.getGreenCost(),
							   card.getGenericCost())) {
			manaPool.spendMana(card.getRedCost(), card.getBlueCost(), card.getGreenCost(),
							   card.getGenericCost());
			card.play(*this);
			stormCount++;
			std::cout << "Successfully played " << card.getName() << "!\n";
			std::cout << "Remaining " << manaPool << "\n";
		} else {
			// throw NotEnoughManaException("Not enough mana to play this card!");
			std::cout << "Not enough mana!\n";
		}
	}

	bool canDiscard() const { return discardsLeft > 0; }

	void useDiscard() {
		if (discardsLeft > 0) {
			discardsLeft--;
		}
	}

	bool isRoundWon() const { return currentScore >= targetScore; }

	void startNewRound() {
		currentScore = 0;
		stormCount = 0;
		discardsLeft = currentRun.player.getMaxDiscards();
		targetScore = currentRun.run.targetScore();
	}
	void addScore(int amount) { currentScore += amount; }
	int getStormCount() const { return stormCount; }
	ManaPool& getManaPool() { return manaPool; }
	CardZone& getGraveyard() { return graveyard; }
	void printStatus() const {
		std::cout << "  Score : " << currentScore << " / " << targetScore << "\n"
				  << "  Storm : " << stormCount << "\n"
				  << "  Discards left: " << discardsLeft << "\n"
				  << "  Mana  : " << manaPool << "\n";
	}
};
