#include "LightPool.h"

void ManaPool::addMana(int r, int b, int g) {
	red += r;
	blue += b;
	green += g;
}

void ManaPool::clearPool() {
	red = 0;
	blue = 0;
	green = 0;
}

bool ManaPool::canAfford(int costR, int costB, int costG, int costGeneric) const {
	if (red < costR || blue < costB || green < costG) {
		return false;
	}

	int leftoverR = red - costR;
	int leftoverB = blue - costB;
	int leftoverG = green - costG;
	int totalLeftover = leftoverR + leftoverB + leftoverG;

	return totalLeftover >= costGeneric;
}

// TODO: check if can afford first
void ManaPool::spendMana(int costR, int costB, int costG, int costGeneric) {
	red -= costR;
	blue -= costB;
	green -= costG;
	/// We drain Green first, then Blue, then Red (arbitrary priority).
	/// TODO:player chosen
	int genericRemaining = costGeneric;
	int* vars[3] = {&green, &blue, &red};
	for (size_t i = 0; i < 3; i++) {
		while (genericRemaining > 0 && *vars[i] > 0) {
			(*vars[i])--;
			genericRemaining--;
		}
	}
}
