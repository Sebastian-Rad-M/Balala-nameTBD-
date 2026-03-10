#include <algorithm>
#include <memory>
#include <random>
#include "CardZone.h"
#include "RNG.h"
#include "Deck.h"
void Deck::shuffle() { std::shuffle(cards.begin(), cards.end(), RNG::engine()); }

std::shared_ptr<Card> Deck::popTopCard() {
		if (cards.empty()) {
			return nullptr;
		}
		auto topCard = cards.back();
		cards.pop_back();
		return topCard;
	}