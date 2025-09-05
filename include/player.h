//
// Created by nikolaj on 9/2/25.
//

#ifndef ROYALGAMEOFURRELOADED_PLAYER_H
#define ROYALGAMEOFURRELOADED_PLAYER_H

class player {
    private:
    bool isBot=false;

    public:
    player(bool _isBot):isBot(_isBot){}

    ///Take a turn, and change the state of the game, doesn't change my internal state
    void takeTurn (int roll) const noexcept;
};

#endif //ROYALGAMEOFURRELOADED_PLAYER_H