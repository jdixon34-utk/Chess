#include "game.h"
#include "board.h"
#include "move.h"
using namespace std;

int main(int argc, char** argv){
    Game game;
    
    game.playTurn(argv[1]);
}
