//
// Created by nikolaj on 9/3/25.
//

#include "board.h"

#include <iostream>

std::array<std::string,18> board::getDisplay(std::array<int,32>& moveTo) const {


    if (moveTo[21]!=-1)
        moveTo[5]=moveTo[21];
    if (moveTo[22]!=-1)
        moveTo[6]=moveTo[22];
    if (moveTo[23]!=-1)
        moveTo[7]=moveTo[23];
    if (moveTo[24]!=-1)
        moveTo[8]=moveTo[24];
    if (moveTo[25]!=-1)
        moveTo[9]=moveTo[25];
    if (moveTo[26]!=-1)
        moveTo[10]=moveTo[26];
    if (moveTo[27]!=-1)
        moveTo[11]=moveTo[27];
    if (moveTo[28]!=-1)
        moveTo[12]=moveTo[28];

    return{
        " It is player "+std::to_string(positions[32]),
    " /===+===+===\\ ",
    std::string(" |")+(positions[4]?"{0}":" * ")+"|"+(positions[5]?"{0}":(positions[21]?"{1}":"   "))+"|"+(positions[20]?"{1}":" * ")+"| ",
    " +"+(moveTo[4]==-1?"=":std::to_string(moveTo[4]))+"==+"+(moveTo[5]==-1?"=":std::to_string(moveTo[5]))+"==+"+(moveTo[20]==-1?"=":std::to_string(moveTo[20]))+"==+ ",
    std::string(" |")+(positions[3]?"{0}":"   ")+"|"+(positions[6]?"{0}":(positions[22]?"{1}":"   "))+"|"+(positions[19]?"{1}":"   ")+"| ",
    " +"+(moveTo[3]==-1?"=":std::to_string(moveTo[3]))+"==+"+(moveTo[6]==-1?"=":std::to_string(moveTo[6]))+"==+"+(moveTo[19]==-1?"=":std::to_string(moveTo[19]))+"==+ ",
    std::string(" |")+(positions[2]?"{0}":"   ")+"|"+(positions[7]?"{0}":(positions[23]?"{1}":"   "))+"|"+(positions[18]?"{1}":"   ")+"| ",
    " +"+(moveTo[2]==-1?"=":std::to_string(moveTo[2]))+"==+"+(moveTo[7]==-1?"=":std::to_string(moveTo[7]))+"==+"+(moveTo[18]==-1?"=":std::to_string(moveTo[18]))+"==+ ",
    std::string(" |")+(positions[1]?"{0}":"   ")+"|"+(positions[8]?"{0}":(positions[24]?"{1}":" * "))+"|"+(positions[17]?"{1}":"   ")+"| ",
    " \\"+(moveTo[1]==-1?"=":std::to_string(moveTo[1]))+"==+"+(moveTo[8]==-1?"=":std::to_string(moveTo[8]))+"==+"+(moveTo[17]==-1?"=":std::to_string(moveTo[17]))+"==/ ",
    std::string("{0}x")+std::to_string(static_cast<int>(positions[0]))+"|"+(positions[9]?"{0}":(positions[25]?"{1}":"   "))+"|{1}x"+std::to_string(static_cast<int>(positions[16]))+"",
    "     +"+(moveTo[9]==-1?"=":std::to_string(moveTo[9]))+"==+     ",
    std::string("{0}x")+std::to_string(static_cast<int>(positions[15]))+"|"+(positions[10]?"{0}":(positions[26]?"{1}":"   "))+"|{1}x"+std::to_string(static_cast<int>(positions[31]))+"",
    " /"+(moveTo[15]==-1?"=":std::to_string(moveTo[15]))+"==+"+(moveTo[10]==-1?"=":std::to_string(moveTo[10]))+"==+"+(moveTo[31]==-1?"=":std::to_string(moveTo[31]))+"==\\ ",
    std::string(" |")+(positions[14]?"{0}":" * ")+"|"+(positions[11]?"{0}":(positions[27]?"{1}":"   "))+"|"+(positions[30]?"{1}":" * ")+"| ",
    " +"+(moveTo[14]==-1?"=":std::to_string(moveTo[14]))+"==+"+(moveTo[11]==-1?"=":std::to_string(moveTo[11]))+"==+"+(moveTo[30]==-1?"=":std::to_string(moveTo[30]))+"==+ ",
    std::string(" |")+(positions[13]?"{0}":"   ")+"|"+(positions[12]?"{0}":(positions[28]?"{1}":"   "))+"|"+(positions[29]?"{1}":"   ")+"| ",
    " \\"+(moveTo[13]==-1?"=":std::to_string(moveTo[13]))+"==+"+(moveTo[12]==-1?"=":std::to_string(moveTo[12]))+"==+"+(moveTo[29]==-1?"=":std::to_string(moveTo[29]))+"==/ ",
        };
}
int board::getFutureGames(std::array<board,7>& futureGames, int roll,std::array<int,32>& moveTo) const {
    int numberStates=0;
    bool player0turn = positions[32]==0;
    if (roll!=0) {
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
                        moveTo[toId]=numberStates;

                        if (to!=4 && to != 8 && to !=14) {
                            futureGames[numberStates].positions[32]=player0turn?1:0;
                        }
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
    }
    //If there are zero legal moves, insert the current game with turn flipped as only legal move
    if (numberStates==0) {
        futureGames[0].positions=positions;
        futureGames[0].positions[32]=player0turn?1:0;
        numberStates=1;
    }
    return numberStates;
}