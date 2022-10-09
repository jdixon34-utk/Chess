#include <iostream>
#include <string>
#include <vector>
#include "game.h"
#include "board.h"
#include "move.h"
using namespace std;


string Game::playTurn(string FEN){
    Board position;

    positions.push_back(position);

    position.genBoardFromFEN(FEN);

    position.printPosition();

    //we have the position all set up
    //now we find all possible moves
    position.genMoves();
  
    //then do the search for the best move

    return "Eventual FEN String";
}
