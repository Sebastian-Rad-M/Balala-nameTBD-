#pragma once
#include <iostream>
#include <memory>

#include "IEffect.h"
#include "RoundTracker.h"
class DrawCardEffect : public IEffect {
   private:
	int amount;

   public:
	explicit DrawCardEffect(int amt) : amount(amt) {}

	void resolve(RoundTracker& state) override {
		for (int i = 0; i < amount; i++) {
			state.drawCard();
		}
	}

	std::unique_ptr<IEffect> clone() const override {
		return std::make_unique<DrawCardEffect>(*this);
	}
};

class AddManaEffect : public IEffect {
   private:
	int red, blue, green;

   public:
	AddManaEffect(int r, int b, int g) : red(r), blue(b), green(g) {}

	void resolve(RoundTracker& state) override {
		// state.addMana(red, blue, green);
		/// TODO: mana system
		std::cout << "Adding Mana -> R:" << red << " B:" << blue << " G:" << green << "\n";
	}

	std::unique_ptr<IEffect> clone() const override {
		return std::make_unique<AddManaEffect>(*this);
	}
};
