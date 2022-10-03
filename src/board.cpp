#include <vector>
#include <string>
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
    while(indexFEN < FEN.length()){
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
