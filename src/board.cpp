#include <string>
#include <cmath>
#include <sstream>
#include "board.h"
#include "move.h"

using namespace std;

void Board::genBoardFromFEN(string FEN){
	int indexFEN = 0, indexBoard = 56;

	allPieces = 0;
	emptySquares = 0;
	pieces[0] = 0;
	pieces[1] = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 6; j++){
			pieceTypes[i][j] = 0;
		}
	}

	//reading in board and setting bitboards
	while(FEN[indexFEN] != ' '){
		switch(FEN[indexFEN]){
			case 'k': pieceTypes[1][0] |= 1ULL << indexBoard; break;
			case 'q': pieceTypes[1][1] |= 1ULL << indexBoard; break;
			case 'r': pieceTypes[1][2] |= 1ULL << indexBoard; break;
			case 'b': pieceTypes[1][3] |= 1ULL << indexBoard; break;
			case 'n': pieceTypes[1][4] |= 1ULL << indexBoard; break;
			case 'p': pieceTypes[1][5] |= 1ULL << indexBoard; break;

			case 'K': pieceTypes[0][0] |= 1ULL << indexBoard; break;
			case 'Q': pieceTypes[0][1] |= 1ULL << indexBoard; break;
			case 'R': pieceTypes[0][2] |= 1ULL << indexBoard; break;
			case 'B': pieceTypes[0][3] |= 1ULL << indexBoard; break;
			case 'N': pieceTypes[0][4] |= 1ULL << indexBoard; break;
			case 'P': pieceTypes[0][5] |= 1ULL << indexBoard; break;

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
	pieces[0] = pieceTypes[0][0] | pieceTypes[0][1] | pieceTypes[0][2] | pieceTypes[0][3] | pieceTypes[0][4] | pieceTypes[0][5];
	pieces[1] = pieceTypes[1][0] | pieceTypes[1][1] | pieceTypes[1][2] | pieceTypes[1][3] | pieceTypes[1][4] | pieceTypes[1][5];
	allPieces = pieces[0] | pieces[1];
	emptySquares = ~allPieces;

	//reading in who's turn it is
	indexFEN++;
	if(FEN[indexFEN] == 'w') color = 0;
	else color = 1;

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

string Board::genFENFromBoard(){
	stringstream ss;
	char FENarr[64];
	int FENarrIndex = 0;
	int emptySqCount = 0;

	ss.clear();

	for(int i = 0; i < 64; i++){
		FENarr[i] = '.';
	}

	for(int i = 56; i > -1; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 6; k++){
				if(pieceTypes[j][k] & (1ULL << i)){
					if(j == 0){
						switch(k){
							case 0: FENarr[FENarrIndex] = 'K'; break;
							case 1: FENarr[FENarrIndex] = 'Q'; break;
							case 2: FENarr[FENarrIndex] = 'R'; break;
							case 3: FENarr[FENarrIndex] = 'B'; break;
							case 4: FENarr[FENarrIndex] = 'N'; break;
							case 5: FENarr[FENarrIndex] = 'P'; break;
						}
					}
					else{
						switch(k){
							case 0: FENarr[FENarrIndex] = 'k'; break;
							case 1: FENarr[FENarrIndex] = 'q'; break;
							case 2: FENarr[FENarrIndex] = 'r'; break;
							case 3: FENarr[FENarrIndex] = 'b'; break;
							case 4: FENarr[FENarrIndex] = 'n'; break;
							case 5: FENarr[FENarrIndex] = 'p'; break;
						}
					}
				}
			}
		}
		if(i % 8 == 7) i -= 16;
		FENarrIndex++;
	}

	for(int i = 0; i < 64; i++){
		if(FENarr[i] == '.') emptySqCount++;
		else{
			if(emptySqCount != 0){ss << emptySqCount; emptySqCount = 0;}
			ss << FENarr[i];
		}
		if(i % 8 == 7){
			if(emptySqCount != 0){ss << emptySqCount; emptySqCount = 0;}
			if(i != 63) ss << "/";
		}
	}

	ss << " ";
	if(color == 0) ss << "w";
	else ss << "b";
	ss << " ";
	if(!whiteCastleRightsKS && !whiteCastleRightsQS && !blackCastleRightsKS && !blackCastleRightsQS){
		ss << "-";
	}
	else{
		if(whiteCastleRightsKS) ss << "K";
		if(whiteCastleRightsQS) ss << "Q";
		if(blackCastleRightsKS) ss << "k";
		if(blackCastleRightsQS) ss << "q";
	}
	ss << " ";
	if(enPassantTargetSquare == 0) ss << "-";
	else {ss << char((enPassantTargetSquare % 8) + 97); ss << char((enPassantTargetSquare / 8) + 49);}
	ss << " ";
	ss << halfMoveClock;
	ss << " ";
	ss << fullMoveNumber;

	return ss.str();
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
	printf("Empty Sqaures\n");
	printBitBoard(emptySquares);
	printf("White Pieces\n");
	printBitBoard(pieces[0]);
	printf("White King\n");
	printBitBoard(pieceTypes[0][0]);
	printf("White Queen\n");
	printBitBoard(pieceTypes[0][1]);
	printf("White Rooks\n");
	printBitBoard(pieceTypes[0][2]);
	printf("White Bishops\n");
	printBitBoard(pieceTypes[0][3]);
	printf("White Knights\n");
	printBitBoard(pieceTypes[0][4]);
	printf("White Pawns\n");
	printBitBoard(pieceTypes[0][5]);
	printf("Black Pieces\n");
	printBitBoard(pieces[1]);
	printf("Black King\n");
	printBitBoard(pieceTypes[1][0]);
	printf("Black Queen\n");
	printBitBoard(pieceTypes[1][1]);
	printf("Black Rooks\n");
	printBitBoard(pieceTypes[1][2]);
	printf("Black Bishops\n");
	printBitBoard(pieceTypes[1][3]);
	printf("Black Knights\n");
	printBitBoard(pieceTypes[1][4]);
	printf("Black Pawns\n");
	printBitBoard(pieceTypes[1][5]);
	if(!color) printf("White's Turn\n");
	else printf("Black's Turn\n");
	printf("White Castle Rights KS: %d\n", whiteCastleRightsKS);
	printf("White Castle Rights QS: %d\n", whiteCastleRightsQS);
	printf("Black Castle Rights KS: %d\n", blackCastleRightsKS);
	printf("Black Castle Rights QS: %d\n", blackCastleRightsQS);
	printf("En Passant Target Square: %d\n", enPassantTargetSquare);
	printf("Moves Since Last Capture or Pawn Advance: %d\n", halfMoveClock);
	printf("Full Move Number: %d\n\n\n", fullMoveNumber);
}

