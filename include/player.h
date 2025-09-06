//
// Created by nikolaj on 9/2/25.
//

#ifndef ROYALGAMEOFURRELOADED_PLAYER_H
#define ROYALGAMEOFURRELOADED_PLAYER_H
#include <array>

#include "board.h"

class player {
    private:
    bool isBot;
    int playerNumber;
    std::array<int16_t, 33*33> brain;

    public:

    [[nodiscard]] int getValue(const board& board) const;

    player(int _playerNumber ,bool _isBot);

    [[nodiscard]] bool isHuman() const { return !isBot; }

    ///Have the player choose which option they like best
    ///@param moves The list of possible moves (only the first numberMoves are considered)
    ///@param numberMoves how many moves there actually are
    [[nodiscard]] int ChooseMove (int numberMoves, const std::array<board,7>& moves, bool useGraphics) const noexcept;
};

#endif //ROYALGAMEOFURRELOADED_PLAYER_H