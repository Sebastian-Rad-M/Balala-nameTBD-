#pragma once
#include <memory>
#include <random>
#include <algorithm>
#include "Cardzone.h"

class Deck : public CardZone {
   public:
	void shuffle() {
		std::random_device rd; 
        std::mt19937 g(rd()); 
        std::shuffle(cards.begin(), cards.end(), g);
	}

	std::shared_ptr<Card> popTopCard() {
		if (cards.empty()) {
			return nullptr;
		}
		auto topCard = cards.back();
		cards.pop_back();
		return topCard;
	}
};
