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
    position.positionsEvaluated = 0;
    position.initialize_tables();
    position.genBoardFromFEN(FEN);

    //then do the search for the best move
    eval = search(&position, 0);

    printf("Evaluation: %f\n", double(eval) / 100);
    printf("Positions Evaluated: %d\n", position.positionsEvaluated);
    printf("Best Move: ");
    (position.bestMove).printMove();

    //make the best move
    position.makeMove(position.bestMove);
    position.color = !position.color;

    printf("Returning FEN String: %s\n", (position.genFENFromBoard()).c_str());

    //return the updated FEN string
    return position.genFENFromBoard();
}

//EMSCRIPTEN_BINDINGS(my_class_example) {
// class_<Game>("chessGame")
//    .constructor<>()
//    .function("playTurn", &Game::playTurn)
//    ;
//}
