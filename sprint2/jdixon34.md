# Sprint 2
Jared Dixon, jdixon34-cs340, Chess

### What I planned to do
* Add Pawn Promotion to genPawnMoves function [Issue #25](https://github.com/utk-cs340-fall22/Chess/issues/25)
* Write makeMove function [Issue #32](https://github.com/utk-cs340-fall22/Chess/issues/32)
* Write undoMove function [Issue #33](https://github.com/utk-cs340-fall22/Chess/issues/33)
* Write makeNormalMove function [Issue #41](https://github.com/utk-cs340-fall22/Chess/issues/41)
* Write undoNormalMove function [Issue #42](https://github.com/utk-cs340-fall22/Chess/issues/42)
* Write makeCastleMove and printMove function [Issue #43](https://github.com/utk-cs340-fall22/Chess/issues/43)
* Write undoCastleMove functions including en passant [Issue #44](https://github.com/utk-cs340-fall22/Chess/issues/44)

### What I did not do
* We were thinking of starting on a basic version of the move search and evaluation but ran out of time

### What problems I encountered
* I had to go back and change the way the bitboards were declared to access them without having to use conditionals

### Issues you worked on
* [Issue #25](https://github.com/utk-cs340-fall22/Chess/issues/25)
* [Issue #32](https://github.com/utk-cs340-fall22/Chess/issues/32)
* [Issue #33](https://github.com/utk-cs340-fall22/Chess/issues/33)
* [Issue #41](https://github.com/utk-cs340-fall22/Chess/issues/41)
* [Issue #42](https://github.com/utk-cs340-fall22/Chess/issues/42)
* [Issue #43](https://github.com/utk-cs340-fall22/Chess/issues/43)
* [Issue #44](https://github.com/utk-cs340-fall22/Chess/issues/44)

### Files you worked on
* Chess/src/board.h
* Chess/src/board.cpp
* Some minor tweaks in move.h and move.cpp

### What you accomplished
The goal of this sprint was to get everything set up to begin the search function for the best move. The work that I contributed dealt with the process
of making a move and then undoing it. To do this, all of the bitboards must be updated accordingly and captures must be taken into account. I wrote the functions makeMove and undoMove which determine which function to call next based on the type of move that is being made/undone (normal, enpassant, castling, or promotion). I then wrote the functions make/undoNormalMoves and make/undoCastleMoves. We weren't able to start on the search function this sprint, but we are still on track to have a respectable chess engine by the end of sprint 4.
