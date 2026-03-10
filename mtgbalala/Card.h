#pragma once
#include "iEffect.h"
#include <vector>
#include <memory>
#include <string>
class modifier;
class RoundTracker;

class Card {
   private:
	std::string name;
	int genericCost, redCost, blueCost, greenCost;
	std::vector<std::unique_ptr<IEffect>> effects;
	char rarity;  // C, U, R, L
	//TODO: enum class
	std::shared_ptr<modifier> mod = nullptr;

   public:
	Card();
	Card(const std::string& name, int genericCost = 0, int redCost = 0, int blueCost = 0,
		 int greenCost = 0, char rarity = 'C', std::shared_ptr<modifier> mod = nullptr);
	Card(const Card& other);
	Card& operator=(const Card& other);
	~Card();
	friend std::ostream& operator<<(std::ostream& os, const Card& c) ;

	void play(RoundTracker& state);
	void addEffect(std::unique_ptr<IEffect>);
	const std::string& getName() const;
	int getGenericCost() const;
	int getRedCost() const;
	int getBlueCost() const;
	int getGreenCost() const;
	char getRarity() const;
	int totalCost() const;
};
