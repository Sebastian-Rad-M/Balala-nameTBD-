#pragma once

#include <iostream>
#include <string>

#include "ActiveRun.h"
#include "RoundTracker.h"

enum class GameState { MAIN_MENU, DRAFT, COMBAT, SHOP, GAME_OVER };

class View {
   public:
	// ── Main Menu ─────────────────────────────────────────────────────────────
	void showMainMenu(GameState& state, ActiveRun& activeRun) {
		printSeparator("MAIN MENU");
		std::cout << "  [1] New Run\n"
				  << "  [2] Quit\n"
				  << "  Choice: ";

		int choice = readInt(1, 2);

		if (choice == 1) {
			activeRun.run.reset();
			activeRun.player = PlayerInfo();
			state = GameState::DRAFT;
		} else {
			state = GameState::GAME_OVER;
		}
	}

	// ── Draft ─────────────────────────────────────────────────────────────────
	void showDraft(GameState& state) {
		printSeparator("DRAFT PHASE");
		std::cout << "  (Draft logic stub – will present 10 cards; player picks 5)\n"
				  << "  Press ENTER to skip draft and start with a default deck...\n";
		std::cin.ignore();

		// TODO: populate RoundTracker::deck with chosen cards

		state = GameState::COMBAT;
	}

	// ── Combat ────────────────────────────────────────────────────────────────
	void showCombat(GameState& state, ActiveRun& activeRun, RoundTracker& round, bool& playerWon) {
		printSeparator("COMBAT – Round " +
					   std::to_string(activeRun.run.getCurrentRound()));  // shows target as context
		activeRun.run.printStatus();
		round.printStatus();

		std::cout << "\n  [1] Play a card (stub)\n"
				  << "  [2] End turn\n"
				  << "  [3] Concede run\n"
				  << "  Choice: ";

		int choice = readInt(1, 3);

		if (choice == 1) {
			// TODO: draw from RoundTracker, pick a card from hand, call tryPlayCard
			std::cout << "  (Card play stub – no card selected yet)\n";
		} else if (choice == 2) {
			round.getManaPool().clearPool();

			if (round.isRoundWon()) {
				playerWon = true;
				state = GameState::SHOP;
			} else {
				// stay in COMBAT for the next turn
			}
		} else {  // concede
			playerWon = false;
			state = GameState::GAME_OVER;
		}
	}

	// ── Shop ──────────────────────────────────────────────────────────────────
	void showShop(GameState& state, ActiveRun& activeRun) {
		printSeparator("SHOP");
		activeRun.triggerPostRoundRewards();
		std::cout << "  Gold: " << activeRun.player.getGold() << "\n"
				  << "  (Shop logic stub – will present cards/packs to buy)\n"
				  << "  Press ENTER to continue to next round...\n";
		std::cin.ignore();

		activeRun.run.advanceRound();

		state = GameState::COMBAT;
	}

	// ── Game Over ─────────────────────────────────────────────────────────────
	void showGameOver(bool playerWon, const ActiveRun& activeRun) {
		printSeparator("GAME OVER");
		if (playerWon) {
			std::cout << "  You beat every blind! Congratulations!\n";
		} else {
			std::cout << "  Your run has ended. Better luck next time.\n";
		}

		std::cout << "  Rounds won: " << activeRun.run.targetScore()
				  << "\n\n";  // targetScore reflects progression
	}

   private:
	// ── Helpers ───────────────────────────────────────────────────────────────

	static void printSeparator(const std::string& title) {
		std::cout << "\n╔══════════════════════════════════╗\n"
				  << "║  " << title;
		const int boxWidth = 34;
		int padding = boxWidth - static_cast<int>(title.size()) - 2;
		for (int i = 0; i < padding; ++i) {
			std::cout << ' ';
		}
		std::cout << "║\n"
				  << "╚══════════════════════════════════╝\n";
	}

	static int readInt(int lo, int hi) {
		int value;
		while (!(std::cin >> value) || value < lo || value > hi) {
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::cout << "  Please enter a number between " << lo << " and " << hi << ": ";
		}
		return value;
	}
};
