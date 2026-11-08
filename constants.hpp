#pragma once

#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <map>
#include <vector>
#include <string>
#include "magicitem.hpp"

namespace gameplay_constants {
	const int DAY_COUNT = 3;
	const int ITEMS_PER_DAY = 3;
	const int WAREHOUSE_CAPACITY = 5;

	const int START_DAY = 1;
	const double START_GOLD = 0.0;

	const double BASE_COEF = 1.0;
	const double DAY_COEF = 0.5;
	const double INSTANT_SELL_COEFF = 0.5;

	inline const std::vector<std::string> ITEM_TYPES{ "weapon", "armor", "potion", "scroll" };

	inline const std::map<std::string, std::vector<std::string>> NAMES{
			{ "weapon",  {"Dragon Blade", "Storm Bow", "Shadow Dagger", "Titan Hammer", "Frost Staff", "Sun Spear", "Executioner Axe", "Dawn Sword", "Doom Crossbow", "Thunder Mace"}},
			{ "armor",  {"Titan Cuirass", "Guardian Shield", "Gladiator Helm", "Sage Robe", "Iron Greaves", "Shadow Mail", "Knight Gauntlets", "Dragon Scale Armor", "Belt of Fortitude", "Amulet of Ward"}},
			{ "potion",  {"Healing Potion", "Mana Draught", "Swiftness Tonic", "Strength Elixir", "Invisibility Brew", "Elixir of Life", "Fire Resistance Flask", "Antidote", "Stone Skin Brew", "Poison Vial"}},
			{ "scroll",  {"Scroll of Fireball", "Scroll of Teleport", "Scroll of Healing", "Scroll of Lightning", "Scroll of Blizzard", "Scroll of Shield", "Scroll of Inferno", "Scroll of Summoning", "Scroll of Purge", "Scroll of Resurrection"} }
	};

	inline const RarityInfo RARITIES[]{
			{ "common", 75.0, "\033[0m" },
			{ "rare", 140.0, "\033[34m" },
			{ "epic", 230.0, "\033[35m" }
	};
}

namespace input_constants {
	const char KEY_ESCAPE = 27;
	const char KEY_RETURN = '0';
}

static std::size_t compute_name_offset() {
	std::size_t max_len = 0;
	for (auto const& pair : gameplay_constants::NAMES) {
		for (const auto& item_name : pair.second) {
			max_len = item_name.length() > max_len ? item_name.length() : max_len;
		}
	}
	return max_len;
}

static std::size_t compute_type_offset() {
	std::size_t max_len = 0;
	for (auto const& pair : gameplay_constants::NAMES)
		max_len = pair.first.length() > max_len ? pair.first.length() : max_len;
	return max_len;
}

static std::size_t compute_rarity_offset() {
	std::size_t max_len = 0;
	for (RarityInfo const& rarityInfo : gameplay_constants::RARITIES)
		max_len = rarityInfo.name.length() > max_len ? rarityInfo.name.length() : max_len;
	return max_len;
}

namespace technical_constants {
	const std::size_t NAME_OFFSET = compute_name_offset();
	const std::size_t TYPE_OFFSET = compute_type_offset();
	const std::size_t RARITY_OFFSET = compute_rarity_offset();
}

#endif // CONSTANTS_HPP
