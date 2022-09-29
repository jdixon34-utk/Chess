#include <string>
#include "game.h"
#include "board.h"
#include "move.h"

void INITIALIZE_KING_LOOKUP_TBL(){

}

void INITIALIZE_KNIGHT_LOOKUP_TBL(){
    unsigned long long tmpBitBoard;
    int rNew;
    int cNew;

    for(int c = 0; c < 8; c++){
        for(int r = 0; r < 8; r++){
            tmpBitBoard = 0;
            rNew = r + 1;
            cNew = c + 2;
            if (rNew < 8 && cNew < 8){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            rNew = r + 2;
            cNew = c + 1;
            if (rNew < 8 && cNew < 8){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            rNew = r + 2;
            cNew = c - 1;
            if (rNew < 8 && cNew >= 0){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            rNew = r + 1;
            cNew = c - 2;
            if (rNew < 8 && cNew >= 0){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            rNew = r - 1;
            cNew = c - 2;
            if (rNew >= 0 && cNew >= 0){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            rNew = r - 2;
            cNew = c - 1;
            if (rNew >= 0 && cNew >= 0){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            rNew = r - 2;
            cNew = c + 1;
            if (rNew >= 0 && cNew < 8){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            rNew = r - 1;
            cNew = c + 2;
            if (rNew >= 0 && cNew < 8){
                tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
            }
            KNIGHT_LOOKUP_TBL[(c * 8) + r] = tmpBitBoard;
        }
    }
}

void INITIALIZE_RAYS(){
	
}

string playTurn(string FEN){

}
