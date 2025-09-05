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

    std::array<std::array<std::string,18> ,7> FutureDisplayStrings;

    for (int i = 0 ; i < futureGameCount ; i++) {
        FutureDisplayStrings[i] = futureGames[i].getDisplay();
    }

    for (int j = 0 ; j < 18 ; j++) {
        for (int i = 0 ; i < futureGameCount ; i++) {
            std::cout << FutureDisplayStrings[i][j] << " | ";
        }
        std::cout << std::endl;
    }
    return 0;
}