#pragma once
#include <iostream>
#include <stdexcept>

class ManaPool {
   private:
	int red;
	int blue;
	int green;

   public:
	ManaPool(int r = 0, int b = 0, int g = 0) : red(r), blue(b), green(g) {}

	void addMana(int r, int b, int g);

	void clearPool();

	bool canAfford(int costR, int costB, int costG, int costGeneric) const;

	// check if can afford first
	void spendMana(int costR, int costB, int costG, int costGeneric);

	friend std::ostream& operator<<(std::ostream& os, const ManaPool& pool) {
		os << "[Mana: " << pool.red << "R, " << pool.blue << "B, " << pool.green << "G]";
		return os;
	}
};
