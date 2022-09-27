#include "board.h"
#include "move.h"
using namespace std;

void playTurn(char* FEN){
    Board board;

    board.genBoardFromFEN(FEN);
    board.genMoves();
    //some other function to return the vector of moves
}

int main(int argc, char** argv){
    playTurn(argv[1]);
}