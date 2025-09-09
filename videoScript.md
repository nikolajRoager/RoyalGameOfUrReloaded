Video script, AI Learns the worlds oldest game
==

Scene 0, intoduction
--
*Live scene, showing of the game board. Camera focused on face mostly*

This is The Royal Game of Ur, it is one of the oldest games in the world.

Or at the very least one of the oldest games where we know the rules.

4600-year-old Game boards and die, just like these (show board), have been found in the bronze-age royal cemetery in the city of Ur -- you know, the place where some guy named Abraham came from.

Other game boards like this have also been found all over modern day Iraq, and archeologists even found a clay tablet with the rules.

This means we can play it today, just like our bronze-age ancestors used to, and in my opinion it is really fun, hence why I made this copy of it.


But unfortunately for me, I don't have any friends... So I don't have anybody to play against.

But thankfully, some American lizard tech-billionaire said that AI is a good replacement for friends, and that is why I have decided to make an AI I can play against.

And in this video, I will show you how I did that.

But first, I think it is a good idea to go through the rules in this game


scene 1, royal rules of ur
--
*Live scene, showing the game board, camera is on the board*

Ok, the rules probably varied a lot from place to place, and over the roughly 2000 years when this game was popular.

The rules I am going with are the original translation by Irving Finkel.


So this right here is the board, we have a bunch of positions, some have a star of sorts, most doesn't.

Each player has seven pieces, and the aim of the game is to move all your pieces from start to finish,
the one player, me,  starts here, and move like this, the other, you,  start here, and move this way.

You move by rolling these four die...

yes this is a dice, it is a tetrahedron, and two of it corners have a dot, the other two doesn't, when you role one dice, either the dot is going to point up, or not.

When you roll four dice, you have to count how many dots are pointing up, and that is the number of moves you have to make.


In this case (roll) we rolled 3, and all my pieces are not started yet, so the only choice is to move ... 1, 2, 3 here.

Now it is player 1s turn ... but if we landed on one of these stars, any of them, we would get an extra free turn.

Now if we play a few turns, eventually we are going to move in here... this is the combat zone, if I stand here, and you roll a two, you end up on top of me, and I get knocked home.

Well that is what happens unless I am standing on this star, in that case I am invulnerable, and you can't land on me, you have to make another move.

The same happens if you are about to land on one of your own pieces, you can't make that move and have to find another move.
If there are no possible moves you just loose your turn, and if there is only one possible move, then you HAVE to do it

Oh, and one more thing, my goal is to get exactly here, and your goal is to get exactly here, so you need to get exactly one more roll than to here,
if you roll a three while standing here, that is no good


Well there you go, that is the rules for the Royal game of Ur, they are quite simple rules, but it is still a hectic fun game

So with that out of the way, before we make the AI: Let's code the game.

Scene 2, the board
--
Presentation



    struct board {
        std::array<int16_t,33> positions =
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        ...
    }


So, the first step is how do we represent the state of the game on the computer, and after a lot of testing, this is the way I think is best

The board contains 33 16 bit numbers, the first 16 numbers is the number of pieces the first player has at each location,

    Photo of game with numbers 

where 0 is there start, this is 1, 2, 3, 4, 5 ... 13, 14 and 15 is finish.


    Photo of game with numbers 

The next 16 numbers is the number of pieces the second player has at each location, so for instance the 16th number is the number of not-started-yet pieces, and 21 is their number of pieces here


    Photo of game with numbers 

