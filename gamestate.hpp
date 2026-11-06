#pragma once

#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "magicitem.hpp"

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
	MagicItem m_warehouse[5];

	void sellFromWarehouse(int slot);
};

#endif // GAMESTATE_HPP
