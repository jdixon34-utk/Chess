3#include "game.h"
#include "board.h"
#include "move.h"
using namespace std;

//global constants and lookup tables to be used to calculate possible moves
unsigned long long RANK_1 = 0x00000000000000FF;
unsigned long long RANK_2 = 0x000000000000FF00;
unsigned long long RANK_3 = 0x0000000000FF0000;
unsigned long long RANK_4 = 0x00000000FF000000;
unsigned long long RANK_5 = 0x000000FF00000000;
unsigned long long RANK_6 = 0x0000FF0000000000;
unsigned long long RANK_7 = 0x00FF000000000000;
unsigned long long RANK_8 = 0xFF00000000000000;
unsigned long long FILE_A = 0x0101010101010101;
unsigned long long FILE_B = 0x0202020202020202;
unsigned long long FILE_C = 0x0404040404040404;
unsigned long long FILE_D = 0x0808080808080808;
unsigned long long FILE_E = 0x1010101010101010;
unsigned long long FILE_F = 0x2020202020202020;
unsigned long long FILE_G = 0x4040404040404040;
unsigned long long FILE_H = 0x8080808080808080;
unsigned long long KING_LOOKUP_TBL[64] = {0};
unsigned long long KNIGHT_LOOKUP_TBL[64] = {0};
unsigned long long RAYS[64][8]; //all rays from one of 64 squares in one of 8 directions(N, NE, E, SE, etc.)
                                //used for sliding pieces only
int main(int argc, char** argv){
    Game game;

    game.playTurn(argv[1]);
}
