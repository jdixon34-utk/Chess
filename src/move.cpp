#include <iostream>
#include <string>
#include "move.h"
using namespace std;

void Move::createMove(char fromSquareArg, char toSquareArg, char specialMoveArg, char promotedPieceArg){
    fromSquare = fromSquareArg;
    toSquare = toSquareArg;
    specialMove = specialMoveArg;
    promotedPiece = promotedPieceArg;
}

void Move::printMove(){
    char from[3], to[3];
    string sm, pp;

    from[0] = (fromSquare % 8) + 65;
    from[1] = (fromSquare / 8) + 49;
    from[2] = 0;

    to[0] = (toSquare % 8) + 65;
    to[1] = (toSquare / 8) + 49;
    to[2] = 0;

    switch(specialMove){
			case 0: sm = "None"; break;
			case 1: sm = "En Passant"; break;
			case 2: sm = "Castling"; break;
			case 3: sm = "Pawn Promotion"; break;
    }

    switch(promotedPiece){
			case 0: pp = "None"; break;
			case 1: pp = "Queen"; break;
			case 2: pp = "Rook"; break;
			case 3: pp = "Bishop"; break;
            case 4: pp = "Knight"; break;
    }

    if(sm == "Castling"){
        if(to[0] == 'G'){
            printf("POSSIBLE MOVE O-O.   Special Move: %-14s   Promoted Piece: %s\n", sm.c_str(), pp.c_str());
        }
        else{
            printf("POSSIBLE MOVE O-O-O.   Special Move: %-14s   Promoted Piece: %s\n", sm.c_str(), pp.c_str());
        }
    }
    else{
        printf("POSSIBLE MOVE from %s to %s.   Special Move: %-14s   Promoted Piece: %s\n", from, to, sm.c_str(), pp.c_str());
    }
}
