#include <vector>
#include <string>
#include <cmath>
#include "board.h"
#include "move.h"

using namespace std;

void Board::genBoardFromFEN(string FEN){
	int indexFEN = 0, indexBoard = 56;

	allPieces = 0;

	whitePieces = 0;
	whiteKing = 0;
	whiteQueen = 0;
	whiteRooks = 0;
	whiteBishops = 0;
	whiteKnights = 0;
	whitePawns = 0;

	blackPieces = 0;
	blackKing = 0;
	blackQueen = 0;
	blackRooks = 0;
	blackBishops = 0;
	blackKnights = 0;
	blackPawns = 0;

	//reading in board and setting bitboards
	while(FEN[indexFEN] != ' '){
		switch(FEN[indexFEN]){
			case 'k': blackKing |= 1ULL << indexBoard; break;
			case 'q': blackQueen |= 1ULL << indexBoard; break;
			case 'r': blackRooks |= 1ULL << indexBoard; break;
			case 'b': blackBishops |= 1ULL << indexBoard; break;
			case 'n': blackKnights |= 1ULL << indexBoard; break;
			case 'p': blackPawns |= 1ULL << indexBoard; break;

			case 'K': whiteKing |= 1ULL << indexBoard; break;
			case 'Q': whiteQueen |= 1ULL << indexBoard; break;
			case 'R': whiteRooks |= 1ULL << indexBoard; break;
			case 'B': whiteBishops |= 1ULL << indexBoard; break;
			case 'N': whiteKnights |= 1ULL << indexBoard; break;
			case 'P': whitePawns |= 1ULL << indexBoard; break;

			case '/' : indexBoard -= 17; break;
			case '1' : break;
			case '2' : indexBoard++; break;
			case '3' : indexBoard += 2; break;
			case '4' : indexBoard += 3; break;
			case '5' : indexBoard += 4; break;
			case '6' : indexBoard += 5; break;
			case '7' : indexBoard += 6; break;
			case '8' : indexBoard += 7; break;
		}
		indexFEN++;
		indexBoard++;
	}
	whitePieces = whiteKing | whiteQueen | whiteRooks | whiteBishops | whiteKnights | whitePawns;
	blackPieces = blackKing | blackQueen | blackRooks | blackBishops | blackKnights | blackPawns;
	allPieces = whitePieces | blackPieces;

	//reading in who's turn it is
	indexFEN++;
	if(FEN[indexFEN] == 'w') whiteTurn = true;
	else whiteTurn = false;

	//reading in castling rights
	indexFEN += 2;
	whiteCastleRightsKS = false;
	whiteCastleRightsQS = false;
	blackCastleRightsKS = false;
	blackCastleRightsQS = false;
	while(FEN[indexFEN] != ' '){
		switch(FEN[indexFEN]){
			case 'K': whiteCastleRightsKS = true; break;
			case 'Q': whiteCastleRightsQS = true; break;
			case 'k': blackCastleRightsKS = true; break;
			case 'q': blackCastleRightsQS = true; break;
			case '-': break;
		}
		indexFEN++;
	}
	indexFEN++;

	//reading in en passant target square
	enPassantTargetSquare = 0;
	if(FEN[indexFEN] != '-'){
		enPassantTargetSquare = ((FEN[indexFEN + 1] - 49) * 8) + (FEN[indexFEN] - 97);
		indexFEN++;
	}

	//reading in half move clock
	indexFEN += 2;
	string num = "";
	while(FEN[indexFEN] != ' '){
		num += FEN[indexFEN];
		indexFEN++;
	}
	halfMoveClock = stoi(num);

	//reading in number of full moves
	indexFEN++;
	num = "";
	while((long unsigned int)indexFEN < FEN.length()){
		num += FEN[indexFEN];
		indexFEN++;
	}
	fullMoveNumber = stoi(num);
}

void Board::printBitBoard(unsigned long long bitBoard){
	for(int r = 7; r >= 0; r--){
		for(int c = 0; c < 8; c++){
			if(bitBoard & (1ULL << ((r * 8) + c))) printf("1 ");
			else printf(". ");
		}
		printf("\n");
	}
	printf("\n");
}

