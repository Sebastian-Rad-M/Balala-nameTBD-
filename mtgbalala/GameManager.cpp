#include "GameManager.h"

GameManager& GameManager::instance() {
    static GameManager inst;
    return inst;
}

void GameManager::run() {
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