void Board::printMoves(){
	printf("%d POSSIBLE MOVES\n", moveIndex);
	for(int i = 0; i < moveIndex; i++){
		moves[i].printMove();
	}
}

//returns index of the least significant bit that is set to 1
int Board::getLSBIndex(unsigned long long bitBoard){
	return __builtin_ctzll(bitBoard);
}

int Board::getMSBIndex(unsigned long long bitBoard){
	return 63 - __builtin_clzll(bitBoard);
}

void Board::genMoves(){
	unsigned long long tmpBitBoard;
	int square;

	/*
	instead of looping through the whole bitboard to find bits set to 1,
	we can keep finding the lsb set to 1, do what we need to do with it,
	set it to 0, and repeat until the bitboard == 0
	*/
	moveIndex = 0; //set/reset the index of the moves array

	tmpBitBoard = pieceTypes[color][0];
	while(pieceTypes[color][0]){
		square = getLSBIndex(pieceTypes[color][0]);
		genKingMoves(square);
		pieceTypes[color][0] &= pieceTypes[color][0] - 1;
	}
	pieceTypes[color][0] = tmpBitBoard;

	tmpBitBoard = pieceTypes[color][1];
	while(pieceTypes[color][1]){
		square = getLSBIndex(pieceTypes[color][1]);
		genQueenMoves(square);
		pieceTypes[color][1] &= pieceTypes[color][1] - 1;
	}
	pieceTypes[color][1] = tmpBitBoard;

	tmpBitBoard = pieceTypes[color][2];
	while(pieceTypes[color][2]){
		square = getLSBIndex(pieceTypes[color][2]);
		genRookMoves(square);
		pieceTypes[color][2] &= pieceTypes[color][2] - 1;
	}
	pieceTypes[color][2] = tmpBitBoard;

	tmpBitBoard = pieceTypes[color][3];
	while(pieceTypes[color][3]){
		square = getLSBIndex(pieceTypes[color][3]);
		genBishopMoves(square);
		pieceTypes[color][3] &= pieceTypes[color][3] - 1;
	}
	pieceTypes[color][3] = tmpBitBoard;

	tmpBitBoard = pieceTypes[color][4];
	while(pieceTypes[color][4]){
		square = getLSBIndex(pieceTypes[color][4]);
		genKnightMoves(square);
		pieceTypes[color][4] &= pieceTypes[color][4] - 1;
	}
	pieceTypes[color][4] = tmpBitBoard;


	genPawnLeftMoves();
	genPawnSinglePushMoves();
	genPawnDoublePushMoves();
	genPawnRightMoves();
	if(enPassantTargetSquare != 0) genEnPassantMoves();
	if(color == 0 && whiteCastleRightsKS) genCastleKS();
	else if(color == 1 && blackCastleRightsKS) genCastleKS();
	if(color == 0 && whiteCastleRightsQS) genCastleQS();
	else if(color == 1 && blackCastleRightsQS) genCastleQS();
}

