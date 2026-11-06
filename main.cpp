#include <iostream>
#include <conio.h>
#include "gamestate.hpp"

static enum Actions {
    RECIEVE_ITEMS = 49,
    SHOW_WAREHOUSE = 50,
    END_DAY = 51,
    SAVE_GAME = 52,
    LOAD_GAME = 53,
    EXIT = 48,
    ESCAPE = 27
};

int main()
{ 
    GameState gameState{};
    while (gameState.getCurrentDay() <= 3) {
        std::system("cls");
        std::cout << "    Day " << gameState.getCurrentDay() << " | \033[33mGold " << gameState.getGold() << "\033[0m" << std::endl;
        std::cout << (gameState.isItemsRecieved() ? "\033[31m" : "\033[0m") << "[1] Recieve daily items" << "\033[0m" << std::endl;
        std::cout << "[2] Warehouse" << std::endl;
        std::cout << "[3] Next day" << std::endl;
        std::cout << "[4] Save Game" << std::endl;
        std::cout << "[5] Load Game" << std::endl;
        std::cout << "[0/ESC] Exit" << std::endl;

        switch ((Actions)_getch()) {
        case RECIEVE_ITEMS:
            gameState.receivedailyItems();
            break;

        case SHOW_WAREHOUSE:
            gameState.showWarehouse();
            break;

        case END_DAY:
            gameState.endDay();
            break;

        case SAVE_GAME:
            gameState.saveToFile();
            break;

        case LOAD_GAME:
            gameState.loadFromFile();
            break;

        case EXIT:
            return 0;

        case ESCAPE:
            return 0;
        }
    }
    std::cout << std::endl << "Total score " << gameState.calculateFinalScore() << std::endl;
    std::cout << "Press any key to exit..." << std::endl;
    char _ = _getch();
    return 0;
}