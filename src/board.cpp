#include <vector>
#include "board.h"
#include "move.h"
using namespace std;

void INITIALIZE_KING_LOOKUP_TBL(){

}

void INITIALIZE_KNIGHT_LOOKUP_TBL(){

}

void INITIALIZE_RAYS(){
	int pos;
	for (size_t i = 0; i < RAYS.size(); i++) {
		//north
		pos = i;
		while(pos+8 < 63){
			pos += 8;
			RAYS[i][0] |= 1UL << (pos);
		}
		pos = i;
		//ne
		//e
		pos = i;
		while((pos+1)%8 != 0){
			pos += 1;
			RAYS[i][2] |= 1UL << (pos);
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
