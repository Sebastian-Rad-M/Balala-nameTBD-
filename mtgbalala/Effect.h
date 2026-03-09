#pragma once
#include <iostream>
#include <memory>

#include "IEffect.h"
#include "RoundTracker.h"

enum class CompareOp {
    LESS_THAN,          // < 
    GREATER_THAN,       // > 
    EQUALS,             // == 
    MODULO_EQUALS_ZERO  // %  == 0
};

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
	AddManaEffect(int r, int b, int g);
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class Score : public IEffect {
   private:
	int baseScore;

   public:
	explicit Score(int score);
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class StormEffect : public IEffect {
   private:
	std::unique_ptr<IEffect> baseEffect;  // WE ARE DEEP IN THE TRENCHES
   public:
	StormEffect(std::unique_ptr<IEffect> effect);
	void resolve(RoundTracker& state) override;
	std::unique_ptr<IEffect> clone() const override;
};

class ConditionalStormCheck : public IEffect {
private:
    CompareOp op;
    int targetValue;
    std::unique_ptr<IEffect> innerEffect;
	
	bool evaluateCondition(int currentStorm) const {
        switch (op) {
            case CompareOp::LESS_THAN: return currentStorm < targetValue;
            case CompareOp::GREATER_THAN: return currentStorm > targetValue;
            case CompareOp::EQUALS: return currentStorm == targetValue;
            case CompareOp::MODULO_EQUALS_ZERO: return currentStorm > 0 && (currentStorm % targetValue) == 0;
            default: return false;
        }
    }

    std::string getOpString() const {
        switch (op) {
            case CompareOp::LESS_THAN: return "<";
            case CompareOp::GREATER_THAN: return ">";
            case CompareOp::EQUALS: return "==";
            case CompareOp::MODULO_EQUALS_ZERO: return "% X == 0";
            default: return "?";
        }
    }
public:
    ConditionalStormCheck(CompareOp operation, int val, std::unique_ptr<IEffect> effect);
    void resolve(RoundTracker& state) override ;
    std::unique_ptr<IEffect> clone() const override;
};

class ApplyStatusEffect : public IEffect {
private:
    std::unique_ptr<IStatus> statusToApply;

public:
    ApplyStatusEffect(std::unique_ptr<IStatus> status);

    void resolve(RoundTracker& state) override ;

    std::unique_ptr<IEffect> clone() const override;
};

class GraveyardScaleEffect : public IEffect {
private:
    std::string searchedName;
    std::unique_ptr<IEffect> baseEffect;
public:
    GraveyardScaleEffect(std::string name, std::unique_ptr<IEffect> effect);
    void resolve(RoundTracker& state) override ;
    std::unique_ptr<IEffect> clone() const override;
};