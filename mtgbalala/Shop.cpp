
#include <memory>
#include <vector>

#include "CardDatabase.h"
#include "RelicFactory.h"
#include "Shop.h"

void Shop::generateRandomStock() {
	cardStock.clear();
	relicStock.clear();
	// TODO: make price based on rarity
	cardStock.push_back({CardDatabase::getInstance().getRandomCard(), 3, false});
	cardStock.push_back({CardDatabase::getInstance().getRandomCard(), 4, false});
	relicStock.push_back({RelicDatabase::getInstance().getRandomRelic(), 10, false});
}

const std::vector<ShopItem<Card>>& Shop::getCards() const { return cardStock; }
const std::vector<ShopItem<IRelic>>& Shop::getRelics() const { return relicStock; }

BuyResult Shop::buyCard(int index, PlayerInfo& player) {
	if (index < 0 || index >= cardStock.size()) {
		return BuyResult::INVALID;
	}
	if (cardStock[index].isSold) {
		return BuyResult::SOLD_OUT;
	}

	if (player.spendGold(cardStock[index].price)) {
		player.getDeck().addCard(cardStock[index].item);
		cardStock[index].isSold = true;
		return BuyResult::SUCCESS;
	}
	return BuyResult::NO_GOLD;
}

BuyResult Shop::buyRelic(int index, PlayerInfo& player) {
	if (index < 0 || index >= relicStock.size()) {
		return BuyResult::INVALID;
	}
	if (relicStock[index].isSold) {
		return BuyResult::SOLD_OUT;
	}

	if (player.spendGold(relicStock[index].price)) {
		if (player.getRelicZone().addRelic(relicStock[index].item)) {
			relicStock[index].isSold = true;
			return BuyResult::SUCCESS;
		} else {
			player.addGold(relicStock[index].price);  // Refund if zone is full
			return BuyResult::INVALID;				  // Or a new "ZONE_FULL" enum!
		}
	}
	return BuyResult::NO_GOLD;
}
