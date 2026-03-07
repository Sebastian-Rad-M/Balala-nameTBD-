#pragma once

#include <optional>

#include "ActiveRun.h"
#include "RoundTracker.h"
#include "View.h"

class GameManager {
   public:
	static GameManager& instance() {
		static GameManager inst;
		return inst;
	}

	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	// i :heart_emoji: singletons

	void run() {
		m_state = GameState::MAIN_MENU;

		while (m_state != GameState::GAME_OVER) {
			switch (m_state) {
				case GameState::MAIN_MENU:
					m_view.showMainMenu(m_state, m_activeRun);
					break;

				case GameState::DRAFT:
					m_view.showDraft(m_state);
					// Construct a fresh RoundTracker for this new combat round
					m_round.emplace(m_activeRun);
					break;

				case GameState::COMBAT:
					m_view.showCombat(m_state, m_activeRun, m_round.value(), m_playerWon);
					break;

				case GameState::SHOP:
					m_view.showShop(m_state, m_activeRun);
					// Advance round and reset round state for the next combat
					m_round->startNewRound();
					break;

				default:
					break;
			}
		}

		m_view.showGameOver(m_playerWon, m_activeRun);
	}

   private:
	GameManager() = default;

	ActiveRun m_activeRun;
	std::optional<RoundTracker> m_round;  // constructed fresh at DRAFT state
	GameState m_state = GameState::MAIN_MENU;
	bool m_playerWon = false;

	View m_view;
};
