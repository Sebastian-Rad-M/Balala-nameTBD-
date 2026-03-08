#include "ActiveRun.h"
#include "CardDatabase.h"
#include "RoundTracker.h"
#include "View.h"
void View::printSeparator(const std::string& title) {
	std::cout << "\n╔══════════════════════════════════╗\n"
			  << "║  " << title;
	const int boxWidth = 34;
	int padding = boxWidth - static_cast<int>(title.size()) - 1;
	for (int i = 0; i < padding; ++i) {
		std::cout << ' ';
	}
	std::cout << "║\n"
			  << "╚══════════════════════════════════╝\n";
}

int View::readInt(int l, int h) {
	int value;
	while (!(std::cin >> value) || value < l || value > h) {
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		std::cout << "  Please enter a number between " << l << " and " << h << ": ";
	}
	return value;
}

void View::showMainMenu(GameState& state, ActiveRun& activeRun) {
	printSeparator("MAIN MENU");
	std::cout << "  [1] New Run\n"
			  << "  [2] Quit\n"
			  << "  Choice: ";

	int choice = readInt(1, 2);

	if (choice == 1) {
		activeRun.run.reset();
		activeRun.player = PlayerInfo();
		const std::string APPEND_COLORS[3] = {"red", "blue", "green"};
		for (int i = 0; i < 2; i++) {
			for (size_t j = 0; j < 3; j++) {
				activeRun.player.getDeck().addCard(
					CardDatabase::getInstance().createCard("c_basic_" + APPEND_COLORS[j]));
			}
		}
		state = GameState::DRAFT;
	} else {
		state = GameState::GAME_OVER;
	}
}

void View::showDraft(GameState& state, ActiveRun& activeRun) {
	printSeparator("DRAFT PHASE");
	std::cout << "  Choose 5 cards from this pool of 10 to form your starting deck.\n\n";

	std::vector<std::shared_ptr<Card>> pool;
	for (int i = 0; i < 10; i++) {
		std::shared_ptr<Card> randomCard = CardDatabase::getInstance().getRandomCard();
		if (randomCard) {
			pool.push_back(randomCard);
		} else {
			std::cout << "  [ERROR] Database is empty! Cannot draft.\n";
			state = GameState::MAIN_MENU;
			return;
			/// TODO: try catch or error or some shi
		}
	}

	for (int pick = 0; pick < 5; pick++) {
		std::cout << "  --- Pick " << (pick + 1) << " of 5 ---\n";

		for (int i = 0; i < pool.size(); i++) {
			std::cout << "  [" << (i + 1) << "] " << *pool[i] << "\n";
		}

		std::cout << "  Choice: ";
		int choice = readInt(1, pool.size());

		std::shared_ptr<Card> chosenCard = pool[choice - 1];
		activeRun.player.getDeck().addCard(chosenCard);

		std::cout << "  --> Drafted " << chosenCard->getName() << "!\n\n";

		pool.erase(pool.begin() + (choice - 1));
	}

	std::cout << "  Draft complete! Your starting deck has " << activeRun.player.getDeck().size()
			  << " cards.\n";
	std::cout << "  Press ENTER to enter combat...\n";
	std::cin.ignore(10000, '\n');
	std::cin.get();
	state = GameState::COMBAT;
}
void View::showCombat(GameState& state, ActiveRun& activeRun, RoundTracker& combatRound,
					  bool& playerWon) {
	printSeparator("COMBAT - Round " + std::to_string(activeRun.run.getCurrentRound()));
	combatRound.printStatus();

	std::cout << "\n  --- YOUR HAND ---\n";
	const auto& handCards = combatRound.getHand().getCards();

	if (handCards.empty()) {
		std::cout << "  (Hand is empty!)\n";
	} else {
		for (size_t i = 0; i < handCards.size(); ++i) {
			std::cout << "  [" << (i + 1) << "] " << *handCards[i] << "\n";
		}
	}

	// --- 2. PLAYER ACTIONS ---
	std::cout << "\n  [1] Play a card\n"
			  << "  [2] End Turn (Concede)\n"
			  << "  Choice: ";

	int choice = readInt(1, 2);

	if (choice == 1) {
		if (handCards.empty()) {
			std::cout << "  [!] You have no cards to play!\n";
		} else {
			std::cout << "  Which card? (1-" << handCards.size() << "): ";
			int cardChoice = readInt(1, handCards.size());

			// Array indices start at 0, so we pass cardChoice - 1
			combatRound.playCardFromHand(cardChoice - 1);
		}
	} else {
		playerWon = false;
		state = GameState::GAME_OVER;
		return;
	}

	// --- 3. WIN CONDITION CHECK ---
	if (combatRound.isRoundWon()) {
		std::cout << "\n  *** BLIND DEFEATED! ***\n";
		std::cout << "  Press ENTER to visit the Shop...\n";
		std::cin.ignore(10000, '\n');
		std::cin.get();

		state = GameState::SHOP;
	}
}
void View::showShop(GameState& state, ActiveRun& activeRun) {
	printSeparator("SHOP");
	activeRun.triggerPostRoundRewards();
	std::cout << "  Gold: " << activeRun.player.getGold() << "\n"
			  << "  (Shop logic stub – will present cards/packs to buy)\n"
			  << "  Press ENTER to continue to next round...\n";
	std::cin.ignore();

	activeRun.run.advanceRound();

	state = GameState::COMBAT;
}

void View::showGameOver(bool playerWon, const ActiveRun& activeRun) {
	printSeparator("GAME OVER");
	if (playerWon) {
		std::cout << "  You beat every blind! Congratulations!\n";
	} else {
		std::cout << "  Your run has ended. Better luck next time.\n";
	}

	std::cout << "  Rounds won: " << activeRun.run.getCurrentRound() << "\n\n";
}
