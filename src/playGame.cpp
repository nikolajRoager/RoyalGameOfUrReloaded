//
// Created by Nikolaj Christensen on 06/09/2025.
//

#include "playGame.h"

#include <chrono>
#include <iostream>

bool playGame(bool useGraphics,  std::array<player,2> players, std::default_random_engine &randomEngine, int& turn) {

    std::uniform_int_distribution<int> dice(0, 1);


    useGraphics = useGraphics || players[0].isHuman() || players[1].isHuman();

    //The current state of the game
    board game;

    //What the game could look like in the future
    //7 is the max number of moves each turn, in practice there will most often be 3
    //Allocating this as a workspace ahead of time speeds up calculations
    //Another variable will tell us how many of the 7 future games are actually for this turn
    //We could use an inplace_vector, but that is a c++26 feature
    std::array<board,7> futureGames;

    //List of the places we move to in every future game, for display
    //such that if we move to 4 as our 2nd possible move, moveTo[4]=2
    std::array<int,32> moveTo={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    turn=0;

    int repeats = 100000;

    while (!game.gameOver()) {

        int roll = dice(randomEngine)+dice(randomEngine)+dice(randomEngine)+dice(randomEngine);

        if (useGraphics)
            moveTo={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

        //Update future games, and get number of possible moves
        int legalMoves = game.getFutureGames(futureGames,roll,moveTo);

        //Display the game if doing so is called for
        if (useGraphics) {

            auto displayStrings = game.getDisplay(moveTo);

            std::cout<<"\n\n\n\nState of the game at Turn "<<turn<<std::endl;
            for (const auto& displayString : displayStrings) {
                std::cout << displayString << std::endl;
            }
            std::cout<<"ROLL: "<<roll<<std::endl;
        }


        //Ask the player whose turn it is to pick their preferred move
        int nextMove = players[game.whoseTurn()].ChooseMove(legalMoves,futureGames,useGraphics);

        //This functions as a quit command, used by human players
        if (nextMove==-1)
            break;

        game = futureGames[nextMove];
        ++turn;
    }

    return game.player1win();
}

