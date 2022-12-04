#ifndef MOVE_H
#define MOVE_H

class Move{
public:
    
    char fromSquare;
    char toSquare;
    char specialMove; //0 = none, 1 = en passant, 2 = castling, 3 = pawn promotion
    char promotedPiece; //0 = none, 1 = queen, 2 = rook, 3 = bishop, 4 = knight
    int castleInfo[4];

    void createMove(char fromSquareArg, char toSquareArg, char specialMoveArg, char promotedPieceArg, int whiteCastleRightsKS, int whiteCastleRightsQS, int blackCastleRightsKS, int blackCastleRightsQS);
    void printMove();
};

#endif
