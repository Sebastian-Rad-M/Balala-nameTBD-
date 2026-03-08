#include "Card.h"
#include "RoundTracker.h"

void Card::play(RoundTracker& state) {
	for (const auto& effect : effects) {
		effect->resolve(state);
	}
}
void Card::addEffect(std::unique_ptr<IEffect> effect) { effects.push_back(std::move(effect)); }
const std::string& Card::getName() const { return name; }

int Card::getGenericCost() const { return genericCost; }

int Card::getRedCost() const { return redCost; }

int Card::getBlueCost() const { return blueCost; }

int Card::getGreenCost() const { return greenCost; }

char Card::getRarity() const { return rarity; }

int Card::totalCost() const { return genericCost + redCost + blueCost + greenCost; }
