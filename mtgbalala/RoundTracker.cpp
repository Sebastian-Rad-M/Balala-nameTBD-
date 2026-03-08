#include "RoundTracker.h"
#include "ActiveRun.h"
RoundTracker::RoundTracker(const ActiveRun& runData)
	: currentRun(runData), currentScore(0), stormCount(0), manaPool(0, 0, 0) {
	targetScore = currentRun.run.targetScore();
}

void RoundTracker::drawCard() {
	auto card = deck.popTopCard();
	if (card) {
		hand.addCard(card);
	} else {
		std::cout << "Deck is empty!\n";
	}  // TODO: maybe lose? either way add an std exception later
}
void RoundTracker::drawCards(int amount) {
    
    
    for (int i = 0; i < amount; i++) drawCard();
    
    relics.triggerOnCardDrawn(*this);
}


bool RoundTracker::promptDiscard() {
	if (hand.size() == 0) {
		return false;
	}

	std::cout << "\n  --- DISCARD A CARD ---\n";

	// 1. Print the current hand
	const auto& handCards = hand.getCards();
	for (size_t j = 0; j < handCards.size(); ++j) {
		std::cout << "  [" << (j + 1) << "] " << *handCards[j] << "\n";
	}

	// 2. Ask for input safely
	int choice = -1;
	while (true) {
		std::cout << "  Choose a card to discard (1-" << handCards.size() << "): ";

		if (std::cin >> choice && choice >= 1 && choice <= handCards.size()) {
			break;	// Valid input!
		}

		// If they typed a letter or out-of-bounds number, clear it and loop
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "  [!] Invalid choice. Try again.\n";
	}

	// 3. Move it to the graveyard
	std::cout << "  --> Discarded " << handCards[choice - 1]->getName() << "!\n";
	hand.moveCardTo(choice - 1, graveyard);

	return true;
}

bool RoundTracker::isRoundWon() const { return currentScore >= targetScore; }

void RoundTracker::startNewRound() {
	currentScore = 0;
	stormCount = 0;
	targetScore = currentRun.run.targetScore();
}

void RoundTracker::addScore(int amount) { currentScore += amount; }
void RoundTracker::addMana(int r, int b, int g) {
       
        relics.triggerOnManaAdded(r, b, g, *this);
        manaPool.addMana(r, b, g);
    }
int RoundTracker::getStormCount() const { return stormCount; }

ManaPool& RoundTracker::getManaPool() { return manaPool; }

CardZone& RoundTracker::getGraveyard() { return graveyard; }
CardZone& RoundTracker::getHand() { return hand; }

void RoundTracker::printStatus() const {
	std::cout << "  Score : " << currentScore << " / " << targetScore << "\n"
			  << "  Storm : " << stormCount << "\n"
			  << "  Mana  : " << manaPool << "\n";
}

void RoundTracker::setupDeck(const Deck& library, const RelicZone& startingRelics) {
	deck.empty();  // add
	for (const auto& card : library.getCards()) {
		deck.addCard(card);
	}

	deck.shuffle();
	// draw 5
	for (int i = 0; i < 5; i++) {
		drawCard();
	}
	RelicZone activeRelics = startingRelics;
}

bool RoundTracker::playCardFromHand(int index) {
	if (index < 0 || index >= hand.size()) {
		return false;
	}

	std::shared_ptr<Card> card = hand.getCards()[index];

	if (manaPool.canAfford(card->getRedCost(), card->getBlueCost(), card->getGreenCost(),
						   card->getGenericCost())) {
		manaPool.spendMana(card->getRedCost(), card->getBlueCost(), card->getGreenCost(),
						   card->getGenericCost());

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
