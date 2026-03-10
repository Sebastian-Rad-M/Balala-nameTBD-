#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include "Shop.h"
#include <limits>
class ActiveRun;
class RoundTracker;

enum class GameState { MAIN_MENU, DRAFT, COMBAT, SHOP, GAME_OVER };

class View {
   private:void clearScreen();
	static void printSeparator(const std::string& title);
	

   public:
   static int readInt(int l, int h);
	
	void showMainMenu(GameState& state, ActiveRun& activeRun);
	void showDraft(GameState& state, ActiveRun& activeRun);
	void showCombat(GameState& state, ActiveRun& activeRun, RoundTracker& combatRound,
					bool& playerWon);
	void showShop(GameState& state, ActiveRun& activeRun);
	void showGameOver(bool playerWon, const ActiveRun& activeRun);
};
