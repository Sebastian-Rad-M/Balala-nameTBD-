#pragma once
#include "Deck.h"
#include "RelicZone.h"
#include "Card.h"
class PlayerInfo {
   private:
	int gold;
	Deck deck;
	RelicZone relics;

   public:
	PlayerInfo() : gold(100) {}// initial gold for testing, make 10 or someshit
	PlayerInfo(int gold) : gold(gold) {}

	~PlayerInfo() = default;

	int getGold() const ;

	void addGold(int amount) ;
	bool spendGold(int amount) ;
	Deck& getDeck() ;
	RelicZone& getRelicZone();

	//copy =opp
	PlayerInfo(const PlayerInfo& other);
    PlayerInfo& operator=(const PlayerInfo& other);
};
