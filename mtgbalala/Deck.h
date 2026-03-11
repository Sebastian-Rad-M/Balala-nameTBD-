#pragma once
#include "CardZone.h"
class Deck : public CardZone {
   public:
	void shuffle();
	std::shared_ptr<Card> popTopCard();	 // returns the pointer to top
};
