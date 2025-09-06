//
// Created by nikolaj on 9/2/25.
//

#ifndef ROYALGAMEOFURRELOADED_PLAYER_H
#define ROYALGAMEOFURRELOADED_PLAYER_H
#include <array>

#include "board.h"

class player {
    private:
    bool isBot=false;
    int playerNumber;

    public:
    player(int _playerNumber ,bool _isBot):playerNumber(_playerNumber),isBot(_isBot){}

    ///Have the player choose which option they like best
    ///@param moves The list of possible moves (only the first numberMoves are considered)
    ///@param numberMoves how many moves there actually are
    int ChooseMove (int numberMoves, std::array<board,7>& moves) const noexcept;
};

#endif //ROYALGAMEOFURRELOADED_PLAYER_H