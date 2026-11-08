#include <random>
#include "constants.hpp"
#include "magicitem.hpp"

MagicItem::MagicItem() : m_name{ "" }, m_type{ "" }, m_rarity{ "" }, m_base_price{ 0.0 }, m_day_added{ 0 }, m_color{ "" } {}

MagicItem::MagicItem(std::string name, std::string type, std::string rarity, double base_price, int current_day, std::string color)
	: m_name{ std::move(name) },
	  m_type{ std::move(type) },
	  m_rarity{ std::move(rarity) },
	  m_base_price{ base_price },
	  m_day_added{ current_day },
	  m_color{ std::move(color) }
{}

double MagicItem::currentValue(int current_day) const
{
	return m_base_price * (gameplay_constants::BASE_COEF + gameplay_constants::DAY_COEF * (current_day - m_day_added));
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

MagicItem GenerateItem(int current_day, std::mt19937& rng)
{
	std::uniform_int_distribution<int> dist_rarity(0, static_cast<int>(std::size(gameplay_constants::RARITIES)) - 1);
	const RarityInfo& rarity_info = gameplay_constants::RARITIES[dist_rarity(rng)];

	std::uniform_int_distribution<int> dist_type(0, static_cast<int>(std::size(gameplay_constants::ITEM_TYPES)) - 1);
	const std::string& type = gameplay_constants::ITEM_TYPES[dist_type(rng)];

	const auto& names_list = gameplay_constants::NAMES.at(type);
	std::uniform_int_distribution<int> dist_name(0, static_cast<int>(names_list.size()) - 1);
	int name_idx = dist_name(rng);

	return MagicItem{ names_list[name_idx], type, rarity_info.name, rarity_info.base_price, current_day, rarity_info.color };
}