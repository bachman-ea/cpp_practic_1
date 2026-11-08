#pragma once

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <random>
#include "magicitem.hpp"
#include "constants.hpp"

class GameState {

public:
	GameState();

	void receivedailyItems();
	
	void showWarehouse();

	void endDay();

	double calculateFinalScore();

	bool saveToFile();

	bool loadFromFile();

	int getCurrentDay() const;
	double getGold() const;
	bool isItemsRecieved() const;
	
private:
	int m_current_day;
	double m_gold;
	bool m_items_recieved_today;
	int m_item_count;
	MagicItem m_warehouse[gameplay_constants::WAREHOUSE_CAPACITY];
	std::mt19937 m_rng;

	void sellFromWarehouse(int slot);
};

#endif // GAMESTATE_HPP
