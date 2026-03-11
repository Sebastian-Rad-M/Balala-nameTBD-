#include <memory>

#include "Card.h"
#include "CardZone.h"

void CardZone::addCard(std::shared_ptr<Card> c) { cards.push_back(c); }

void CardZone::removeCard(int index) { cards.erase(cards.begin() + index); }

int CardZone::getSize() const { return cards.size(); }

void CardZone::clearZone() { cards.clear(); }

void CardZone::moveCardTo(int index, CardZone& destination) {
	destination.addCard(cards[index]);
	removeCard(index);
}
const std::vector<std::shared_ptr<Card>>& CardZone::getCards() const { return cards; }
