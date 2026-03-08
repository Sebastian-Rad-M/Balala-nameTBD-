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