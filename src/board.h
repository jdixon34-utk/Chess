#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>

class Board{
private:

    	//important info given from FEN string
	bool whiteTurn;
	bool whiteCastleRightsKS;
	bool whiteCastleRightsQS;
	bool blackCastleRightsKS;
	bool blackCastleRightsQS;
	char enPassantTargetSquare;//square that a pawn that has moved forward 2 spaces goes over
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
	
	std::vector<class Move> moves; //Move is a struct that will be defined somewhere else
					//it just holds the information of a move: "from" square, "to" square, and other small info

public:

	void genBoardFromFEN(std::string FEN);
	void printBitBoard(unsigned long long bitBoard);
	void printPosition();

	void genMoves();

	void genKingMoves();
	void genQueenMoves();
	void genRookMoves();
	void genBishopMoves();
	void genKnightMoves();
	void genPawnLeftMoves();
	void genPawnSinglePushMoves();
	void genPawnDoublePushMoves();
	void genPawnRightMoves();
	void genPawnLeftEnPassantMoves();
	void genPawnRightEnPassantMoves();
	void genCastleKS();
	void genCastleQS();
};

#endif
