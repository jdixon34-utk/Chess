#include <cstring>
#include <unistd.h>
#include "board.h"
#include "move.h"
#include "search.h"

int search(Board* position, int maxDepth, int depth, int alpha, int beta){
    if(depth == maxDepth){
        position->positionsEvaluated++;
        return position->evaluatePosition();
    }

    if(position->color == 0){
        int wcurrent;
        int max = -10010;
        int capturedPieceType;
        int numMovesWhite;
        Move whiteMoves[128];

        position->genMoves();
        memcpy(whiteMoves, position->moves, sizeof(Move) * 128);
        numMovesWhite = position->moveIndex;
        for(int i = 0; i < numMovesWhite; i++){
            capturedPieceType = position->makeMove(whiteMoves[i]);
            if(!position->inCheck()){
                position->color = 1;
                wcurrent = search(position, maxDepth, depth + 1, alpha, beta);
                position->color = 0;
                if(wcurrent > max){
                    max = wcurrent;
                    if(depth == 0) position->bestMove = whiteMoves[i];
                }
                if(max > alpha) alpha = max;
                if(beta <= alpha){
                    position->undoMove(whiteMoves[i], capturedPieceType);
                    break;
                }
            }
            position->undoMove(whiteMoves[i], capturedPieceType);
        }
        //if checkmate or stalemate
        if(max == -10010){
            if(position->inCheck()) return -10000 - (10 - depth); //more value for a faster checkmate
            else return 0;
        }
        return max;
    }
    else{
        int bcurrent;
        int min = 10010;
        int capturedPieceType;
        int numMovesBlack;
        Move blackMoves[128];

        position->genMoves();
        memcpy(blackMoves, position->moves, sizeof(Move) * 128);
        numMovesBlack = position->moveIndex;
        for(int i = 0; i < numMovesBlack; i++){
            capturedPieceType = position->makeMove(blackMoves[i]);
            if(!position->inCheck()){
                position->color = 0;
                bcurrent = search(position, maxDepth, depth + 1, alpha, beta);
                position->color = 1;
                if(bcurrent < min){
                    min = bcurrent;
                    if(depth == 0) position->bestMove = blackMoves[i];
                }
                if(min < beta) beta = min;
                if(beta <= alpha){
                    position->undoMove(blackMoves[i], capturedPieceType);
                    break;
                }
            }
            position->undoMove(blackMoves[i], capturedPieceType);
        }
        //if checkmate or stalemate
        if(min == 10010){
            if(position->inCheck()) return 10000 + (10 - depth); //more value for a faster checkmate
            else return 0;
        }
        return min;
    }
}
