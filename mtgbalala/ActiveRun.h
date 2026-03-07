#pragma once
#include "PlayerInfo.h"
#include "RunTracker.h"

class ActiveRun {
   public:
	PlayerInfo player;
	RunTracker run;

	void triggerPostRoundRewards() {
		int reward = run.targetScore() / 100;
		player.addGold(reward);
	}
};
