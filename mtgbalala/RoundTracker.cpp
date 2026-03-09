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

	void RoundTracker::addStatus(std::unique_ptr<IStatus> status) {
		activeStatuses.push_back(std::move(status));
	}

	bool RoundTracker::promptDiscard() {
		if (hand.size() == 0) {
			return false;
		}

		std::cout << "\n  --- DISCARD A CARD ---\n";
		const auto& handCards = hand.getCards();
		for (size_t j = 0; j < handCards.size(); ++j) {
			std::cout << "  [" << (j + 1) << "] " << *handCards[j] << "\n";
		}

		int choice = -1;
		while (true) {
			std::cout << "  Choose a card to discard (1-" << handCards.size() << "): ";

			if (std::cin >> choice && choice >= 1 && choice <= handCards.size()) {
				break;	// Valid input!
			}
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "  [!] Invalid choice. Try again.\n";
		}
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
		deck.empty(); 
		for (const auto& card : library.getCards()) {
			deck.addCard(card);
		}

		deck.shuffle();
		// draw 5
		for (int i = 0; i < 5; i++) {
			drawCard();
		}
		this->relics = startingRelics;
	}

	bool RoundTracker::playCardFromHand(int index) {
		if (index < 0 || index >= hand.size()) {
			return false;
		}

		std::shared_ptr<Card> card = hand.getCards()[index];

		int r = card->getRedCost();
		int b = card->getBlueCost();
		int g = card->getGreenCost();
		int gen = card->getGenericCost();
		for (auto& status : activeStatuses) status->modifyCost(r, b, g, gen);
		if (manaPool.canAfford(r, b, g, gen)) {manaPool.spendMana(r, b, g, gen);
			card->play(*this);
			stormCount++;
			std::cout << "  --> Successfully played " << card->getName()<< "!\n";
			for (auto& status : activeStatuses) status->onCardPlayed(*card, *this);
			relics.triggerOnCardPlayed(*this);
			activeStatuses.erase(std::remove_if(activeStatuses.begin(), activeStatuses.end(),[](const std::unique_ptr<IStatus>& s) { return s->isExpired(); }),activeStatuses.end());
			
			hand.moveCardTo(index, graveyard);
			return true;}
		else {
			std::cout << "  --> [!] Not enough mana to play " << card->getName() << "!\n";
			return false;
		}
	}
	int RoundTracker::requestHandTarget() {
		const auto& handCards = hand.getCards();
		if (handCards.empty()) {return -1;}

		std::cout << "\n  --- TARGET ---\n";
		for (int i = 0; i < handCards.size(); i++) {
			std::cout << "  [" << (i + 1) << "] " << *handCards[i] << "\n";
		}
		
		int choice;
		std::cout << "  Select a card to exile (1-" << handCards.size() << "): ";
		
		
		return View::readInt(1, handCards.size())-1; // Return the 0-based array index!
	}