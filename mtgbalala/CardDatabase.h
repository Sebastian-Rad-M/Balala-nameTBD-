#pragma once
#include "card.h"
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

/// i :heart: singletons
/// actually its a factory design patern, not just a random singleton, dont smite me
class CardDatabase {
private:
  CardDatabase() { loadAllCards(); }
  std::unordered_map<std::string, Card> library;

public:
  static CardDatabase &getInstance() {
    static CardDatabase instance;
    return instance;
  }
  CardDatabase(const CardDatabase &) = delete;
  CardDatabase &operator=(const CardDatabase &) = delete;

  void loadAllCards() {
    /// TODO: Json reader, sau 30 de linii ce cpp cu fiecare carte
    Card brainstorm("Brainstorm", 0, 1, 0);
    library["c_brainstorm"] = brainstorm;
  }

  std::shared_ptr<Card> createCard(const std::string &cardID) {
    if (library.find(cardID) != library.end()) {
      return std::make_shared<Card>(library[cardID]);
    }
    std::cerr << "Error: Card ID " << cardID << " not found!\n";
    return nullptr;
  }

  std::shared_ptr<Card> getRandomCard() {
    //TODO: this is linear distribution, make it rarity bound or make another one that is?
    if (library.empty()) return nullptr;
    auto rCard= library.begin();
    std::advance(rCard, rand() % library.size());
    return std::make_shared<Card>(rCard->second);
  }
};