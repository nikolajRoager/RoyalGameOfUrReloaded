//
// Created by Nikolaj Christensen on 05/09/2025.
//

#include "player.h"

#include <iostream>

int player::ChooseMove(int numberMoves, std::array<board, 7> &moves) const noexcept {
    //Show the human all options, and ask them what they like best
    if (!isBot) {

        std::array<std::array<std::string,18> ,7> FutureDisplayStrings;

        for (int i = 0 ; i < numberMoves; i++) {
            FutureDisplayStrings[i] = moves[i].getDisplay();
            std::cout <<"   MOVE "<<i<<"       |";
        }

        std::cout << '\n';
        for (int j = 0 ; j < 18 ; j++) {
            for (int i = 0 ; i < numberMoves; i++) {
                std::cout << FutureDisplayStrings[i][j] << " | ";
            }
            std::cout << '\n';
        }
        std::cout <<"Choose which move you want to make:"<< std::endl;

        std::string line;
        //Keep getting inputs until the idiot enters a number
        while (true) {
            std::getline(std::cin,line);

            //-1 means quit game
            if (line.compare("q")==0 || line.compare("Q")==0) {
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

    return 0;
}
