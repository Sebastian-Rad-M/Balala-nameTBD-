#include "Effect.h"
//draw/discard
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
       if(state.promptDiscard());
       else {std::cout << "No cards to discard.\n";break;}
    }
}
std::unique_ptr<IEffect> DiscardEffect::clone() const {
    return std::make_unique<DiscardEffect>(*this);
}
/// mana 
AddManaEffect::AddManaEffect(int r, int b, int g) : red(r), blue(b), green(g) {}
void AddManaEffect::resolve(RoundTracker& state) {
    state.getManaPool().addMana(red, blue, green);
    std::cout << "Added Mana -> " << red << "R, " << blue << "B, " << green << "G\n";
}

std::unique_ptr<IEffect> AddManaEffect::clone() const {
    return std::make_unique<AddManaEffect>(*this);
}
///score
Score::Score(int score) : baseScore(score) {}
void Score::resolve(RoundTracker& state) {
    state.addScore(baseScore); 
}

std::unique_ptr<IEffect> Score::clone() const {
    return std::make_unique<Score>(*this);
}
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