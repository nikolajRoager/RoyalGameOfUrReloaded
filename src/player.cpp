//
// Created by Nikolaj Christensen on 05/09/2025.
//

#include "player.h"

#include <fstream>
#include <iostream>
#include <immintrin.h>

player::player(int _playerNumber ,bool _isBot):isBot(_isBot),playerNumber(_playerNumber),brain({
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

player::player(int _playerNumber ,bool _isBot, std::ifstream& brainFile):isBot(_isBot),playerNumber(_playerNumber), brain({}) {

    brainFile.seekg(0,std::ios::beg);
    for (int i = 0; i < 33; ++i) {
        for (int j = 0; j < 33; ++j) {
            brainFile>>brain[i*33 + j];
        }
    }
}

void player::printBrain() const {
    for (int i = 0; i < 33; ++i) {
        for (int j = 0; j <= i; ++j) {
            std::cout << brain[i*33 + j] << ' ' ;
        }
        std::cout<<'\n';
    }
    std::cout<<std::flush;
}


int player::getValue(const board& board) const{
    //We will add parts of the sum as 32 bit snippets to this register, then sum it up when they are all there
    __m256i sum = _mm256_setzero_si256();//Start empty


    //For the first 16 rows, we only look at the first 16 columns
    for (int i = 0; i < 16; ++i) {
        if (!board.positions[i])
            continue;
        __m256i vec = _mm256_setzero_si256();

        //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
        {
            //Pick out a section of the vector and this row
            __m256i v_vec = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&board.positions[0]));
            __m256i m_vec = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&brain[i * 33]));

            //Multiply them together
            __m256i prod = _mm256_madd_epi16(v_vec, m_vec);

            //Add it together,
            //this only works on 64 bit machines
            vec = _mm256_add_epi32(vec, prod);
        }

        //Multiply with the corresponding element in V (from the row-vector on the left)
        __m256i v_elem = _mm256_set1_epi32(board.positions[i]);
        //The numbers are small enough that only the low bits are needed
        vec = _mm256_mullo_epi32(vec, v_elem);

        //Add to the sum
        //this only works on 64 bit machines
        sum = _mm256_add_epi32(sum, vec);
    }

    //For the final 17 rows, we look at 32 columns in batches of 16
    for (int i = 16; i < 33; ++i) {
        if (!board.positions[i])
            continue;
        __m256i vec = _mm256_setzero_si256();

        //Compute the dot-product in steps of 16 indices, as that is all we can fit in 256 bytes
        {
            //Pick out a section of the vector and this row
            __m256i v_vec = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&board.positions[0]));
            __m256i m_vec = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&brain[i * 33 + 0]));

            //Multiply them together
            __m256i prod = _mm256_madd_epi16(v_vec, m_vec);

            //Add it together,
            //this only works on 64 bit machines
            vec = _mm256_add_epi32(vec, prod);
        }
        {
            //Pick out a section of the vector and this row
            __m256i v_vec = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&board.positions[16]));
            __m256i m_vec = _mm256_loadu_si256(reinterpret_cast<const __m256i *>(&brain[i * 33 + 16]));

            //Multiply them together
            __m256i prod = _mm256_madd_epi16(v_vec, m_vec);

            //Add it together,
            //this only works on 64 bit machines
            vec = _mm256_add_epi32(vec, prod);
        }

        //Multiply with the corresponding element in V (from the row-vector on the left)
        __m256i v_elem = _mm256_set1_epi32(i==33?(board.positions[i]?1:-1) :  board.positions[i]);
        //The numbers are small enough that only the low bits are needed
        vec = _mm256_mullo_epi32(vec, v_elem);

        //Add to the sum
        sum = _mm256_add_epi32(sum, vec);
    }





    //Extract and sum up the result, I tried using a few hadds, but it proved slower
    int32_t res[8];
    _mm256_storeu_si256((__m256i*)res, sum);
    return res[0] + res[1] + res[2] + res[3] + res[4] + res[5] + res[6] + res[7] + (board.positions[32]?brain[33*33-1]:(-brain[33*33-1]))/*Handle the final element as its own thing, it didn't fit in the registers*/;

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