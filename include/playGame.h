//
// Created by Nikolaj Christensen on 06/09/2025.
//

#ifndef ROYALGAMEOFURRELOADED_PLAYGAME_H
#define ROYALGAMEOFURRELOADED_PLAYGAME_H
#include <random>

#include "player.h"

///Play one royal game of ur, and return true if player 1 won
bool playGame(bool useGraphics, std::array<player,2> players, std::default_random_engine &randomEngine, int& turn);
#endif //ROYALGAMEOFURRELOADED_PLAYGAME_H