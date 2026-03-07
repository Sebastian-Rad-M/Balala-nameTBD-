#pragma once
#include <random>

#include "Cardzone.h"

class Deck : public CardZone {
   public:
	void shuffle() {
		auto rng = std::default_random_engine{};
		std::shuffle(std::begin(cards), std::end(cards), rng);
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
