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

	void addMana(int r, int b, int g) {
		red += r;
		blue += b;
		green += g;
	}

	void clearPool() {
		red = 0;
		blue = 0;
		green = 0;
	}

	bool canAfford(int costR, int costB, int costG, int costGeneric) const {
		if (red < costR || blue < costB || green < costG) {
			return false;
		}

		int leftoverR = red - costR;
		int leftoverB = blue - costB;
		int leftoverG = green - costG;
		int totalLeftover = leftoverR + leftoverB + leftoverG;

		return totalLeftover >= costGeneric;
	}
	// check if can afford first
	void spendMana(int costR, int costB, int costG, int costGeneric) {
		red -= costR;
		blue -= costB;
		green -= costG;
		/// We drain Green first, then Blue, then Red (arbitrary priority).
		/// TODO:player chosen
		int genericRemaining = costGeneric;
		while (genericRemaining > 0 && green > 0) {
			green--;
			genericRemaining--;
		}
		while (genericRemaining > 0 && blue > 0) {
			blue--;
			genericRemaining--;
		}
		while (genericRemaining > 0 && red > 0) {
			red--;
			genericRemaining--;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const ManaPool& pool) {
		os << "[Mana: " << pool.red << "R, " << pool.blue << "B, " << pool.green << "G]";
		return os;
	}
};
