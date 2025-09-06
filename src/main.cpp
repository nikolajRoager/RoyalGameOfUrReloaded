#include <iostream>
#include <random>

#include "board.h"
#include "player.h"


int main() {

    //Intentionally using default seed for now
    std::default_random_engine generator(0);
    std::uniform_int_distribution<int> dice(0, 1);


    std::cout << "Hello, World!, let us play a game" << std::endl;


    //The people who will play this game
    player players[] = {player(0,false),player(1,false)};

    //The current state of the game
    board game;

    //What the game could look like in the future
    //7 is the max number of moves each turn, in practice there will most often be 3
    //Allocating this as a workspace ahead of time speeds up calculations
    //Another variable will tell us how many of the 7 future games are actually for this turn
    //We could use an inplace_vector, but that is a c++26 feature
    std::array<board,7> futureGames;

    //Should the game be printed? if not we will just hear who won (no-graphics only makes sense for bot-vs-bot)
    bool useGraphics=true;

    int turn=0;

    while (!game.gameOver()) {

        int roll = dice(generator)+dice(generator)+dice(generator)+dice(generator);

        //Display the game if doing so is called for
        if (useGraphics) {
            auto displayStrings = game.getDisplay();

            std::cout<<"State of the game at Turn "<<turn<<std::endl;
            for (const auto& displayString : displayStrings) {
                std::cout << displayString << std::endl;
            }
            std::cout<<"ROLL: "<<roll<<std::endl;
        }

        //Update future games, and get number of possible moves
        int legalMoves = game.getFutureGames(futureGames,roll);

        //Ask the player whose turn it is to pick their preferred move
        int nextMove = players[game.whoseTurn()].ChooseMove(legalMoves,futureGames);

        //This functions as a quit command, used by human players
        if (nextMove==-1)
            break;

        game = futureGames[nextMove];
        ++turn;
    }
    return 0;
}