void Board::genKingMoves(int square){
	unsigned long long king_moves;
	int new_square;
	Move move;

	king_moves = KING_LOOKUP_TBL[square] ^ (pieces[color] & KING_LOOKUP_TBL[square]);

	while(king_moves != 0){
        new_square = getLSBIndex(king_moves);
        king_moves &= king_moves - 1;
    	move.createMove(square, new_square, 0, 0);
		moves[moveIndex++] = move;
    }
}

void Board::genQueenMoves(int square){
	genRookMoves(square);
	genBishopMoves(square);
}

void Board::genRookMoves(int square){
    unsigned long long rm = 0;
	int block, new_square;
	Move move;

	// North
	rm |= RAYS[square][0] ^ (pieces[color] & RAYS[square][0]);
	if(RAYS[square][0] & allPieces){
		block = getLSBIndex(RAYS[square][0] & allPieces);
		rm &= ~RAYS[block][0];
	}
	// East
	rm |= RAYS[square][2] ^ (pieces[color] & RAYS[square][2]);
	if(RAYS[square][2] & allPieces){
		block = getLSBIndex(RAYS[square][2] & allPieces);
		rm &= ~RAYS[block][2];
	}
	// South
	rm |= RAYS[square][4] ^ (pieces[color] & RAYS[square][4]);
	if(RAYS[square][4] & allPieces){
		block = getMSBIndex(RAYS[square][4] & allPieces);
		rm &= ~RAYS[block][4];
	}
	// West
	rm |= RAYS[square][6] ^ (pieces[color] & RAYS[square][6]);
	if(RAYS[square][6] & allPieces){
		block = getMSBIndex(RAYS[square][6] & allPieces);
		rm &= ~RAYS[block][6];
	}

	while(rm != 0){
        new_square = getLSBIndex(rm);
        rm &= rm - 1;
    	move.createMove(square, new_square, 0, 0);
		moves[moveIndex++] = move;
    }
}

void Board::genBishopMoves(int square){
	unsigned long long bishop_moves = 0;
	int new_square;
	Move move;

	//ne
	bishop_moves |= RAYS[square][1] ^ (pieces[color] & RAYS[square][1]);
	if(RAYS[square][1] & allPieces){
		new_square = getLSBIndex(RAYS[square][1]&allPieces);
		bishop_moves &= ~RAYS[new_square][1];
	}
	//se
	bishop_moves |= RAYS[square][3] ^ (pieces[color] & RAYS[square][3]);
	if(RAYS[square][3] & allPieces){
		new_square = getMSBIndex(RAYS[square][3]&allPieces);
		bishop_moves &= ~RAYS[new_square][3];
	}
	//sw
	bishop_moves |= RAYS[square][5] ^ (pieces[color] & RAYS[square][5]);
	if(RAYS[square][5] & allPieces){
		new_square = getMSBIndex(RAYS[square][5]&allPieces);
		bishop_moves &= ~RAYS[new_square][5];
	}
	//nw
	bishop_moves |= RAYS[square][7] ^ (pieces[color] & RAYS[square][7]);
	if(RAYS[square][7] & allPieces){
		new_square = getLSBIndex(RAYS[square][7] & allPieces);
		bishop_moves &= ~RAYS[new_square][7];
	}

    while(bishop_moves != 0){
        new_square = getLSBIndex(bishop_moves);
        bishop_moves &= bishop_moves - 1;
    	move.createMove(square, new_square, 0, 0);
		moves[moveIndex++] = move;
    }
}