void Board::printPosition(){
	printf("All Pieces\n");
	printBitBoard(allPieces);
	printf("White Pieces\n");
	printBitBoard(whitePieces);
	printf("White King\n");
	printBitBoard(whiteKing);
	printf("White Queen\n");
	printBitBoard(whiteQueen);
	printf("White Rooks\n");
	printBitBoard(whiteRooks);
	printf("White Bishops\n");
	printBitBoard(whiteBishops);
	printf("White Knights\n");
	printBitBoard(whiteKnights);
	printf("White Pawns\n");
	printBitBoard(whitePawns);
	printf("Black Pieces\n");
	printBitBoard(blackPieces);
	printf("Black King\n");
	printBitBoard(blackKing);
	printf("Black Queen\n");
	printBitBoard(blackQueen);
	printf("Black Rooks\n");
	printBitBoard(blackRooks);
	printf("Black Bishops\n");
	printBitBoard(blackBishops);
	printf("Black Knights\n");
	printBitBoard(blackKnights);
	printf("Black Pawns\n");
	printBitBoard(blackPawns);
	if(whiteTurn) printf("White's Turn\n");
	else printf("Black's Turn\n");
	printf("White Castle Rights KS: %d\n", whiteCastleRightsKS);
	printf("White Castle Rights QS: %d\n", whiteCastleRightsQS);
	printf("Black Castle Rights KS: %d\n", blackCastleRightsKS);
	printf("Black Castle Rights QS: %d\n", blackCastleRightsQS);
	printf("En Passant Target Square: %d\n", enPassantTargetSquare);
	printf("Moves Since Last Capture or Pawn Advance: %d\n", halfMoveClock);
	printf("Full Move Number: %d\n", fullMoveNumber);
}

//returns index of the least significant bit that is set to 1
int Board::getLSBIndex(unsigned long long bitBoard){
	bitBoard = bitBoard ^ (bitBoard - 1);

	return __builtin_popcountll(bitBoard) - 1;
}

void Board::genMoves(){
	/*
	unsigned long long tmpBitBoard;
	int square;

	if(whiteTurn){

		instead of looping through the whole bitboard to find bits set to one,
		we can keep finding the lsb set to one, do what we need to do with it,
		set it to zero, and repeat until the bitboard == 0

		tmpBitBoard = whiteKing;
		while(whiteKing){
			square = getLSBIndex(whiteKing);
			genKingMoves(square);
			whiteKing ^= 1ULL << square;
		}
		whiteKing = tmpBitBoard;

		tmpBitBoard = whiteKnight;
		while(whiteKnight){
			square = getLSBIndex(whiteKnight);
			genKnightMoves(square);
			whiteKnight ^= 1ULL << square;
		}
		whiteKnight = tmpBitBoard;

		just do king and knight for now because they are easy
	}
	else{

		same thing but for black
	}

	*/
}

void Board::genKingMoves(int square){

}

void Board::genQueenMoves(int square){

}

void Board::genRookMoves(int square){

}

void Board::genBishopMoves(int square){

}

void Board::genKnightMoves(int square){

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

void Board::INITIALIZE_KING_LOOKUP_TBL(){
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

void Board::INITIALIZE_KNIGHT_LOOKUP_TBL(){
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

void Board::INITIALIZE_RAYS(){
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
		while(pos-9 >= 0 && (pos-9)%8 != 7){
			pos -= 9;
			RAYS[i][5] |= (1ULL << pos);
		}
		//w
		pos = i;
		while(pos%8 != 0 && (pos-1)%8 != 7){
			pos -= 1;
			RAYS[i][6] |= (1ULL << pos);
		}
		//nw
		pos = i;
		RAYS[i][1] = 0;
		while((pos+9)%8 != 0 && (pos+9) < 63){
			pos += 7;
			RAYS[i][7] |= (1ULL << pos);
		}
	}
}
