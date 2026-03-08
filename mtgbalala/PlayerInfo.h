#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Deck.h"
/// TODO: Forward declarations, remove later
class Relic;

class PlayerInfo {
   private:
	int gold;
	Deck deck;
	// std::vector<std::shared_ptr<Relic>> m_relics;
	/// TODO: add deck and relics when Card.h / Relic.h are ready

   public:
	PlayerInfo() : gold(10)	 {}

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
};
