#include <iostream>
#include <string>
#include "game.h"
#include "board.h"
#include "move.h"
#include "search.h"
//#include <emscripten/bind.h>
//using namespace emscripten;
//When using webassembly comment namespace out
using namespace std;


std::string Game::playTurn(std::string FEN){
    int eval;
    Board position;
    positions.push_back(position);

    //set up position
    position.initialize_tables();
    position.genBoardFromFEN(FEN);

    //position.printPosition();
    //position.genMoves();
    //position.printMoves();

    //then do the search for the best move
    eval = search(&position, 0);

    printf("Evaluation: %d\n", eval);

    //return the updated FEN string
    return position.genFENFromBoard();
}

//EMSCRIPTEN_BINDINGS(my_class_example) {
// class_<Game>("chessGame")
//    .constructor<>()
//    .function("playTurn", &Game::playTurn)
//    ;
//}
