#include <iostream>

#include "EffectRed.h"
#include "RoundTracker.h"

void RiteOfFlameEffect::resolve(RoundTracker& state) {
	const auto& grave = state.getGraveyard().getCards();
	for (const auto& card : grave) {
		if (card->getName() == "Rite of Flame") {
			incrementBonus();
		}
	}

	int totalRed = 2 + bonusMana;
	state.getManaPool().addMana(totalRed, 0, 0);

	std::cout << "Rite of Flame resolves! Found " << bonusMana << " copies in the grave. Added "
			  << totalRed << " Red Mana.\n";
	resetBonus();
}

std::unique_ptr<IEffect> RiteOfFlameEffect::clone() const {
	return std::make_unique<RiteOfFlameEffect>(*this);
}