It might seem a little weird that this is both location 5 and 21, but that is just the way I represent this.


    struct board {
        std::array<int16_t,33> positions =
        {7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        ...
    }

The final number is whose turn it is, it is 0 if it is the first player, 1 if it is the second player.

You might argue that this is inefficient, after all in most places there can only be one or zero pieces, that could be stored as a single bit, so why on earth am I explicitly using 16 bit numbers?

Well, I tried a lot of different things, and the 16 bit version is actually the fastest.

The reason for this, is basically that I am using a kind of dark-magic low-level C++ extension, called AVX2, which allows me to use a single processor instruction on multiple data at the same time, and
from my testing AVX2 works best on 16 bit or higher integers, so that is why I am using 16 bit.

I am going to go into more details with AVX2 later

Scene 3, `getFutureGames()`
--------------
Now, with a representation of the game, we need to find all possible moves

     State vector and picture of game

Say, if the state of the game is this, and the first player just rolled 2, what moves can they make? and what will the game look like afterwards?

I call the function which calculates this `getFutureGames` and here it is:

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

Yeah, it is ugly, but it is actually pretty simple. The first thing to note is that this function returns an integer, the number of possible moves,

    Highlight future moves

And it also writes the board after each move to a pre-allocated std::array for all future moves, this is slightly more efficient than allocating a new list. 

As for the rest of the function.

Scene 4, `getFutureGames` live
--
Live section focusing on the game board

The function basically loops through all the locations the first or second player could be in, and for each location, we check if we have a piece there.

Then we check if we can make the move, or if we are blocked, and check if we should remove an opponent piece.

scene 5, playing the game
--
Live screencast, focus on `playGame.cpp`, game should already be running with player vs player game

To make a functioning game, all we need is a random generator to roll the dice, and a way of displaying the game,
then we can get possible future states of the game, and then we can ask the player what move they like best and make that the current state.

This is what I have here, this is a very simplistic console implementation of the Royal Game of Ur,

Now it is player 0 turn, the first player, I rolled ..., so I can move here
as you can see the program highlights that I can move here, there is a zero because that is move number 0, the only move
lets write 0.

Now it is player 1 turn, the second player, you rolled ..., so we can move here, move 0

Now it is my turn again, I can make two moves, move 0 here, or move 1 here, ... there we go, your turn.

And... well, this is a perfectly functioning game now. As I said, it is a really simple game to make, but I want an AI to play against

scene 6, AI decisions
--
*Live scene, focusing on the game board with 3 pieces on the board (player 1 is two behind player 0), with value matrix as a prop*

One way for the AI to decide what move to make, is to assign a numerical value to each possible future, and pick the one with the highest value.

So we need some kind of getValue function, which takes a board as input, and returns a number.

One way to do that is to just have a value for each position on the board, say 4 points for standing here, 8 for standing here, and 20 for each finished piece

That certainly works, but I want my AI to take into consideration all the other pieces on the board, and the way I will do this is using a value Matrix like this.

This is a 33 by 33 matrix, a table of numbers, which tells me how many points each pair of pieces is worth.

For example, I am here on position 7, and you are at position 21, remember that is how I represent the state of the board it is 21 if you are there, 5 if I am there
Then the value of this is row 21, column 7, which is -2, because it is bad for me that you are here, two is after all the most likely roll, so you are likely to take me

When it comes to these two pieces, we check position 3 and position 21, that is +2, because I might take you, so we add that to the value

Oh by the way, the way I have set it up in the code, you always look in the lower left of, so we check row 21 column 7, not column 21 row 7, so all these numbers are all 0

I also check each piece against itself, so in this case we need to check 21 by 21, 3 by 3 and 7 by 7. and the final row, row 33 is for whose turn it is,

You might recognize what we are doing here as a vector matrix vector multiplication, and this is basically reduced the AI decisionmaking process to.


scene 7, optimizations and SIMD
--
*Presentation*

    int32_t getValue(const board& board) {
        int32_t sum=0;
        for (int i = 0; i < 33; ++i)
            for (int j = i; j < 33; ++j) {
                sum += brain[i+j*33]*board.positions[j]*board.positions[i];
            }
        return sum;
    }

It is fairly easy to make a simple getValue function, like this, and this gives a functional AI opponent... well at least if we have a good brain matrix, 

The problem is that to get a good brain matrix, we need to train the bot by having bots with different brains play against each other millions of times
So it is really important that the game can run quickly, and this getValue function is very slow

On average, this takes something like 2 microseconds to run, and that makes it the slowest function in the game by an order of magnitude.
And we need to run it for every possible move every turn.

So how can we do better? Well, there are a lot of ways to improve this, for example you can check if the vector or matrix elements are zero
and skip all multiplications which are obviously going to give 0
But to really improve this, we need to use dark magic, also known as low-level C.

    Show list of numbers

Let us take a step back and ask ourself, what happens if I add every number in this list, to the numbers in that list?

    Show numbers getting added

Well, our C or C++ code gets compiled to an assembly instruction which adds the first numbers, then the next numbers, then the next and so on, same deal if we multiplied or compared
    
    show lists getting added

But we don't need the calculations to happen one after another, it would really be better if there was a single instruction: to just add this entire list to that entire list.
And it turns out there is, and that is called SIMD: Single instruction multiple data
On modern CPUs, there are a few magic registers, which can hold multiple numbers, and where a single instruction can effect the entire register

On my CPU, I have the AVX2 extension, that means I have 16 YMM registers, which can hold 256 bits each, so I can add, multiply or compare 16 16 bit numbers at the same time
I can explicitly tell the C or C++ compiler to use the YMM registers, and AVX2 instructions using the intrinsic assembly directly in the code

    Show code

Rewriting the getValue function to use AVX2 is not pretty, this is what it looks like now. But it is much much faster, now it takes 170 nanoseconds on average, which is much better,
and now a full game, with two bots playing against each other, takes roughly 100 microseconds, which is fast enough 