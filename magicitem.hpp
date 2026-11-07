#pragma once

#ifndef MAGICITEM_HPP
#define MAGICITEM_HPP

#include <string>

class MagicItem {

public:
	MagicItem();

	MagicItem(std::string name, std::string type, std::string rarity, double base_price, int current_day, std::string color);

	double currentValue(int current_day) const;

	const std::string& getName() const;
	const std::string& getType() const;
	const std::string& getRarity() const;
	double getBasePrice() const;
	int getDayAdded() const;
	const std::string& getColor() const;

private:
	std::string m_name;
	std::string m_type;
	std::string m_rarity;
	double m_base_price;
	int m_day_added;
	std::string m_color;
};

struct RarityInfo {
	const std::string name;
	double base_price;
	const std::string color;
};

MagicItem GenerateItem(int current_day);

#endif // MAGICITEM_HPP
