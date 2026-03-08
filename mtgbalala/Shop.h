#pragma once
#include <vector>
#include <memory>
#include "CardDatabase.h"
#include "RelicFactory.h"
#include "PlayerInfo.h"

enum class BuyResult { SUCCESS, NO_GOLD, SOLD_OUT, INVALID };

template <typename T>
struct ShopItem {
    std::shared_ptr<T> item;
    int price;
    bool isSold = false;
};

class Shop {
private:
    std::vector<ShopItem<Card>> cardStock;
    std::vector<ShopItem<IRelic>> relicStock;

public:
    void generateRandomStock() ;

    const std::vector<ShopItem<Card>>& getCards() const ;
    const std::vector<ShopItem<IRelic>>& getRelics() const;

    BuyResult buyCard(int index, PlayerInfo& player) ;

    BuyResult buyRelic(int index, PlayerInfo& player) ;
};