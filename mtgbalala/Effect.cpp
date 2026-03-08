#include "Effect.h"

void DrawCardEffect::resolve(RoundTracker& state) {
    for (int i = 0; i < amount; i++) {
        state.drawCard();
    }
}

std::unique_ptr<IEffect> DrawCardEffect::clone() const {
    return std::make_unique<DrawCardEffect>(*this);
}


AddManaEffect::AddManaEffect(int r, int b, int g) : red(r), blue(b), green(g) {}
void AddManaEffect::resolve(RoundTracker& state) {
    state.getManaPool().addMana(red, blue, green);
    std::cout << "Added Mana -> " << red << "R, " << blue << "B, " << green << "G\n";
}

std::unique_ptr<IEffect> AddManaEffect::clone() const {
    return std::make_unique<AddManaEffect>(*this);
}
