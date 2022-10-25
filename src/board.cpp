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

	if(whiteTurn){
		/*
		instead of looping through the whole bitboard to find bits set to 1,
		we can keep finding the lsb set to 1, do what we need to do with it,
		set it to 0, and repeat until the bitboard == 0
		*/
		moveIndex = 0; //set/reset the index of the moves array

		tmpBitBoard = whiteKing;
		while(whiteKing){
			square = getLSBIndex(whiteKing);
			genKingMoves(square);
			whiteKing &= whiteKing - 1;
		}
		whiteKing = tmpBitBoard;

		tmpBitBoard = whiteQueen;
		while(whiteQueen){
			square = getLSBIndex(whiteQueen);
			genQueenMoves(square);
			whiteQueen &= whiteQueen - 1;
		}
		whiteQueen = tmpBitBoard;

		tmpBitBoard = whiteRooks;
		while(whiteRooks){
			square = getLSBIndex(whiteRooks);
			genRookMoves(square);
			whiteRooks &= whiteRooks - 1;
		}
		whiteRooks = tmpBitBoard;

		tmpBitBoard = whiteBishops;
		while(whiteBishops){
			square = getLSBIndex(whiteBishops);
			genBishopMoves(square);
			whiteBishops &= whiteBishops - 1;
		}
		whiteBishops = tmpBitBoard;

		tmpBitBoard = whiteKnights;
		while(whiteKnights){
			square = getLSBIndex(whiteKnights);
			genKnightMoves(square);
			whiteKnights &= whiteKnights - 1;
		}
		whiteKnights = tmpBitBoard;


		genPawnLeftMoves();
		genPawnSinglePushMoves();
		genPawnDoublePushMoves();
		genPawnRightMoves();
		if(enPassantTargetSquare != 0) genEnPassantMoves();
		if(whiteCastleRightsKS) genCastleKS();
		if(whiteCastleRightsQS) genCastleQS();
	}
	else{
		tmpBitBoard = blackKing;
		while(blackKing){
			square = getLSBIndex(blackKing);
			genKingMoves(square);
			blackKing &= blackKing - 1;
		}
		blackKing = tmpBitBoard;

		tmpBitBoard = blackQueen;
		while(blackQueen){
			square = getLSBIndex(blackQueen);
			genQueenMoves(square);
			blackQueen &= blackQueen - 1;
		}
		blackQueen = tmpBitBoard;

		tmpBitBoard = blackRooks;
		while(blackRooks){
			square = getLSBIndex(blackRooks);
			genRookMoves(square);
			blackRooks &= blackRooks - 1;
		}
		blackRooks = tmpBitBoard;

		tmpBitBoard = blackBishops;
		while(blackBishops){
			square = getLSBIndex(blackBishops);
			genBishopMoves(square);
			blackBishops &= blackBishops - 1;
		}
		blackBishops = tmpBitBoard;

		tmpBitBoard = blackKnights;
		while(blackKnights){
			square = getLSBIndex(blackKnights);
			genKnightMoves(square);
			blackKnights &= blackKnights - 1;
		}
		blackKnights = tmpBitBoard;

		genPawnLeftMoves();
		genPawnSinglePushMoves();
		genPawnDoublePushMoves();
		genPawnRightMoves();
		if(enPassantTargetSquare != 0) genEnPassantMoves();
		if(blackCastleRightsKS) genCastleKS();
		if(blackCastleRightsQS) genCastleQS();
	}
}

