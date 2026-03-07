#pragma once
#include <iostream>

// RunTracker – 1+ rounds

class RunTracker {
   private:
	int currentRound = 1;
	int roundsWon = 0;

   public:
	void roundWon() { roundsWon++; }
	void advanceRound() { currentRound++; }
	int targetScore() const {
		return 100 + (currentRound - 1) *
						 50;  /// formula mega provizorie, probabil o sa fie ceva cu exponentiala
	}
	void reset() {
		currentRound = 1;
		roundsWon = 0;
	}

	void printStatus() const {
		std::cout << "  Run   : Round " << currentRound << "  (won: " << roundsWon << ")\n";
	}
};
