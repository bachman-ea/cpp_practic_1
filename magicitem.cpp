#include <random>
#include "magicitem.hpp"

MagicItem::MagicItem() : m_name{ "" }, m_type{ "" }, m_rarity{ "" }, m_base_price{ 0.0 }, m_day_added{ 0 }, m_color{ "" } {}

MagicItem::MagicItem(std::string name, std::string type, std::string rarity, double base_price, int current_day, std::string color) : m_name{ std::move(name) }, m_type{ std::move(type) }, m_rarity{ std::move(rarity) }, m_base_price{ std::move(base_price) }, m_day_added{ std::move(current_day) }, m_color{ std::move(color) } {}

double MagicItem::currentValue(int current_day) const
{
	return m_base_price * (1.0 + 0.5 * (current_day - m_day_added));
}

const std::string& MagicItem::getName() const
{
	return m_name;
}

const std::string& MagicItem::getType() const
{
	return m_type;
}

const std::string& MagicItem::getRarity() const
{
	return m_rarity;
}

double MagicItem::getBasePrice() const
{
	return m_base_price;
}

int MagicItem::getDayAdded() const
{
	return m_day_added;
}

const std::string& MagicItem::getColor() const
{
	return m_color;
}

MagicItem GenerateItem(int current_day)
{
	static std::mt19937 gen(std::random_device{}());

	static std::uniform_int_distribution<int> dist_rarity(0, 2);
	static std::uniform_int_distribution<int> dist_type(0, 3);
	static std::uniform_int_distribution<int> dist_name(0, 9);

	static constexpr RarityInfo rarities[3]{
		{ "common", 75.0, "\033[0m" },
		{ "rare", 140.0, "\033[34m" },
		{ "epic", 230.0, "\033[35m" }
	};

	static const char* const types[4]{ "weapon", "armor", "potion", "scroll" };

	static const char* const names[4][10]{
		{ "Dragon Blade", "Storm Bow", "Shadow Dagger", "Titan Hammer", "Frost Staff", "Sun Spear", "Executioner Axe", "Dawn Sword", "Doom Crossbow", "Thunder Mace" },
		{ "Titan Cuirass", "Guardian Shield", "Gladiator Helm", "Sage Robe", "Iron Greaves", "Shadow Mail", "Knight Gauntlets", "Dragon Scale Armor", "Belt of Fortitude", "Amulet of Ward" },
		{ "Healing Potion", "Mana Draught", "Swiftness Tonic", "Strength Elixir", "Invisibility Brew", "Elixir of Life", "Fire Resistance Flask", "Antidote", "Stone Skin Brew", "Poison Vial" },
		{ "Scroll of Fireball", "Scroll of Teleport", "Scroll of Healing", "Scroll of Lightning", "Scroll of Blizzard", "Scroll of Shield", "Scroll of Inferno", "Scroll of Summoning", "Scroll of Purge", "Scroll of Resurrection" } 
	};

	const auto& rarity_info = rarities[dist_rarity(gen)];
	int type_idx = dist_type(gen);
	int name_idx = dist_name(gen);

	return MagicItem{
		names[type_idx][name_idx],
		types[type_idx],
		rarity_info.name,
		rarity_info.base_price,
		current_day,
		rarity_info.color
	};
}