void Board::genKingMoves(int square){
	unsigned long long king_moves;
	int new_square;
	Move move;

	if(whiteTurn){
		king_moves = KING_LOOKUP_TBL[square] ^ (whitePieces & KING_LOOKUP_TBL[square]);
 	}else{
		king_moves = KING_LOOKUP_TBL[square] ^ (blackPieces& KING_LOOKUP_TBL[square]);
	}

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
	if(whiteTurn){
		// North
		rm |= RAYS[square][0] ^ (whitePieces & RAYS[square][0]);
		if(RAYS[square][0] & allPieces){
			block = getLSBIndex(RAYS[square][0] & allPieces);
			rm &= ~RAYS[block][0];
		}
		// East
		rm |= RAYS[square][2] ^ (whitePieces & RAYS[square][2]);
		if(RAYS[square][2] & allPieces){
			block = getLSBIndex(RAYS[square][2] & allPieces);
			rm &= ~RAYS[block][2];
		}
		// South
		rm |= RAYS[square][4] ^ (whitePieces & RAYS[square][4]);
		if(RAYS[square][4] & allPieces){
			block = getMSBIndex(RAYS[square][4] & allPieces);
			rm &= ~RAYS[block][4];
		}
		// West
		rm |= RAYS[square][6] ^ (whitePieces & RAYS[square][6]);
		if(RAYS[square][6] & allPieces){
			block = getMSBIndex(RAYS[square][6] & allPieces);
			rm &= ~RAYS[block][6];
		}
	}else{ // Black's Turn
		// North
		rm |= RAYS[square][0] ^ (blackPieces & RAYS[square][0]);
		if(RAYS[square][0] & allPieces){
			block = getLSBIndex(RAYS[square][0] & allPieces);
			rm &= ~RAYS[block][0];
		}
		// East
		rm |= RAYS[square][2] ^ (blackPieces & RAYS[square][2]);
		if(RAYS[square][2] & allPieces){
			block = getLSBIndex(RAYS[square][2] & allPieces);
			rm &= ~RAYS[block][2];
		}
		// South
		rm |= RAYS[square][4] ^ (blackPieces & RAYS[square][4]);
		if(RAYS[square][4] & allPieces){
			block = getMSBIndex(RAYS[square][4] & allPieces);
			rm &= ~RAYS[block][4];
		}
		// West
		rm |= RAYS[square][6] ^ (blackPieces & RAYS[square][6]);
		if(RAYS[square][6] & allPieces){
			block = getMSBIndex(RAYS[square][6] & allPieces);
			rm &= ~RAYS[block][6];
		}
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
	if(whiteTurn){
		//ne
		bishop_moves |= RAYS[square][1] ^ (whitePieces & RAYS[square][1]);
		if(RAYS[square][1] & allPieces){
			new_square = getLSBIndex(RAYS[square][1]&allPieces);
			bishop_moves &= ~RAYS[new_square][1];
		}
		//se
		bishop_moves |= RAYS[square][3] ^ (whitePieces & RAYS[square][3]);
		if(RAYS[square][3] & allPieces){
			new_square = getMSBIndex(RAYS[square][3]&allPieces);
			bishop_moves &= ~RAYS[new_square][3];
		}
		//sw
		bishop_moves |= RAYS[square][5] ^ (whitePieces & RAYS[square][5]);
		if(RAYS[square][5] & allPieces){
			new_square = getMSBIndex(RAYS[square][5]&allPieces);
			bishop_moves &= ~RAYS[new_square][5];
		}
		//nw
		bishop_moves |= RAYS[square][7] ^ (whitePieces & RAYS[square][7]);
		if(RAYS[square][7] & allPieces){
			new_square = getLSBIndex(RAYS[square][7] & allPieces);
			bishop_moves &= ~RAYS[new_square][7];
		}
	}else{
		//ne
		bishop_moves |= (RAYS[square][1] ^ (blackPieces & RAYS[square][1]));
		if(RAYS[square][1] & allPieces){
			new_square = getLSBIndex(RAYS[square][1]&allPieces);
			bishop_moves &= ~RAYS[new_square][1];
		}
		//se
		bishop_moves |= (RAYS[square][3] ^ (blackPieces & RAYS[square][3]));
		if(RAYS[square][3] & allPieces){
			new_square = getMSBIndex(RAYS[square][3]&allPieces);
			bishop_moves &= ~RAYS[new_square][3];
		}
		//sw
		bishop_moves |= (RAYS[square][5] ^ (blackPieces & RAYS[square][5]));
		if(RAYS[square][5] & allPieces){
			new_square = getMSBIndex(RAYS[square][5]&allPieces);
			bishop_moves &= ~RAYS[new_square][5];
		}
		//nw
		bishop_moves |= (RAYS[square][7] ^ (blackPieces & RAYS[square][7]));
		if(RAYS[square][7] & allPieces){
			new_square = getLSBIndex(RAYS[square][7]&allPieces);
			bishop_moves &= ~RAYS[new_square][7];
		}
	}
	while(bishop_moves != 0){
        new_square = getLSBIndex(bishop_moves);
        bishop_moves &= bishop_moves - 1;
    	move.createMove(square, new_square, 0, 0);
		moves[moveIndex++] = move;
    }
}

void Board::genKnightMoves(int square){
    unsigned long long knight_moves = 0;
	int new_square;
	Move move;

    if(whiteTurn){
        knight_moves = KNIGHT_LOOKUP_TBL[square] ^ (whitePieces & KNIGHT_LOOKUP_TBL[square]);
    }else{ // Black's Turn
        knight_moves = KNIGHT_LOOKUP_TBL[square] ^ (blackPieces & KNIGHT_LOOKUP_TBL[square]);
    }

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

    if(whiteTurn){
        pawn_left_moves = ((whitePawns << 7ULL) & ~FILE_H) & blackPieces;

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
        pawn_left_moves = ((blackPawns >> 7ULL) & ~FILE_A) & whitePieces;

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

    if(whiteTurn){
        pawn_sp_moves = (whitePawns << 8ULL) & ~allPieces;

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
        pawn_sp_moves = (blackPawns >> 8ULL) & ~allPieces;

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

    if(whiteTurn){
        pawn_dp_moves = ((whitePawns << 16ULL) & (((~allPieces & RANK_3) << 8ULL) & (~allPieces & RANK_4)));
		while(pawn_dp_moves != 0){
			new_square = getLSBIndex(pawn_dp_moves);
			square = new_square - 16;
			pawn_dp_moves &= pawn_dp_moves - 1;
			move.createMove(square, new_square, 0, 0);
			moves[moveIndex++] = move;
		}
    }else{ // Black's Turn
        pawn_dp_moves = ((blackPawns >> 16ULL) & (((~allPieces & RANK_6) >> 8ULL) & (~allPieces & RANK_5)));
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

    if(whiteTurn){
        pawn_right_moves = ((whitePawns << 9ULL) & ~FILE_A) & blackPieces;

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
        pawn_right_moves = ((blackPawns >> 9ULL) & ~FILE_H) & whitePieces;

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

    if(whiteTurn){
        enpass_moves = ((whitePawns << 7ULL) & ~FILE_H) & (1ULL << enPassantTargetSquare);

		while(enpass_moves != 0){
			new_square = getLSBIndex(enpass_moves);
			square = new_square - 7;
			enpass_moves &= enpass_moves - 1;
			move.createMove(square, new_square, 1, 0);
			moves[moveIndex++] = move;
		}

		enpass_moves = ((whitePawns << 9ULL) & ~FILE_A) & (1ULL << enPassantTargetSquare);

		while(enpass_moves != 0){
			new_square = getLSBIndex(enpass_moves);
			square = new_square - 9;
			enpass_moves &= enpass_moves - 1;
			move.createMove(square, new_square, 1, 0);
			moves[moveIndex++] = move;
		}
    }else{ // Black's Turn
        enpass_moves = ((blackPawns >> 7ULL) & ~FILE_A) & (1ULL << enPassantTargetSquare);

		while(enpass_moves != 0){
			new_square = getLSBIndex(enpass_moves);
			square = new_square + 7;
			enpass_moves &= enpass_moves - 1;
			move.createMove(square, new_square, 1, 0);
			moves[moveIndex++] = move;
		}

		enpass_moves = ((blackPawns >> 9ULL) & ~FILE_H) & (1ULL << enPassantTargetSquare);

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

	if(whiteTurn){
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

	if(whiteTurn){
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

int Board::inCheck(){
	int square;
	unsigned long long tmpBitBoard;
	if(!color){
	//Knight
		square = getLSBIndex(whiteKing);
		if(KNIGHT_LOOKUP_TBL[square] & blackKnights != 0) return 1;
	//Bishop/Queen
	//ne
	tmpBitBoard |= RAYS[square][1] ^ (whitePieces & RAYS[square][1]);
	if(RAYS[square][1] & allPieces){
		new_square = getLSBIndex(RAYS[square][1]&allPieces);
		tmpBitBoard &= ~RAYS[new_square][1];
	}
	//se
	tmpBitBoard |= RAYS[square][3] ^ (whitePieces & RAYS[square][3]);
	if(RAYS[square][3] & allPieces){
		new_square = getMSBIndex(RAYS[square][3]&allPieces);
		tmpBitBoard &= ~RAYS[new_square][3];
	}
	//sw
	tmpBitBoard |= RAYS[square][5] ^ (whitePieces & RAYS[square][5]);
	if(RAYS[square][5] & allPieces){
		new_square = getMSBIndex(RAYS[square][5]&allPieces);
		tmpBitBoard &= ~RAYS[new_square][5];
	}
	//nw
	tmpBitBoard |= RAYS[square][7] ^ (whitePieces & RAYS[square][7]);
	if(RAYS[square][7] & allPieces){
		new_square = getLSBIndex(RAYS[square][7] & allPieces);
		tmpBitBoard &= ~RAYS[new_square][7];
	}
	if(tmpBitBoard & blackBishops != 0 || tmpBitBoard & blackQueen != 0) return 1;
	//Rook/Queen

	//King

	//Pawn (will change slightly for black)
		if(blackPawns & (1 << (square+9)) != 0 || blackPawns & (1 << (square+7))) return 1;
	}
}
