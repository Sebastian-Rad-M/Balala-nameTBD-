#pragma once
#include <optional>
#include "ActiveRun.h"
#include "RoundTracker.h"
#include "View.h"

class GameManager {
    private:
	GameManager() = default;
	ActiveRun activeRun;
	std::optional<RoundTracker> round;  // constructed fresh at DRAFT state
	GameState state = GameState::MAIN_MENU;
	bool playerWon = false;
	View view;
	
	public:
	static GameManager& instance() {
		static GameManager inst;
		return inst;
	}

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	// i :heart_emoji: singletons

	void run() {
		state = GameState::MAIN_MENU;

		while (state != GameState::GAME_OVER) {
			switch (state) {
				case GameState::MAIN_MENU:
					view.showMainMenu(state, activeRun);
					break;

				case GameState::DRAFT:
					view.showDraft(state);
					// TODO: 
					round.emplace(activeRun);
					break;

				case GameState::COMBAT:
					view.showCombat(state, activeRun, round.value(), playerWon);
					break;

				case GameState::SHOP:
					view.showShop(state, activeRun);
					// Advance round and reset round state for the next combat
					round->startNewRound();
					break;

				default:
					break;
			}
		}

		view.showGameOver(playerWon, activeRun);
	}

  
};
