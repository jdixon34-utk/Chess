#ifndef MOVE_H
#define MOVE_H

class Move{
private:
    
    char fromSquare;
    char toSquare;
    char specialMove; //0 = none, 1 = en passant, 2 = castling, 3 = pawn promotion
    char promotedPiece; //0 = none, 1 = queen, 2 = rook, 3 = bishop, 4 = knight

public:
    void createMove(char fromSquareArg, char toSquareArg, char specialMoveArg, char promotedPieceArg);
    void printMove();
};

#endif
