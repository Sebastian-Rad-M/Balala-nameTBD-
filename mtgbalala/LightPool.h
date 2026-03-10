#include <iostream>
#include <stdexcept>
#pragma once
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

	
	void spendMana(int costR, int costB, int costG, int costGeneric);
	// check canAfford before
	// for generic We drain Green first, then Blue, then Red (arbitrary priority).

	friend std::ostream& operator<<(std::ostream& os, const ManaPool& pool) {
		os << "[Mana: " << pool.red << "R, " << pool.blue << "B, " << pool.green << "G]";
		return os;
	}
};
