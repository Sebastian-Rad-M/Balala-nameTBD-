#pragma once
#include <algorithm>
#include <memory>
#include <random>
#include <vector>

class Card; // forward declaration — shared_ptr<Card> doesn't need the full
            // definition
class CardZone {
protected:
  std::vector<std::shared_ptr<Card>> cards;

public:
  void addCard(std::shared_ptr<Card> c) { cards.push_back(c); }

  void removeCard(int index) { cards.erase(cards.begin() + index); }

  int size() const { return cards.size(); }

  void empty() { cards.clear(); }

  void moveCardTo(int index, CardZone &destination) {
    destination.addCard(cards[index]);
    removeCard(index);
  }
};
