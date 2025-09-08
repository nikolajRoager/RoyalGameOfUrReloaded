#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "board.h"
#include "player.h"
#include "playGame.h"


int main() {

    bool graphics = false;
    bool player0isBot = true;
    bool player1isBot = true;

    //Intentionally using default seed for now
    std::default_random_engine generator(0);

    std::cout << "Hello, World!, let us play a game" << std::endl;

    //Ask the human if player 0 or 1 are bots
    std::cout<< "Is player 0 bot controlled? (y/n)"<<std::endl;
    std::string input = "";
    while (input!="y" && input!="n") {
        std::getline(std::cin,input);
    }
    if (input=="y") {
        player0isBot = true;
    }
    else {
        player0isBot = false;
        graphics=true;
    }

    std::cout<< "Is player 1 bot controlled? (y/n)"<<std::endl;
    input = "";
    while (input!="y" && input!="n") {
        std::getline(std::cin,input);
    }
    if (input=="y") {
        player1isBot = true;
    }
    else {
        player1isBot = false;
        graphics=true;
    }

    if (!graphics) {
        std::cout<< "Do you want to view a single bot-vs-bot game? if not we will run 1000 tests(y/n)"<<std::endl;
        input = "";
        while (input!="y" && input!="n") {
            std::getline(std::cin,input);
        }
        if (input=="y") {
            graphics=true;
        }
        else {
            graphics=false;
        }

    }

    std::ifstream brainFile ("brain.txt");

    if (!brainFile.is_open()) {
        std::cerr << "Can't open brain.txt; you should execute the program from the folder where it exists" << std::endl;
        return 1;
    }

    //The people who will play this game
    std::array<player,2> players = {player(0,player0isBot,brainFile),player(1,player1isBot,brainFile)};

    //A single game, with graphics turned on
    if (graphics || players[0].isHuman() || players[1].isHuman()) {
        int turn=0;
        const auto start = std::chrono::high_resolution_clock::now();
        bool win = playGame(true,players,generator,turn);
        const auto stop= std::chrono::high_resolution_clock::now();
        const auto duration = stop-start;

        std::cout << "Player " << (win ? "1" : "0") << " wins!, in "<<turn<<" turns and "<<(duration_cast<std::chrono::seconds>(duration)).count()<<" s"<< std::endl;
    }
    //Or a bunch of games with graphics turned off
    else {
        int repeats = 1000;
        int totalTurns = 0;
        int player1Wins = 0;

            const auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < repeats; ++i) {
            int turn=0;

            if ( playGame(false,players,generator,turn)) {
                ++player1Wins;
            }
            totalTurns+=turn;
        }
        const auto stop= std::chrono::high_resolution_clock::now();
        const auto duration = stop-start;

        std::cout << "Player 1 won "<<player1Wins<<"/"<<repeats<<" games, average number of turns was "<<totalTurns/repeats<<" turns and average duration was "<<(duration_cast<std::chrono::nanoseconds>(duration)).count()/repeats<<" ns"<< std::endl;
    }
    return 0;
}