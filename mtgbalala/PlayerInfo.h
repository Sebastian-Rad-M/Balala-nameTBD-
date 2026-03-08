#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Deck.h"
#include "RelicZone.h"

class PlayerInfo {
   private:
	int gold;
	Deck deck;
	RelicZone relics;

   public:
	PlayerInfo() : gold(100) {}// initial gold for testing, make 10 or someshit

	PlayerInfo(int gold) : gold(gold) {}

	~PlayerInfo() = default;

	int getGold() const { return gold; }

	void addGold(int amount) { gold += amount; }
	bool spendGold(int amount) {
		if (gold < amount) {
			return false;
		}
		gold -= amount;
		return true;
	}
	Deck& getDeck() { return deck; }
	RelicZone& getRelicZone() { return relics; }
};
