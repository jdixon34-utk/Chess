#ifndef BOARD_H
#define BOARD_H
#include <string>
#include "move.h"

//global constants and lookup tables to be used to calculate possible moves
extern unsigned long long RANK_1;
extern unsigned long long RANK_2;
extern unsigned long long RANK_3;
extern unsigned long long RANK_4;
extern unsigned long long RANK_5;
extern unsigned long long RANK_6;
extern unsigned long long RANK_7;
extern unsigned long long RANK_8;
extern unsigned long long FILE_A;
extern unsigned long long FILE_B;
extern unsigned long long FILE_C;
extern unsigned long long FILE_D;
extern unsigned long long FILE_E;
extern unsigned long long FILE_F;
extern unsigned long long FILE_G;
extern unsigned long long FILE_H;
extern unsigned long long KING_LOOKUP_TBL[64];
extern unsigned long long KNIGHT_LOOKUP_TBL[64];
//all rays from one of 64 squares in one of 8 directions(N, NE, E, SE, etc.)
//used for sliding pieces only
extern unsigned long long RAYS[64][8];

extern void INITIALIZE_KING_LOOKUP_TBL();
extern void INITIALIZE_KNIGHT_LOOKUP_TBL();
extern void INITIALIZE_RAYS();


class Board{
private:

    	//important info given from FEN string
	bool whiteTurn;
	bool whiteCastleRightsKS;
	bool whiteCastleRightsQS;
	bool blackCastleRightsKS;
	bool blackCastleRightsQS;
	int enPassantTargetSquare;//square that a pawn that has moved forward 2 spaces goes over
	int halfMoveClock;//The number of halfmoves since the last capture or pawn advance, used for the fifty-move rule
    int fullMoveNumber;//The number of the full moves. It starts at 1 and is incremented after Black's move

	unsigned long long allPieces;

	unsigned long long whitePieces;
	unsigned long long whiteKing;
	unsigned long long whiteQueen;
	unsigned long long whiteRooks;
	unsigned long long whiteBishops;
	unsigned long long whiteKnights;
	unsigned long long whitePawns;

	unsigned long long blackPieces;
	unsigned long long blackKing;
	unsigned long long blackQueen;
	unsigned long long blackRooks;
	unsigned long long blackBishops;
	unsigned long long blackKnights;
	unsigned long long blackPawns;

	//Move is a struct that will be defined somewhere else
	//it just holds the information of a move: "from" square, "to" square, and other small info
	class Move moves[128];
	int moveIndex;
public:

	void genBoardFromFEN(std::string FEN);
	void printBitBoard(unsigned long long bitBoard);
	void printPosition();

	void printMoves();

	int getLSBIndex(unsigned long long bitBoard);
	int getMSBIndex(unsigned long long);

	void genMoves();
	void genKingMoves(int square);
	void genQueenMoves(int square);
	void genRookMoves(int square);
	void genBishopMoves(int square);
	void genKnightMoves(int square);
	void genPawnLeftMoves();
	void genPawnSinglePushMoves();
	void genPawnDoublePushMoves();
	void genPawnRightMoves();
	unsigned long long genPromoMoves(unsigned long long input_bb, unsigned long long rank_mask, int offset);
	void genEnPassantMoves();
	void genCastleKS();
	void genCastleQS();

	int inCheck();
};

#endif
