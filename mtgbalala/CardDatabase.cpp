#include "CardDatabase.h"
#include "Effect.h"
#include "RNG.h"
#include "json.hpp"
using json = nlohmann::json;

CardDatabase& CardDatabase::getInstance() {
	static CardDatabase instance;
	return instance;
}

CardDatabase::CardDatabase() { loadAllCards(); }

void CardDatabase::loadAllCards() {
	// --- STARTER CARDS ---
	// name, genericCost, redCost, blueCost, greenCost, rarity
	Card basicRed("Basic Red", 0, 0, 0, 0, 'B');
	basicRed.addEffect(std::make_unique<ConditionalStormCheck>(
		CompareOp::LESS_THAN, 3, std::make_unique<AddManaEffect>(1, 0, 0)));
	library["c_basic_red"] = basicRed;

	Card basicBlue("Basic Blue", 0, 0, 0, 0, 'B');
	basicBlue.addEffect(std::make_unique<ConditionalStormCheck>(
		CompareOp::LESS_THAN, 3, std::make_unique<AddManaEffect>(0, 1, 0)));
	library["c_basic_blue"] = basicBlue;

	Card basicGreen("Basic Green", 0, 0, 0, 0, 'B');
	basicGreen.addEffect(std::make_unique<ConditionalStormCheck>(
		CompareOp::LESS_THAN, 3, std::make_unique<AddManaEffect>(0, 0, 1)));
	library["c_basic_green"] = basicGreen;

	// --- COMMON CARDS ---
	Card gitaxianProbe("Gitaxian Probe", 0, 0, 0, 0, 'C');
	gitaxianProbe.addEffect(std::make_unique<DrawCardEffect>(1));
	library["c_gitaxian_probe"] = gitaxianProbe;

	Card divination("Divination", 1, 0, 1, 0, 'C');
	divination.addEffect(std::make_unique<DrawCardEffect>(2));
	library["c_divination"] = divination;

	Card grapeshot("Grapeshot", 0, 1, 0, 0, 'C');
	grapeshot.addEffect(std::make_unique<Score>(5));
	grapeshot.addEffect(std::make_unique<StormEffect>(std::make_unique<Score>(50)));
	library["c_grapeshot"] = grapeshot;

	Card riteOfFlame("Rite of Flame", 0, 1, 0, 0, 'C');
	riteOfFlame.addEffect(std::make_unique<AddManaEffect>(2, 0, 0));
	riteOfFlame.addEffect(std::make_unique<GraveyardScaleEffect>(
		"Rite of Flame", std::make_unique<AddManaEffect>(1, 0, 0)));
	library["c_rite_of_flame"] = riteOfFlame;

	Card lightingBolt("Lightning Bolt", 0, 1, 0, 0, 'C');
	lightingBolt.addEffect(std::make_unique<Score>(10));
	library["c_lighting_bolt"] = lightingBolt;

	Card franticSearch("Frantic_Search", 2, 0, 1, 0, 'C');
	franticSearch.addEffect(std::make_unique<DrawCardEffect>(2));
	franticSearch.addEffect(std::make_unique<AddManaEffect>(1, 1, 1));
	franticSearch.addEffect(std::make_unique<DiscardEffect>(2));
	library["c_frantic_search"] = franticSearch;

	Card manamorphose("Manamorphose", 1, 1, 0, 0, 'C');
	manamorphose.addEffect(std::make_unique<DrawCardEffect>(1));
	manamorphose.addEffect(std::make_unique<AddManaEffect>(1, 1, 0));
	library["c_manamorphose"] = manamorphose;  // maybe make it an uncommon and get of any color?
	// Uncommons
	Card overcharge("Overcharge", 0, 1, 1, 0, 'U');
	overcharge.addEffect(
		std::make_unique<ApplyStatusEffect>(std::make_unique<OverchargeStatus>(1)));
	library["c_overcharge"] = overcharge;

	// Rares and Legendaries
	Card ancestralRecall("Ancestral Recall", 0, 0, 1, 0, 'R');
	ancestralRecall.addEffect(std::make_unique<DrawCardEffect>(3));
	library["c_ancestral_recall"] = ancestralRecall;

	Card blackLotus("Black Lotus", 0, 0, 0, 0, 'L');
	blackLotus.addEffect(std::make_unique<AddManaEffect>(3, 3, 3));
	library["c_black_lotus"] = blackLotus;

	// TODO: JSON PARSER
}
std::shared_ptr<Card> CardDatabase::createCard(const std::string& cardID) {
	if (library.find(cardID) != library.end()) {
		return std::make_shared<Card>(library[cardID]);
	}
	std::cerr << "Error: Card ID " << cardID << " not found!\n";
	return nullptr;
}

std::shared_ptr<Card> CardDatabase::getTrueRandomCard() {
	if (library.empty()) {
		return nullptr;
	}
	int randomIndex = RNG::range(0, library.size() - 1);
	auto rCard = library.begin();
	std::advance(rCard, randomIndex);
	return std::make_shared<Card>(rCard->second);
}

std::shared_ptr<Card> CardDatabase::getRandomCard() {
	if (library.empty()) {
		return nullptr;
	}
	int totalWeight = 0;
	for (const auto& pair : library) {
		char r = pair.second.getRarity();

		if (r == 'B') {
			continue;  // Basics = 0
		} else if (r == 'C') {
			totalWeight += 60;	// Commons = 60%
		} else if (r == 'U') {
			totalWeight += 30;	// Uncommons = 30%
		} else if (r == 'R') {
			totalWeight += 10;	// Rares = 10%
		} else if (r == 'L') {
			totalWeight += 1;  // Legendaries = 1%
		}
	}
	if (totalWeight == 0) {
		std::cerr << "  [!] Error: No draftable cards in the database!\n";
		return nullptr;
	}

	int winningTicket = RNG::range(1, totalWeight);
	int currentWeight = 0;
	for (const auto& pair : library) {
		char r = pair.second.getRarity();

		if (r == 'B') {
			continue;
		}
		if (r == 'C') {
			currentWeight += 60;
		} else if (r == 'U') {
			currentWeight += 30;
		} else if (r == 'R') {
			currentWeight += 10;
		} else if (r == 'L') {
			currentWeight += 1;
		}
		if (currentWeight >= winningTicket) {
			return std::make_shared<Card>(pair.second);
		}
	}

	return nullptr;	 // Fallback
					 /// TODO: error handling
}
