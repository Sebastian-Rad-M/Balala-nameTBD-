#pragma once
#include "IEffect.h"
#include "RoundTracker.h"

enum class CompareOp { LESS_THAN, GREATER_THAN, EQUALS, MODULO_EQUALS_ZERO };

class DrawCardEffect : public IEffect {
   private:
	int amount;

   public:
	explicit DrawCardEffect(int amt) : amount(amt) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class DiscardEffect : public IEffect {
   private:
	int amount;

   public:
	explicit DiscardEffect(int amt) : amount(amt) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class AddManaEffect : public IEffect {
   private:
	int red, blue, green;

   public:
	AddManaEffect(int r, int b, int g) : red(r), blue(b), green(g) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class Score : public IEffect {
   private:
	int baseScore;

   public:
	Score(int score) : baseScore(score) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class StormEffect : public IEffect {
   private:
	std::unique_ptr<IEffect> baseEffect;  // WE ARE DEEP IN THE TRENCHES
   public:
	StormEffect(std::unique_ptr<IEffect> effect) : baseEffect(std::move(effect)) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class ConditionalStormCheck : public IEffect {
	// TODO: transform this into coditional anythign and have to pass a getstorm
   private:
	CompareOp op;
	int targetValue;
	std::unique_ptr<IEffect> innerEffect;

	bool evaluateCondition(const int currentStorm) const {
		switch (op) {
			case CompareOp::LESS_THAN:
				return currentStorm < targetValue;
			case CompareOp::GREATER_THAN:
				return currentStorm > targetValue;
			case CompareOp::EQUALS:
				return currentStorm == targetValue;
			case CompareOp::MODULO_EQUALS_ZERO:
				return currentStorm > 0 && (currentStorm % targetValue) == 0;
			default:
				return false;
		}
	}

   public:
	ConditionalStormCheck(const CompareOp operation, const int val, std::unique_ptr<IEffect> effect)
		: op(operation), targetValue(val), innerEffect(std::move(effect)) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class ApplyStatusEffect : public IEffect {
   private:
	std::unique_ptr<IStatus> statusToApply;

   public:
	ApplyStatusEffect(std::unique_ptr<IStatus> status) : statusToApply(std::move(status)) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class GraveyardScaleEffect : public IEffect {
   private:
	std::string searchedName;
	std::unique_ptr<IEffect> baseEffect;

   public:
	GraveyardScaleEffect(const std::string& name, std::unique_ptr<IEffect> effect)
		: searchedName(name), baseEffect(std::move(effect)) {}
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};
