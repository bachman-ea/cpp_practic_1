#include <iostream>
#include <iomanip>
#include <conio.h>
#include <fstream>
#include "constants.hpp"
#include "gamestate.hpp"

GameState::GameState() : m_current_day{ 1 }, m_gold{ 0.0 }, m_items_recieved_today{ false }, m_item_count{ 0 }, m_warehouse{ } {}

void GameState::receivedailyItems()
{
	enum Action {
		RECIEVE = '1',
		SELL = '0'
	};

	if (m_items_recieved_today) {
		std::cout << "Daily items already recieved" << std::endl;
		std::cout << "Press any key to continue..." << std::endl;
		char _ = _getch();
		return;
	}
	m_items_recieved_today = true;

	std::cout << std::endl;
	for (int i = 0; i < gameplay_constants::ITEMS_PER_DAY; i++) {
		MagicItem item{ GenerateItem(m_current_day) };
		std::cout << std::setw(technical_constants::NAME_OFFSET) << std::left << item.getName() << " | " <<
			std::setw(technical_constants::TYPE_OFFSET) << std::left << item.getType() << " | " <<
			item.getColor() << std::setw(technical_constants::RARITY_OFFSET) << std::left << item.getRarity() << "\33[0m => " << item.getBasePrice() << std::endl;
		std::cout << "[1] Recieve" << std::endl;
		std::cout << "[0] Sell for " << item.getBasePrice() / 2 << std::endl;
		for (bool inChoice = true; inChoice;) {
			switch (_getch()) {
			case RECIEVE:
				if (m_item_count == 5) {
					m_gold += item.getBasePrice() / 2;
					std::cout << "Warehouse is full, item was selled for " << item.getBasePrice() / 2 << std::endl;
				}
				else {
					m_warehouse[m_item_count] = item;
					m_item_count++;
				}
				inChoice = false;
				break;

			case SELL:
				m_gold += item.getBasePrice() / 2;
				inChoice = false;
				break;

			default:
				break;
			}
		}
	}
	std::cout << "Press any key to continue..." << std::endl;
	char _ = _getch();
}

void GameState::showWarehouse()
{
	for (bool inWarehouse = true; inWarehouse;) {
		std::system("cls");
		std::cout << "Warehouse [select item to sell it]:" << std::endl;
		for (int i = 0; i < m_item_count; i++)
			std::cout << (m_warehouse[i].getDayAdded() - m_current_day == 0 ? "\33[31m" : "\33[0m") << "[" << i + 1 << "] " << "\33[0m" <<
			std::setw(technical_constants::NAME_OFFSET) << std::left << m_warehouse[i].getName() << " | " <<
			std::setw(technical_constants::TYPE_OFFSET) << std::left << m_warehouse[i].getType() << " | " <<
			m_warehouse[i].getColor() << std::setw(technical_constants::RARITY_OFFSET) << std::left << m_warehouse[i].getRarity() << "\33[0m | Day " << m_warehouse[i].getDayAdded() << " => " << m_warehouse[i].currentValue(m_current_day) << std::endl;
		std::cout << std::endl << "[0] Return" << std::endl;
		for (bool inChoice = true; inChoice;) {
			char input = _getch();
			if (isdigit(input) && input - '0' <= m_item_count && input - '0' > 0) {
				sellFromWarehouse(input - '0' - 1);
				inChoice = false;
			}
			else if (input == '0' || input == 27) {
				inChoice = false;
				inWarehouse = false;
			}
		}
	}
}

void GameState::sellFromWarehouse(int slot)
{
	if (0 <= slot && slot <= (m_item_count - 1))
		if (m_warehouse[slot].getDayAdded() < m_current_day) {
			m_gold += m_warehouse[slot].currentValue(m_current_day);
			for (int i = slot; i < m_item_count; i++)
				m_warehouse[i] = m_warehouse[i + 1];
			m_item_count--;
		}
}

void GameState::endDay()
{
	m_current_day++;
	m_items_recieved_today = false;
}

double GameState::calculateFinalScore()
{
	double final_sum = m_gold;
	for (int i = 0; i < m_item_count; i++)
		final_sum += m_warehouse[i].currentValue(m_current_day);
	return final_sum;
}

bool GameState::saveToFile()
{
	std::ofstream out("save.txt");
	if (out.is_open()) {
		out << "current_day=" << m_current_day << std::endl;
		out << "gold=" << m_gold << std::endl;
		out << "items_received_today=" << m_items_recieved_today << std::endl;
		out << "item_count=" << m_item_count << std::endl;
		for (int i = 0; i < m_item_count; i++) {
			out << "item_name=" << m_warehouse[i].getName() << std::endl;
			out << "item_type=" << m_warehouse[i].getType() << std::endl;
			out << "item_rarity=" << m_warehouse[i].getRarity() << std::endl;
			out << "item_base_price=" << m_warehouse[i].getBasePrice() << std::endl;
			out << "day_added=" << m_warehouse[i].getDayAdded() << std::endl;
			out << "color=" << m_warehouse[i].getColor() << std::endl;
		}
	}
	else
		return false;
	out.close();
	return true;
}

bool GameState::loadFromFile()
{
	std::ifstream in("save.txt");
	if (in.is_open()) {
		std::string line;
		std::getline(in, line);
		m_current_day = std::stoi(line.substr(line.find("=") + 1));
		std::getline(in, line);
		m_gold = std::stod(line.substr(line.find("=") + 1));
		std::getline(in, line);
		m_items_recieved_today = std::stoi(line.substr(line.find("=") + 1));
		std::getline(in, line);
		m_item_count = std::stoi(line.substr(line.find("=") + 1));
		for (int i = 0; i < m_item_count; i++) {
			std::getline(in, line);
			std::string name{ line.substr(line.find("=") + 1) };
			std::getline(in, line);
			std::string type{ line.substr(line.find("=") + 1) };
			std::getline(in, line);
			std::string rarity{ line.substr(line.find("=") + 1) };
			std::getline(in, line);
			double base_price{ std::stod(line.substr(line.find("=") + 1)) };
			std::getline(in, line);
			int day_added{ std::stoi(line.substr(line.find("=") + 1)) };
			std::getline(in, line);
			std::string color{ line.substr(line.find("=") + 1) };
			m_warehouse[i] = { name, type, rarity, base_price, day_added, color };
		}
	}
	else
		return false;
	in.close();
	return true;
}

int GameState::getCurrentDay() const
{
	return m_current_day;
}

double GameState::getGold() const
{
	return m_gold;
}

bool GameState::isItemsRecieved() const
{
	return m_items_recieved_today;
}
