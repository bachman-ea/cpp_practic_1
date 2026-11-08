#include <iostream>
#include <conio.h>
#include "gamestate.hpp"
#include "constants.hpp"

int main()
{ 
    enum Actions {
        RECEIVE_ITEMS = '1',
        SHOW_WAREHOUSE = '2',
        END_DAY = '3',
        SAVE_GAME = '4',
        LOAD_GAME = '5',
        EXIT = input_constants::KEY_RETURN,
        ESCAPE = input_constants::KEY_ESCAPE
    };

    GameState gameState{};
    while (gameState.getCurrentDay() <= gameplay_constants::DAY_COUNT) {
        std::system("cls");
        std::cout << "    Day " << gameState.getCurrentDay() << " | \033[33mGold " << gameState.getGold() << "\033[0m" << std::endl;
        std::cout << (gameState.isItemsRecieved() ? "\033[31m" : "\033[0m") << "[1] Receive daily items" << "\033[0m" << std::endl;
        std::cout << "[2] Warehouse" << std::endl;
        std::cout << "[3] Next day" << std::endl;
        std::cout << "[4] Save Game" << std::endl;
        std::cout << "[5] Load Game" << std::endl;
        std::cout << "[0/ESC] Exit" << std::endl;

        for (bool inChoice = true; inChoice;) {
            switch (_getch()) {
            case RECEIVE_ITEMS:
                inChoice = false;
                gameState.receivedailyItems();
                break;

            case SHOW_WAREHOUSE:
                inChoice = false;
                gameState.showWarehouse();
                break;

            case END_DAY:
                inChoice = false;
                gameState.endDay();
                break;

            case SAVE_GAME:
                inChoice = false;
                gameState.saveToFile();
                break;

            case LOAD_GAME:
                inChoice = false;
                gameState.loadFromFile();
                break;

            case EXIT:
                return 0;

            case ESCAPE:
                return 0;

            default:
                break;
            }
        }
    }
    std::cout << std::endl << "Total score " << gameState.calculateFinalScore() << std::endl;
    std::cout << "Press any key to exit..." << std::endl;
    char _ = _getch();
    return 0;
}
