//
// Created by nikolaj on 9/3/25.
//

#include "board.h"

std::array<std::string,18> board::getDisplay() const {

    return{
        " It is player "+std::to_string(positions[32]),
    " /===+===+===\\ ",
    std::string(" |")+(positions[4]?"{0}":" * ")+"|"+(positions[5]?"{0}":(positions[21]?"{1}":"   "))+"|"+(positions[20]?"{1}":" * ")+"| ",
    " +===+===+===+ ",
    std::string(" |")+(positions[3]?"{0}":"   ")+"|"+(positions[6]?"{0}":(positions[22]?"{1}":"   "))+"|"+(positions[19]?"{1}":"   ")+"| ",
    " +===+===+===+ ",
    std::string(" |")+(positions[2]?"{0}":"   ")+"|"+(positions[7]?"{0}":(positions[23]?"{1}":"   "))+"|"+(positions[18]?"{1}":"   ")+"| ",
    " +===+===+===+ ",
    std::string(" |")+(positions[1]?"{0}":"   ")+"|"+(positions[8]?"{0}":(positions[24]?"{1}":" * "))+"|"+(positions[17]?"{1}":"   ")+"| ",
    " \\===+===+===/ ",
    std::string("{0}x")+std::to_string(static_cast<int>(positions[0]))+"|"+(positions[9]?"{0}":(positions[25]?"{1}":"   "))+"|{1}x"+std::to_string(static_cast<int>(positions[16]))+"",
    "     +===+     ",
    std::string("{0}x")+std::to_string(static_cast<int>(positions[15]))+"|"+(positions[10]?"{0}":(positions[26]?"{1}":"   "))+"|{1}x"+std::to_string(static_cast<int>(positions[31]))+"",
    " /===+===+===\\ ",
    std::string(" |")+(positions[14]?"{0}":" * ")+"|"+(positions[11]?"{0}":(positions[27]?"{1}":"   "))+"|"+(positions[30]?"{1}":" * ")+"| ",
    " +===+===+===+ ",
    std::string(" |")+(positions[13]?"{0}":"   ")+"|"+(positions[12]?"{0}":(positions[28]?"{1}":"   "))+"|"+(positions[29]?"{1}":"   ")+"| ",
    " \\===+===+===/ "
        };
}
int board::getFutureGames(std::array<board,7>& futureGames, int roll) const {
    if (roll==0)
        return 0;
    //Literally defining this one thing speeds up the code a lot (144 ns to 84 ns)
    bool player0turn = positions[32]==0;

    int numberStates=0;
    //It is some player's turn, loop through all the places we can move roll from
    for (int from = 0; from < 16-roll; ++from) {
        int fromId=from+(player0turn?0:16);
        //We have something which can move from here
        if (positions[fromId]>0) {
            //We can move there if we ain't there, and the enemy isn't on 8
            int to = from+roll;
            int toId=to+(player0turn?0:16);
            if (to==15 || positions[toId]==0) {
                if (to!=8 || positions[(player0turn?16:0)+8]==0) {
                    //Ok, we CAN move there
                    futureGames[numberStates].positions=positions;
                    --futureGames[numberStates].positions[fromId];
                    ++futureGames[numberStates].positions[toId];

                    if (to!=4 && to != 8 && to !=14)
                        futureGames[numberStates].positions[32]=player0turn?0:1;
                    //Knock out enemy pieces if relevant
                    if (to > 4 && to<13) {
                        if (futureGames[numberStates].positions[(player0turn?16:0)+to]>0) {
                            futureGames[numberStates].positions[(player0turn?16:0)+to]=0;
                            futureGames[numberStates].positions[(player0turn?16:0)]++;
                        }
                    }
                    ++numberStates;
                }
            }
        }
    }
    return numberStates;
}
