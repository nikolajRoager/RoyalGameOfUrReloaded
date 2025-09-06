//
// Created by nikolaj on 9/3/25.
//

#ifndef ROYALGAMEOFURRELOADED_BOARD_H
#define ROYALGAMEOFURRELOADED_BOARD_H

#include <array>
#include<cstdint>
#include <string>
#include <vector>

///The board of the game as a struct, I think it is easier if everyone has access to the data
///It is essentially just a 528 bit array with a few utillity methods attached to it
struct board {
///I am as distraught as you that I couldn't fit it in a nice round 512 bits, but any compression makes the game slower, not faster
    std::array<int16_t,33> positions = {};

    [[nodiscard]] inline int whoseTurn() const {return positions[33];}

    ///Has player 0 already won?
    [[nodiscard]] inline bool player0win() const {
        return positions[15]==7;
    }
    ///Has player 1 already won?
    [[nodiscard]] inline bool player1win() const {
        return positions[31]==7;
    }
    [[nodiscard]] inline bool gameOver() const {
        return player0win() || player1win();
    }

    //Game start
    board() {
        positions=
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
         7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    }

    ///Get strings we can print to the terminal to display the current state
    [[nodiscard]] std::array<std::string,18> getDisplay() const;

    [[nodiscard]] int getFutureGames(std::array<board,7>& futureGames, int roll) const;
};

#endif //ROYALGAMEOFURRELOADED_BOARD_H