#include <iostream>

#include "board.h"



int main() {
    std::cout << "Hello, World!, let us play a game" << std::endl;


    board game;

    auto displayStrings = game.getDisplay();

    for (const auto& displayString : displayStrings) {
        std::cout << displayString << std::endl;
    }

    std::array<board,7> futureGames;
    int futureGameCount = game.getFutureGames(futureGames,4);

    std::cout << "Number of Future Games: " << futureGameCount << std::endl;




    return 0;
}