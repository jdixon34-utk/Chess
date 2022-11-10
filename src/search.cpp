#include <cstring>
#include "board.h"
#include "move.h"
#include "search.h"

int search(Board* position, int depth){
    if(depth == 4) return position->evaluatePosition();

    if(position->color == 0){
        int wcurrent;
        int max = -10000;
        int capturedPieceType;
        int numMovesWhite;
        Move whiteMoves[128];

        position->genMoves();
        memcpy(whiteMoves, position->moves, sizeof(Move) * 128);
        numMovesWhite = position->moveIndex;
        for(int i = 0; i < numMovesWhite; i++){
            //printf("Depth %d Trying White Move %d: ", depth, i);
            //whiteMoves[i].printMove();
            capturedPieceType = position->makeMove(whiteMoves[i]);
            if(!position->squareUnderAttack(position->getKingPosition())){
                position->color = 1;
                wcurrent = search(position, depth + 1);
                if(wcurrent > max){
                    max = wcurrent;
                    if(depth == 0) position->bestMove = whiteMoves[i];
                }
                position->color = 0;
            }
            position->undoMove(whiteMoves[i], capturedPieceType);
        }
        return max;
    }
    else{
        int bcurrent;
        int min = 10000;
        int capturedPieceType;
        int numMovesBlack;
        Move blackMoves[128];

        position->genMoves();
        memcpy(blackMoves, position->moves, sizeof(Move) * 128);
        numMovesBlack = position->moveIndex;
        for(int i = 0; i < numMovesBlack; i++){
            //printf("Depth %d Trying Black Move %d: ", depth, i);
            //blackMoves[i].printMove();
            capturedPieceType = position->makeMove(blackMoves[i]);
            if(!position->squareUnderAttack(position->getKingPosition())){
                position->color = 0;
                bcurrent = search(position, depth + 1);
                if(bcurrent < min){
                    min = bcurrent;
                    if(depth == 0) position->bestMove = blackMoves[i];
                }
                position->color = 1;
            }
            position->undoMove(blackMoves[i], capturedPieceType);
        }
        return min;
    }
}
