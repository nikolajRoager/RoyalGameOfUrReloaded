//
// Created by Nikolaj Christensen on 05/09/2025.
//

#include "player.h"

#include <iostream>


player::player(int _playerNumber ,bool _isBot):playerNumber(_playerNumber),isBot(_isBot),brain({
          //The diagonal is the inherent value of the position, they generally ascend, except when it comes to leaving safety
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  6,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  8,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0, 10,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0, 14,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0, 12,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 14,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 16,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 18,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 24,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 30,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,

          //Having someone else 1,3 and especially 2 behind me is bad (2 is most likely roll by far), being 2 behind the opponent is great for the same reason
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,    0, -1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,    0,  0, -3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0, -3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0, -4,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  2,  0,  0, -1, -2,  3,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0, -5,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  2,  0,  0, -1,  4,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0, -6,  0,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  2,  0,  0,  0, -2,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0, -7,  0,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0, -1, -2,  0,  0, -1, -2,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,-12,  0,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  2,  0,  0, -1, -2,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,-11,  0,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0, -1, -2,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-12,  0,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0, -1,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-14,  0,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-17,  0,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-24,  0,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-24,  0,   0,
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,-30,   0,

        //The final row is the value of player 1 having turn combined with all positions
          0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, -20,//Player 1 having turn is bad for player 0
}){}


int player::getValue(const board& board) const{
    int32_t sum=0;

    for (int i = 0; i < 33; ++i)
        if (board.positions[i]) {
            for (int j = i; j < 33; ++j) {
                if (board.positions[j]) {
                    int matrixElement = brain[i+j*33];
                    if (matrixElement)
                        sum += brain[i+j*33]*board.positions[j]*board.positions[i];
                }
            }
        }
    return sum;
}


int player::ChooseMove(int numberMoves, const std::array<board, 7> &moves, bool useGraphics) const noexcept {

    if (isBot) {
        //Get the value of each move, and go with the best one

        //There is always a move 0, it may be nothing, but it is there
        int best_value = playerNumber == 0? getValue(moves[0]) : -getValue(moves[0]);
        if (useGraphics)
            std::cout<<"Bot rates move 0 : "<<best_value<<std::endl;
        int best_move = 0;
        for (int i = 1 ; i < numberMoves ; ++i) {
            int newValue = playerNumber==0? getValue(moves[i]) : -getValue(moves[i]);


            if ( (newValue > best_value)) {
                best_value = newValue;
                best_move = i;
            }
            if (useGraphics)
                std::cout<<"Bot rates move "<<i<<" : "<<newValue<<std::endl;
        }

        if (useGraphics) {
            std::cout<<"Bot chooses move "<<best_move<<". Press enter to continue"<<std::endl;

            std::string input;
            std::getline(std::cin,input);

        }
        //Choose the highest/lowest value if player 0/1
        return best_move;
    }
    else {

    //I assume the human has already seen the options, useGraphics should be on when humans are involved
        std::cout <<"Choose which move you want to make:"<< std::endl;

        std::string line;
        //Keep getting inputs until the idiot enters a number
        while (true) {
            std::getline(std::cin,line);

            //-1 means quit game
            if (line=="q" || line=="Q") {
                return -1;
            }
            try {
                int move = std::stoi(line);
                if (move >= numberMoves || move < 0) {
                    std::cout <<"Move is out of range"<<std::endl;
                }
                else
                    return move;
            }catch (...) {
                std::cout<<"Not a number, try again"<<std::endl;
                //Whatever try again
            }
        }
    }
}