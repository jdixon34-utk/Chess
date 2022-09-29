#include <vector>
#include "board.h"
#include "move.h"
using namespace std;

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

void Board::genBoardFromFEN(char* FEN){

}

void Board::genMoves(){

}

void Board::genKingMoves(){

}

void Board::genQueenMoves(){

}

void Board::genRookMoves(){

}

void Board::genBishopMoves(){

}

void Board::genKnightMoves(){

}

void Board::genPawnLeftMoves(){

}

void Board::genPawnSinglePushMoves(){

}

void Board::genPawnDoublePushMoves(){

}

void Board::genPawnRightMoves(){

}

void Board::genPawnLeftEnPassantMoves(){

}

void Board::genPawnRightEnPassantMoves(){

}

void Board::genCastleKS(){

}

void Board::genCastleQS(){

}
