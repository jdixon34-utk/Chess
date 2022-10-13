# Sprint 1
Jared Dixon, jdixon34-cs340, Chess

### What I planned to do
* Wrote KNIGHT_LOOKUP_TBL function [Issue #10](https://github.com/utk-cs340-fall22/Chess/issues/10)
* Wrote genBoardFromFEN function [Issue #12](https://github.com/utk-cs340-fall22/Chess/issues/12)
* Wrote printBitBoard function [Issue #13](https://github.com/utk-cs340-fall22/Chess/issues/13)
* Wrote printPosition function [Issue #14](https://github.com/utk-cs340-fall22/Chess/issues/14)
* Wrote move constructor and printMove function [Issue #22](https://github.com/utk-cs340-fall22/Chess/issues/22)
* Wrote pawnMoves functions including en passant [Issue #23](https://github.com/utk-cs340-fall22/Chess/issues/23)
* Wrote castling functions [Issue #24](https://github.com/utk-cs340-fall22/Chess/issues/24)


### What I did not do
* Implement pawn promotion
* Disallow castling while in check or through check

### What problems I encountered
* Everything went as expected

### Issues you worked on
* [Issue #10](https://github.com/utk-cs340-fall22/Chess/issues/10)
* [Issue #12](https://github.com/utk-cs340-fall22/Chess/issues/12)
* [Issue #13](https://github.com/utk-cs340-fall22/Chess/issues/13)
* [Issue #14](https://github.com/utk-cs340-fall22/Chess/issues/14)
* [Issue #22](https://github.com/utk-cs340-fall22/Chess/issues/22)
* [Issue #23](https://github.com/utk-cs340-fall22/Chess/issues/23)
* [Issue #24](https://github.com/utk-cs340-fall22/Chess/issues/24)

### Files you worked on
* All files in Chess/src

### What you accomplished
I did a lot of research into the best ways to represent the board and generate the possible moves. I then created the skeleton of the program with all of functions we would need to write. From then, Justin, Devin, and I worked together on writing all of the functions to read in a FEN string of a position and to create a list of all the possible moves. I wrote functions for a lookup table, parsing the FEN string input, printing for debugging, creating moves, and generating moves. We spent a lot of time planning for efficiency in this stage because it will be one of the main determinants of how good the engine is.
