#pragma once
#include <iostream>
#include <string>
//call me pest control the way i be debuging shit
//#include "ActiveRun.h"
//#include "RoundTracker.h"
class ActiveRun;
class RoundTracker;



// this class is a placefolder , we will use sfml 
enum class GameState { MAIN_MENU, DRAFT, COMBAT, SHOP, GAME_OVER };

class View {
  private:
    static void printSeparator(const std::string& title);
    static int readInt(int l, int h);
    
  public:
    void showMainMenu(GameState& state, ActiveRun& activeRun);
    void showDraft(GameState& state, ActiveRun& activeRun);  
   void showCombat(GameState& state, ActiveRun& activeRun, RoundTracker& combatRound, bool& playerWon);
    void showShop(GameState& state, ActiveRun& activeRun);
    void showGameOver(bool playerWon, const ActiveRun& activeRun);
};