#pragma once
#include "Effect.h"

class RiteOfFlameEffect : public IEffect {
   private:
	int bonusMana = 0;

   public:
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
	void incrementBonus() { bonusMana++; }
	void resetBonus() { bonusMana = 0; }
};
