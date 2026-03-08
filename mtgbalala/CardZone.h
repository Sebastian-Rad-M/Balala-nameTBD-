#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

class Card;
class CardZone {
   protected:
	std::vector<std::shared_ptr<Card>> cards;

   public:
	void addCard(std::shared_ptr<Card> c);

	void removeCard(int index);

	int size() const;

	void empty();

	void moveCardTo(int index, CardZone& destination);
	const std::vector<std::shared_ptr<Card>>& getCards() const;
};
