#include "Effect.h"
// draw/discard
void DrawCardEffect::resolve(RoundTracker& state) {
	for (int i = 0; i < amount; i++) {
		state.drawCard();
	}
}

std::unique_ptr<IEffect> DrawCardEffect::clone() const {
	return std::make_unique<DrawCardEffect>(*this);
}

void DiscardEffect::resolve(RoundTracker& state) {
	for (int i = 0; i < amount; i++) {
		if (state.promptDiscard())
			;
		else {
			std::cout << "No cards to discard.\n";
			break;
		}
	}
}
std::unique_ptr<IEffect> DiscardEffect::clone() const {
	return std::make_unique<DiscardEffect>(*this);
}
/// mana
AddManaEffect::AddManaEffect(int r, int b, int g) : red(r), blue(b), green(g) {}
void AddManaEffect::resolve(RoundTracker& state) {
	state.addMana(red, blue, green);
	std::cout << "Added Mana -> " << red << "R, " << blue << "B, " << green << "G\n";
}

std::unique_ptr<IEffect> AddManaEffect::clone() const {
	return std::make_unique<AddManaEffect>(*this);
}
/// score
Score::Score(int score) : baseScore(score) {}
void Score::resolve(RoundTracker& state) { state.addScore(baseScore); }

std::unique_ptr<IEffect> Score::clone() const { return std::make_unique<Score>(*this); }
/// storm
StormEffect::StormEffect(std::unique_ptr<IEffect> effect) : baseEffect(std::move(effect)) {}

void StormEffect::resolve(RoundTracker& state) {
	int storm = state.getStormCount();
	for (int i = 0; i < storm; ++i) {
		baseEffect->resolve(state);
	}
}

std::unique_ptr<IEffect> StormEffect::clone() const {
	return std::make_unique<StormEffect>(baseEffect->clone());
}

ConditionalStormCheck::ConditionalStormCheck(CompareOp operation, int val, std::unique_ptr<IEffect> effect) 
        : op(operation), targetValue(val), innerEffect(std::move(effect)) {}

    void ConditionalStormCheck::resolve(RoundTracker& state) {
        int storm = state.getStormCount();
        
        if (evaluateCondition(storm)) {
            innerEffect->resolve(state);
        } else {
            
            std::cout << "[Nope! Storm count (" << storm << ") did not meet condition: " 
                      << getOpString() << " " << targetValue << "]\n";
        }
    }

    std::unique_ptr<IEffect> ConditionalStormCheck::clone() const {
        return std::make_unique<ConditionalStormCheck>(op, targetValue, innerEffect->clone());
    }

    GraveyardScaleEffect::GraveyardScaleEffect(std::string name, std::unique_ptr<IEffect> effect) 
        : searchedName(name), baseEffect(std::move(effect)) {}
    
    void GraveyardScaleEffect::resolve(RoundTracker& state) {
        int count = 0;

        const auto& grave = state.getGraveyard().getCards();
        for (const auto& card : grave) {
            if (card->getName() == searchedName) {
                count++;
            }
        }
        
        if (count > 0) {
           
            for (int i = 0; i < count; ++i) {
                baseEffect->resolve(state);
            }
        }
    }
    
    std::unique_ptr<IEffect> GraveyardScaleEffect::clone() const {
        return std::make_unique<GraveyardScaleEffect>(searchedName, baseEffect->clone());
    }
    ApplyStatusEffect::ApplyStatusEffect(std::unique_ptr<IStatus> status) 
        : statusToApply(std::move(status)) {}

    void ApplyStatusEffect::resolve(RoundTracker& state) {
        std::cout << " Gained status: " << statusToApply->getName() << "!\n";
        state.addStatus(statusToApply->clone());
    }

    std::unique_ptr<IEffect> ApplyStatusEffect::clone() const {
        return std::make_unique<ApplyStatusEffect>(statusToApply->clone());
    }