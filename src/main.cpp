#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "board.h"
#include "player.h"
#include "playGame.h"


int main() {

    //Intentionally using default seed for now
    std::default_random_engine generator(0);

    std::cout << "Hello, World!, let us play a game" << std::endl;

    std::ifstream brainFile ("brain.txt");

    if (!brainFile.is_open()) {
        std::cerr << "Can't open brain.txt; you should execute the program from the folder where it exists" << std::endl;
        return 1;
    }

    //The people who will play this game
    std::array<player,2> players = {player(0,false),player(1,true,brainFile)};


    int turn=0;
    const auto start = std::chrono::high_resolution_clock::now();
    bool win = playGame(true,players,generator,turn);
    const auto stop= std::chrono::high_resolution_clock::now();
    const auto duration = stop-start;

    std::cout << "Player " << (win ? "1" : "0") << " wins!, in "<<turn<<" turns and "<<(duration_cast<std::chrono::nanoseconds>(duration)).count()<<" ns"<< std::endl;
    return 0;
}