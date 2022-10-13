# Sprint 1
Justin McKnight, JMcknight75, Chess Website

### What you planned to do
*genKingMoves
*genQueenMoves
*genBishopMoves
*create INITIALIZE_RAYS
*create getMSBIndex


### What you did not do
*make a function for pawn promotion

### What problems you encountered
*Problems compiling and testing code
*Bugs with generating moves

### Issues you worked on
[#21](https://github.com/utk-cs340-fall22/Chess/issues/21) genQueenMoves
[#20](https://github.com/utk-cs340-fall22/Chess/issues/20) Create getMSBIndex
[#19](https://github.com/utk-cs340-fall22/Chess/issues/19) genBishopMoves
[#18](https://github.com/utk-cs340-fall22/Chess/issues/18) genKingMoves
[#7](https://github.com/utk-cs340-fall22/Chess/issues/7) Make INITIALIZE_RAYS


### Files you worked on
board.cpp
board.h
main.cpp

### What you accomplished
I created a function that shows the RAYS, or all squares a queen could move to on a blank board, from each square on the board. I then wrote genKingMoves, which generates where the king can go in a position, genBishopMoves, which generates where a bishop can go in a position, and genQueenMoves, which generates where a queen can move to in a position. In order to make these, I wrote genMSBIndex which finds the uppermost set bit in an unsigned long long.
