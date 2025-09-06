#include <chrono>
#include <iostream>
#include <random>

#include "board.h"
#include "player.h"
#include "playGame.h"


int main() {

    //Intentionally using default seed for now
    std::default_random_engine generator(0);

    std::cout << "Hello, World!, let us play a game" << std::endl;


    //The people who will play this game
    std::array<player,2> players = {player(0,true),player(1,true)};

    int turn=0;
    const auto start = std::chrono::high_resolution_clock::now();
    bool win = playGame(false,players,generator,turn);
    const auto stop= std::chrono::high_resolution_clock::now();
    const auto duration = stop-start;

    std::cout << "Player " << (win ? "1" : "0") << " wins!, in "<<turn<<" turns and "<<(duration_cast<std::chrono::nanoseconds>(duration)).count()<<" ns"<< std::endl;
    return 0;
}