#pragma once
#include "PlayerInfo.h"
#include "RunTracker.h"
#include "Shop.h"

class ActiveRun {
   public:
	PlayerInfo player;
	RunTracker run;
	Shop currentShop;
	void triggerPostRoundRewards() {
		int reward = run.targetScore() / 100;
		player.addGold(reward);
		currentShop.generateRandomStock();
	}
};
