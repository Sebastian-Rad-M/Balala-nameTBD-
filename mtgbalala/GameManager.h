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
    static GameManager& instance();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;
    // i :heart_emoji: singletons

    void run();
};