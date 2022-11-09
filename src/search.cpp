#include "board.h"
#include "search.h"

int search(Board* position, int depth){
    if(depth == 2) return position->evaluatePosition();

    if(position->color == 0){
        int current;
        int max = -10000;
        int capturedPieceType;

        position->genMoves();
        for(int i = 0; i < position->moveIndex; i++){
            capturedPieceType = position->makeMove(position->moves[i]);
            if(!position->squareUnderAttack(position->getKingPosition())){
                position->color = 1;
                current = search(position, depth++);
                if(current > max){
                    max = current;
                    if(depth == 0) position->bestMove = position->moves[i];
                }
            }
            position->undoMove(position->moves[i], capturedPieceType);
        }
        return max;
    }
    else{
        int current;
        int min = 10000;
        int capturedPieceType;

        position->genMoves();
        for(int i = 0; i < position->moveIndex; i++){
            capturedPieceType = position->makeMove(position->moves[i]);
            if(!position->squareUnderAttack(position->getKingPosition())){
                position->color = 0;
                current = search(position, depth++);
                if(current < min){
                    min = current;
                    if(depth == 0) position->bestMove = position->moves[i];
                }
            }
            position->undoMove(position->moves[i], capturedPieceType);
        }
        return min;
    }
}
