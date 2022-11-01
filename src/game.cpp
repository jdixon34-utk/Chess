#include <iostream>
#include <string>
#include "game.h"
#include "board.h"
#include "move.h"
//#include <emscripten/bind.h>
//using namespace emscripten;
//When using webassembly comment namespace out
using namespace std;


std::string Game::playTurn(std::string FEN){
    Board position;

    positions.push_back(position);

    position.genBoardFromFEN(FEN);

    //position.printPosition();

    //we have the position all set up
    //now we find all possible moves
    
    position.genMoves();
    position.printMoves();
 
    //then do the search for the best move

    //return the updated FEN string
    return position.genFENFromBoard();
}

//EMSCRIPTEN_BINDINGS(my_class_example) {
// class_<Game>("chessGame")
//    .constructor<>()
//    .function("playTurn", &Game::playTurn)
//    ;
//}
