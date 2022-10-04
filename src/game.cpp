#include <iostream>
#include <string>
#include "game.h"
#include "board.h"
#include "move.h"
using namespace std;

<<<<<<< HEAD
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
            // Left-Up
            if(i-1 < 57) KING_LOOKUP_TBL[i] |= 1ULL << (i+7);
            // Left-Down
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
		//ne
		pos = i;
    RAYS[i][1] = 0;
    while((pos+9)%8 != 0 && pos+9 < 63){
      pos += 9;
      RAYS[i][1] |= (1ULL << pos);
    }
		//e
		pos = i;
		RAYS[i][2] = 0;
		while((pos+1)%8 != 0){
			pos += 1;
			RAYS[i][2] |= (1ULL << pos);
		}
		//se
    pos = i;
    RAYS[i][3] = 0;
    while(pos-7 >= 0 && (pos-7)%8 != 0){
      pos -= 7;
      RAYS[i][3] |= (1ULL << pos);
    }
		//s
		pos = i;
		RAYS[i][4] = 0;
		while((pos-8) >= 0){
			pos -= 8;
			RAYS[i][4] |= (1ULL << pos);
		}
		//sw
    pos = i;
    while(pos-9 >= 0 && (pos)%8 != 0){
      pos -= 9;
      RAYS[i][5] |= (1ULL << pos);
    }
		//w
    pos = i;
		while(pos%8 != 0 && (pos-1)%8 != 0){
			pos -= 1;
			RAYS[i][6] |= (1ULL << pos);
		}
		//nw
    pos = i;
    RAYS[i][1] = 0;
    while((pos)%8 != 0 && pos+9 < 63){
      pos += 7;
      RAYS[i][7] |= (1ULL << pos);
    }
	}
}
=======
>>>>>>> 396436608076386d481482c3d9fcfc5f6c8199de

string Game::playTurn(string FEN){

}
