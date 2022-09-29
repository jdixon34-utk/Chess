#include <iostream>
#include <string>
#include "game.h"
#include "board.h"
#include "move.h"

void Game::INITIALIZE_KING_LOOKUP_TBL(){
    for(unsigned long long i=0; i<64; i++){
        //Kings move to the right
        if((i+1) % 8){
            KING_LOOKUP_TBL[i] |= 1ULL << (i+1);
            // Up to the Right
            if(i+1 < 57) KING_LOOKUP_TBL[i] |= 1ULL << (i+9);
            //Down to the Right
            if(i+1 > 7) KING_LOOKUP_TBL[i] |= 1ULL << (i-7);
        }
        
        //Kings move to the left
        if((i-1) % 8 != 7){
            KING_LOOKUP_TBL[i] |= 1ULL << (i-1);
            // Up Left
            if(i-1 < 57) KING_LOOKUP_TBL[i] |= 1ULL << (i+7);
            // Up Down
            if(i-1 > 7) KING_LOOKUP_TBL[i] |= 1ULL << (i-9);
        }

        //King moves up
        if(i < 57) KING_LOOKUP_TBL[i] |= 1ULL << (i+8);

        //King moves down
        if(i > 7) KING_LOOKUP_TBL[i] |= 1ULL << (i-8);
    }
}

void Game::INITIALIZE_KNIGHT_LOOKUP_TBL(){
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

void Game::INITIALIZE_RAYS(){
	int pos;
	for (int i = 0; i < 64; i++) {
		//north
		pos = i;
		RAYS[i][0] = 0;
		while(pos+8 < 63){
			pos += 8;
			RAYS[i][0] |= (1ULL << pos);
		}
		pos = i;
		//ne
		//e
		pos = i;
		RAYS[i][2] = 0;
		while((pos+1)%8 != 0){
			pos += 1;
			RAYS[i][2] |= (1ULL << pos);
		}
		//se
		//s
		//sw
		//w
		//nw
	}
}

std::string Game::playTurn(std::string FEN){

}
