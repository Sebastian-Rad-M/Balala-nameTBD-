#pragma once
#include <memory>
#include <random>
#include <algorithm>
#include "Cardzone.h"
#include "RNG.h"

class Deck : public CardZone {
   public:
	void shuffle() {
		std::shuffle(cards.begin(), cards.end(), RNG::engine());
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
