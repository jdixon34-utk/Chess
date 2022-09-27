#ifndef MOVE_H
#define MOVE_H

class Move{
private:
    
    char fromSquare;
    char toSquare;
    char specialMove; //1 = en passant, 2 = castling, 3 = pawn promotion
    char promotedPiece; //1 = queen, 2 = rook, 3 = bishop, 4 = knight

public:
    void createMove(char fromSquare, char toSquare, char specialMove, char promotedPiece);
};

#endif