void Board::genKnightMoves(int square){
	unsigned long long knight_moves;
	int new_square;
	Move move;

	knight_moves = KNIGHT_LOOKUP_TBL[square] ^ (pieces[color] & KNIGHT_LOOKUP_TBL[square]);

	while(knight_moves != 0){
        new_square = getLSBIndex(knight_moves);
        knight_moves &= knight_moves - 1;
    	move.createMove(square, new_square, 0, 0);
		moves[moveIndex++] = move;
    }
}

void Board::genPawnLeftMoves(){
	unsigned long long pawn_left_moves = 0;
	int new_square;
	int square;
	Move move;

    if(color == 0){
        pawn_left_moves = ((pieceTypes[0][5] << 7ULL) & ~FILE_H) & pieces[1];

		//pawn promotion
		if(pawn_left_moves & RANK_8){
			pawn_left_moves = genPromoMoves(pawn_left_moves, RANK_8, -7);
		}

		while(pawn_left_moves != 0){
			new_square = getLSBIndex(pawn_left_moves);
			square = new_square - 7;
			pawn_left_moves &= pawn_left_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }else{ // Black's Turn
        pawn_left_moves = ((pieceTypes[0][5] >> 7ULL) & ~FILE_A) & pieces[0];

		//pawn promotion
		if(pawn_left_moves & RANK_1){
			pawn_left_moves = genPromoMoves(pawn_left_moves, RANK_1, 7);
		}

		while(pawn_left_moves != 0){
			new_square = getLSBIndex(pawn_left_moves);
			square = new_square + 7;
			pawn_left_moves &= pawn_left_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }
}

void Board::genPawnSinglePushMoves(){
	unsigned long long pawn_sp_moves = 0;
	int new_square;
	int square;
	Move move;

    if(color == 0){
        pawn_sp_moves = (pieceTypes[0][5] << 8ULL) & emptySquares;

		//pawn promotion
		if(pawn_sp_moves & RANK_8){
			pawn_sp_moves = genPromoMoves(pawn_sp_moves, RANK_8, -8);
		}

		while(pawn_sp_moves != 0){
			new_square = getLSBIndex(pawn_sp_moves);
			square = new_square - 8;
			pawn_sp_moves &= pawn_sp_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }else{ // Black's Turn
        pawn_sp_moves = (pieceTypes[1][5] >> 8ULL) & emptySquares;

		//pawn promotion
		if(pawn_sp_moves & RANK_1){
			pawn_sp_moves = genPromoMoves(pawn_sp_moves, RANK_1, 8);
		}

		while(pawn_sp_moves != 0){
			new_square = getLSBIndex(pawn_sp_moves);
			square = new_square + 8;
			pawn_sp_moves &= pawn_sp_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }
}

void Board::genPawnDoublePushMoves(){
	unsigned long long pawn_dp_moves = 0;
	int new_square, square;
	Move move;

    if(color == 0){
        pawn_dp_moves = ((pieceTypes[0][5] << 16ULL) & (((emptySquares & RANK_3) << 8ULL) & (emptySquares & RANK_4)));
		while(pawn_dp_moves != 0){
			new_square = getLSBIndex(pawn_dp_moves);
			square = new_square - 16;
			pawn_dp_moves &= pawn_dp_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }else{ // Black's Turn
        pawn_dp_moves = ((pieceTypes[1][5] >> 16ULL) & (((emptySquares & RANK_6) >> 8ULL) & (emptySquares & RANK_5)));
		while(pawn_dp_moves != 0){
			new_square = getLSBIndex(pawn_dp_moves);
			square = new_square + 16;
			pawn_dp_moves &= pawn_dp_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }
}

void Board::genPawnRightMoves(){
	unsigned long long pawn_right_moves = 0;
	int new_square, square;
	Move move;

    if(color == 0){
        pawn_right_moves = ((pieceTypes[0][5] << 9ULL) & ~FILE_A) & pieces[1];

		//pawn promotion
		if(pawn_right_moves & RANK_8){
			pawn_right_moves = genPromoMoves(pawn_right_moves, RANK_8, -9);
		}

		while(pawn_right_moves != 0){
			new_square = getLSBIndex(pawn_right_moves);
			square = new_square - 9;
			pawn_right_moves &= pawn_right_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }else{ // Black's Turn
        pawn_right_moves = ((pieceTypes[1][5] >> 9ULL) & ~FILE_H) & pieces[0];

		//pawn promotion
		if(pawn_right_moves & RANK_1){
			pawn_right_moves = genPromoMoves(pawn_right_moves, RANK_1, 9);
		}

		while(pawn_right_moves != 0){
			new_square = getLSBIndex(pawn_right_moves);
			square = new_square + 9;
			pawn_right_moves &= pawn_right_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }
}

unsigned long long Board::genPromoMoves(unsigned long long input_bb, unsigned long long rank_mask, int offset){
	int square, new_square;
	unsigned long long promo_moves = input_bb & rank_mask;
	Move move;

	while(promo_moves != 0){
		new_square = getLSBIndex(promo_moves);
		square = new_square + offset;
		promo_moves &= promo_moves - 1;
		move.createMove(square, new_square, 3, 1);
		moves[moveIndex++] = move;
		move.createMove(square, new_square, 3, 2);
		moves[moveIndex++] = move;
		move.createMove(square, new_square, 3, 3);
		moves[moveIndex++] = move;
		move.createMove(square, new_square, 3, 4);
		moves[moveIndex++] = move;
	}
	input_bb &= ~rank_mask;
	return input_bb;
}

void Board::genEnPassantMoves(){
	unsigned long long enpass_moves = 0;
	int new_square, square;
	Move move;

    if(color == 0){
        enpass_moves = ((pieceTypes[0][5] << 7ULL) & ~FILE_H) & (1ULL << enPassantTargetSquare);

		while(enpass_moves != 0){
			new_square = getLSBIndex(enpass_moves);
			square = new_square - 7;
			enpass_moves &= enpass_moves - 1;
			move.createMove(square, new_square, 1, 0);
			moves[moveIndex++] = move;
		}

		enpass_moves = ((pieceTypes[0][5] << 9ULL) & ~FILE_A) & (1ULL << enPassantTargetSquare);

		while(enpass_moves != 0){
			new_square = getLSBIndex(enpass_moves);
			square = new_square - 9;
			enpass_moves &= enpass_moves - 1;
			move.createMove(square, new_square, 1, 0);
			moves[moveIndex++] = move;
		}
    }else{ // Black's Turn
        enpass_moves = ((pieceTypes[1][5] >> 7ULL) & ~FILE_A) & (1ULL << enPassantTargetSquare);

		while(enpass_moves != 0){
			new_square = getLSBIndex(enpass_moves);
			square = new_square + 7;
			enpass_moves &= enpass_moves - 1;
			move.createMove(square, new_square, 1, 0);
			moves[moveIndex++] = move;
		}

		enpass_moves = ((pieceTypes[1][5] >> 9ULL) & ~FILE_H) & (1ULL << enPassantTargetSquare);

		while(enpass_moves != 0){
			new_square = getLSBIndex(enpass_moves);
			square = new_square + 9;
			enpass_moves &= enpass_moves - 1;
			move.createMove(square, new_square, 1, 0);
			moves[moveIndex++] = move;
		}
    }
}

void Board::genCastleKS(){
	Move move;

	if(color == 0){
		//makes sure no pieces are blocking
		if(((3ULL << 5) & allPieces) == 0){
			move.createMove(4, 6, 2, 0);
			moves[moveIndex++] = move;
		}
	}
	else{
		//makes sure no pieces are blocking
		if(((3ULL << 61) & allPieces) == 0){
			move.createMove(60, 62, 2, 0);
			moves[moveIndex++] = move;
		}
	}
}

void Board::genCastleQS(){
	Move move;

	if(color == 0){
		//makes sure no pieces are blocking
		if(((7ULL << 1) & allPieces) == 0){
			move.createMove(4, 2, 2, 0);
			moves[moveIndex++] = move;
		}
	}
	else{
		//makes sure no pieces are blocking
		if(((7ULL << 57) & allPieces) == 0){
			move.createMove(60, 58, 2, 0);
			moves[moveIndex++] = move;
		}
	}
}

int Board::squareUnderAttack(int square){
	int new_square;
	unsigned long long tmpBitBoard = 0;
	//Knight
		if((KNIGHT_LOOKUP_TBL[square] & pieceTypes[!color][4]) != 0) return 1;
		//Bishop/Queen
		//ne
		tmpBitBoard |= RAYS[square][1] ^ (pieces[color] & RAYS[square][1]);
		if(RAYS[square][1] & allPieces){
			new_square = getLSBIndex(RAYS[square][1]&allPieces);
			tmpBitBoard &= ~RAYS[new_square][1];
		}
		//se
		tmpBitBoard |= RAYS[square][3] ^ (pieces[color] & RAYS[square][3]);
		if(RAYS[square][3] & allPieces){
			new_square = getMSBIndex(RAYS[square][3]&allPieces);
			tmpBitBoard &= ~RAYS[new_square][3];
		}
		//sw
		tmpBitBoard |= RAYS[square][5] ^ (pieces[color] & RAYS[square][5]);
		if(RAYS[square][5] & allPieces){
			new_square = getMSBIndex(RAYS[square][5]&allPieces);
			tmpBitBoard &= ~RAYS[new_square][5];
		}
		//nw
		tmpBitBoard |= RAYS[square][7] ^ (pieces[color] & RAYS[square][7]);
		if(RAYS[square][7] & allPieces){
			new_square = getLSBIndex(RAYS[square][7] & allPieces);
			tmpBitBoard &= ~RAYS[new_square][7];
		}
		if((tmpBitBoard & pieceTypes[!color][3]) != 0 || (tmpBitBoard & pieceTypes[!color][1]) != 0) return 1;

		//Rook/Queen
		tmpBitBoard = 0;
		//n
		tmpBitBoard |= RAYS[square][0] ^ (pieces[color] & RAYS[square][0]);
		if(RAYS[square][0] & allPieces){
			new_square = getLSBIndex(RAYS[square][0]&allPieces);
			tmpBitBoard &= ~RAYS[new_square][0];
		}
		//e
		tmpBitBoard |= RAYS[square][2] ^ (pieces[color] & RAYS[square][2]);
		if(RAYS[square][2] & allPieces){
			new_square = getLSBIndex(RAYS[square][2]&allPieces);
			tmpBitBoard &= ~RAYS[new_square][2];
		}
		//s
		tmpBitBoard |= RAYS[square][4] ^ (pieces[color] & RAYS[square][4]);
		if(RAYS[square][4] & allPieces){
			new_square = getLSBIndex(RAYS[square][4]&allPieces);
			tmpBitBoard &= ~RAYS[new_square][4];
		}
		//w
		tmpBitBoard |= RAYS[square][6] ^ (pieces[color] & RAYS[square][6]);
		if(RAYS[square][6] & allPieces){
			new_square = getLSBIndex(RAYS[square][6]&allPieces);
			tmpBitBoard &= ~RAYS[new_square][6];
		}
		if((tmpBitBoard & pieceTypes[!color][2]) != 0 || (tmpBitBoard & pieceTypes[!color][1]) != 0) return 1;
		//King
		if(KING_LOOKUP_TBL[getLSBIndex(pieceTypes[!color][0])] & square){
			return 1;
		}
		//Pawn (will change slightly for black)
		if(color){
			if((pieceTypes[!color][5] & (1 << (square-9))) != 0 || (pieceTypes[!color][1] & (1 << (square-7)))) return 1;
		}else{
			if((pieceTypes[!color][5] & (1 << (square+9))) != 0 || (pieceTypes[!color][1] & (1 << (square+7)))) return 1;
		}

	return 0;
}

int Board::makeMove(Move move){
	//call appropriate make move function
	switch(move.specialMove){
		case 0: return makeNormalMove(move);
		case 1: makeEnPassMove(move); break;
		case 2: makeCastleMove(move); break;
		case 3: makePromotionMove(move); break;
	}
	return 0;
}

//returns 1 if move is a capture, otherwise returns 0
int Board::makeNormalMove(Move move){
	//setting/unsetting squares for side that is moving
	for(int i = 5; i >= 0; i--){
		if(pieceTypes[color][i] & (1ULL << move.fromSquare)){
			pieceTypes[color][i] ^= (1ULL << move.fromSquare);
			pieces[color] ^= (1ULL << move.fromSquare);
			pieceTypes[color][i] |= (1ULL << move.toSquare);
			pieces[color] |= (1ULL << move.toSquare);
			break;
		}
	}

	//if move captures opponent's piece, update the opponent's bitboards
	if(pieces[!color] & (1ULL << move.toSquare)){
		for(int i = 5; i > 0; i--){
			if(pieceTypes[!color][i] & (1ULL << move.toSquare)){
				pieceTypes[!color][i] ^= (1ULL << move.toSquare);
				pieces[!color] ^= (1ULL << move.toSquare);

				//update allPieces and emptySquares
				allPieces = pieces[0] | pieces[1];
				emptySquares = ~allPieces;

				//retval is used for capture parameter in undoNormalMove that tells us the piece that was captured
				//0 = no capture, 1 = queen capture, 2 = rook capture, etc.
				//king cannot be captured, so that is why 0 can represent a non capture
				return i;
			}
		}
	}

	//update allPieces and emptySquares
	allPieces = pieces[0] | pieces[1];
	emptySquares = ~allPieces;

	return 0;
}

void Board::makeEnPassMove(Move move){
	//Remove players pawn origin
	pieceTypes[color][5] &= ~(1ULL << move.fromSquare);
	allPieces &= ~(1ULL << move.fromSquare);

	//Remove caputured pawn
	pieceTypes[!color][5] &= ~(1ULL << (move.toSquare - 8));
	allPieces &= ~(1ULL << (move.toSquare - 8));

	//Place players pawn in new spot
	pieceTypes[color][5] |= (1ULL << move.toSquare);
	allPieces |= (1ULL << move.toSquare);

	emptySquares = ~allPieces;
}

void Board::makeCastleMove(Move move){
	//unsetting/setting king bitboards
	pieceTypes[color][0] ^= (1ULL << move.fromSquare);
	pieces[color] ^= (1ULL << move.fromSquare);
	pieceTypes[color][0] |= (1ULL << move.toSquare);
	pieces[color] |= (1ULL << move.toSquare);

	//unsetting/setting rook bitboards
	//if kingside castle
	if(move.fromSquare < move.toSquare){
		int rookSquare = getMSBIndex(pieceTypes[color][2]);
		pieceTypes[color][2] ^= (1ULL << rookSquare);
		pieces[color] ^= (1ULL << rookSquare);
		pieceTypes[color][2] |= (1ULL << (move.toSquare - 1));
		pieces[color] |= (1ULL << (move.toSquare - 1));
	}
	//else queenside castle
	else{
		int rookSquare = getLSBIndex(pieceTypes[color][2]);
		pieceTypes[color][2] ^= (1ULL << rookSquare);
		pieces[color] ^= (1ULL << rookSquare);
		pieceTypes[color][2] |= (1ULL << (move.toSquare + 1));
		pieces[color] |= (1ULL << (move.toSquare + 1));
	}

	//update allPieces and emptySquares
	allPieces = pieces[0] | pieces[1];
	emptySquares = ~allPieces;
}

//Updates bit boards for a pawn promotion
int Board::makePromotionMove(Move move){
	int capturedPieceType = 0;
	if((allPieces&(1<<move.toSquare)) != 0){
		//Capture into Promotion
		for(int i = 1; i < 4; i++){
			if((pieceTypes[!color][i] & (1 << move.toSquare)) != 0){
				pieceTypes[!color][i] &= ~(1 << move.toSquare);
				pieces[!color] &= ~(1 << move.toSquare);
				capturedPieceType = i;
				break;
			}
		}
	}
	allPieces &= ~(1 << move.fromSquare);
	allPieces |= (1 << move.toSquare);
	emptySquares &= ~(1 << move.toSquare);
	emptySquares |= (1 << move.fromSquare);
	pieces[color] &= ~(1 << move.fromSquare);
	pieces[color] |= (1 << move.toSquare);
	pieceTypes[color][5] &= ~(1 << move.fromSquare);
	pieceTypes[color][int(move.promotedPiece)] |= (1 << move.toSquare);

	return capturedPieceType;
}

void Board::undoMove(Move move, int capturedPieceType){
	//call appropriate undo move function
	//capture parameter tells us the piece that was captured
	//0 = no capture, 1 = queen capture, 2 = rook capture, etc.
	//king cannot be captured, so that is why 0 can represent a non capture
	switch(move.specialMove){
		case 0: undoNormalMove(move, capturedPieceType); break;
		case 1: undoEnPassMove(move); break;
		case 2: undoCastleMove(move); break;
		case 3: undoPromotionMove(move, capturedPieceType); break;
	}
}

void Board::undoNormalMove(Move move, int capturedPieceType){
	//setting/unsetting squares for side that was moving
	for(int i = 5; i >= 0; i--){
		if(pieceTypes[color][i] & (1ULL << move.toSquare)){
			pieceTypes[color][i] ^= (1ULL << move.toSquare);
			pieces[color] ^= (1ULL << move.toSquare);
			pieceTypes[color][i] |= (1ULL << move.fromSquare);
			pieces[color] |= (1ULL << move.fromSquare);
			break;
		}
	}

	//if move captured opponent's piece, update the opponent's bitboards
	if(capturedPieceType){
		pieceTypes[!color][capturedPieceType] |= (1ULL << move.toSquare);
		pieces[!color] |= (1ULL << move.toSquare);
	}

	//update allPieces and emptySquares
	allPieces = pieces[0] | pieces[1];
	emptySquares = ~allPieces;
}

void Board::undoEnPassMove(Move move){
	//Remove players pawn from landing square
	pieceTypes[color][5] &= ~(1ULL << move.toSquare);
	allPieces &= ~(1ULL << move.toSquare);

	//add caputured pawn
	pieceTypes[!color][5] |= ~(1ULL << (move.toSquare - 8));
	allPieces &= ~(1ULL << (move.toSquare - 8));

	//Place players pawn in original spot
	pieceTypes[color][5] |= (1ULL << move.fromSquare);
	allPieces |= (1ULL << move.fromSquare);

	emptySquares = ~allPieces;
}

void Board::undoCastleMove(Move move){
	//unsetting/setting king bitboards
	pieceTypes[color][0] ^= (1ULL << move.toSquare);
	pieces[color] ^= (1ULL << move.toSquare);
	pieceTypes[color][0] |= (1ULL << move.fromSquare);
	pieces[color] |= (1ULL << move.fromSquare);

	//unsetting/setting rook bitboards
	//if kingside castle
	if(move.fromSquare < move.toSquare){
		int rookSquare = getMSBIndex(pieceTypes[color][2]);
		pieceTypes[color][2] ^= (1ULL << rookSquare);
		pieces[color] ^= (1ULL << rookSquare);
		pieceTypes[color][2] |= (1ULL << (rookSquare + 2));
		pieces[color] |= (1ULL << (rookSquare + 2));
	}
	//else queenside castle
	else{
		int rookSquare = getLSBIndex(pieceTypes[color][2]);
		pieceTypes[color][2] ^= (1ULL << rookSquare);
		pieces[color] ^= (1ULL << rookSquare);
		pieceTypes[color][2] |= (1ULL << (rookSquare - 3));
		pieces[color] |= (1ULL << (rookSquare - 3));
	}

	//update allPieces and emptySquares
	allPieces = pieces[0] | pieces[1];
	emptySquares = ~allPieces;
}
//TODO for Justin, first thing sprint3
void Board::undoPromotionMove(Move move, int capturedPieceType){


	if(capturedPieceType == 0) allPieces &= ~(1 << move.toSquare);
	allPieces |= (1 << move.fromSquare);
	emptySquares &= ~(1 << move.fromSquare);
	if(capturedPieceType == 0) emptySquares |= (1 << move.toSquare);
	pieces[color] &= ~(1 << move.toSquare);
	pieces[color] |= (1 << move.fromSquare);
	pieceTypes[color][int(move.promotedPiece)] &= ~(1 << move.toSquare);
	pieceTypes[color][5] |= (1 << move.fromSquare);
}
