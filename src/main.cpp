#include "game.h"
#include "board.h"
#include "move.h"
using namespace std;

//global constants and lookup tables to be used to calculate possible moves
unsigned long long RANK_1 = 0x00000000000000FF;
unsigned long long RANK_2 = 0x000000000000FF00;
unsigned long long RANK_3 = 0x0000000000FF0000;
unsigned long long RANK_4 = 0x00000000FF000000;
unsigned long long RANK_5 = 0x000000FF00000000;
unsigned long long RANK_6 = 0x0000FF0000000000;
unsigned long long RANK_7 = 0x00FF000000000000;
unsigned long long RANK_8 = 0xFF00000000000000;
unsigned long long FILE_A = 0x0101010101010101;
unsigned long long FILE_B = 0x0202020202020202;
unsigned long long FILE_C = 0x0404040404040404;
unsigned long long FILE_D = 0x0808080808080808;
unsigned long long FILE_E = 0x1010101010101010;
unsigned long long FILE_F = 0x2020202020202020;
unsigned long long FILE_G = 0x4040404040404040;
unsigned long long FILE_H = 0x8080808080808080;
unsigned long long KING_LOOKUP_TBL[64] = {0};
unsigned long long KNIGHT_LOOKUP_TBL[64] = {0};
//all rays from one of 64 squares in one of 8 directions(N, NE, E, SE, etc.)
//used for sliding pieces only
unsigned long long RAYS[64][8];

void INITIALIZE_KING_LOOKUP_TBL();
void INITIALIZE_KNIGHT_LOOKUP_TBL();
void INITIALIZE_RAYS();

//all eval tables are in reverse order from what they look like
//element 1 is square A1, element 2 is square B2, etc.
//first table is white, second is black
int KING_EVAL_TBL[2][64] = {{    40,   50,   40,   20,   20,   40,   50,   40,
                                 30,   40,   30,   10,   10,   30,   40,   30,
						         10,    0,   -5,  -10,  -10,   -5,    0,   10,
						          0,  -10,  -20,  -40,  -40,  -20,  -10,  -10,
						        -60,  -60,  -60,  -60,  -60,  -60,  -60,  -60,
						       -200, -200, -200, -200, -200, -200, -200, -200,
						       -500, -500, -500, -500, -500, -500, -500, -500,
						       -999, -999, -999, -999, -999, -999, -999, -999},

						      {-999, -999, -999, -999, -999, -999, -999, -999,
						       -500, -500, -500, -500, -500, -500, -500, -500,
						       -200, -200, -200, -200, -200, -200, -200, -200,
						        -60,  -60,  -60,  -60,  -60,  -60,  -60,  -60,
						    	  0,  -10,  -20,  -40,  -40,  -20,  -10,  -10,
						         10,    0,   -5,  -10,  -10,   -5,    0,   10,
						         30,   40,   30,   10,   10,   30,   40,   30,
						         40,   50,   40,   20,   20,   40,   50,   40}};

int PAWN_EVAL_TBL[2][64] = {{     0,    0,    0,    0,    0,    0,    0,    0,
                                  0,    0,    0,    0,    0,    0,    0,    0,
						         20,   20,   30,   40,   40,   30,   20,   20,
						         50,   50,   50,   60,   60,   60,   30,   30,
						         80,   80,   80,   80,   80,   80,   40,   40,
						        100,  100,  100,  100,  100,  100,  100,  100,
						        300,  300,  300,  300,  300,  300,  300,  300,
						          0,    0,    0,    0,    0,    0,    0,    0},

						      {   0,    0,    0,    0,    0,    0,    0,    0,
						        300,  300,  300,  300,  300,  300,  300,  300,
						        100,  100,  100,  100,  100,  100,  100,  100,
						         80,   80,   80,   80,   80,   80,   40,   40,
						    	 50,   50,   50,   60,   60,   60,   30,   30,
						         20,   20,   30,   40,   40,   30,   20,   20,
						          0,    0,    0,    0,    0,    0,    0,    0,
						          0,    0,    0,    0,    0,    0,    0,    0}};

int KNIGHT_EVAL_TBL[2][64] = {{-300, -300, -200, -200, -200, -200, -300, -300,
                               -300, -200,    0,    0,    0,    0,    0,    0,
						       -100,  -50,    0,    0,    0,    0,  -50, -100,
						          0,   50,  100,  200,  200,  100,   50,    0,
						         50,  100,   80,  300,  300,   80,  100,   50,
						        200,  300,  400,  400,  400,  400,  300,  100,
						        300,  300,  300,  300,  300,  300,  300,  300,
						        100,  100,  100,  100,  100,  100,  100,  100},

						      { 100,  100,  100,  100,  100,  100,  100,  100,
						        300,  300,  300,  300,  300,  300,  300,  300,
						        200,  300,  400,  400,  400,  400,  300,  100,
						         50,  100,   80,  300,  300,   80,  100,   50,
						    	  0,   50,  100,  200,  200,  100,   50,    0,
						       -100,  -50,    0,    0,    0,    0,  -50, -100,
						       -300, -200,    0,    0,    0,    0,    0,    0,
						       -300, -300, -200, -200, -200, -200, -300, -300}};


//int W_KNIGHT_EVAL_TBL[64] = {};

//int W_PAWN_EVAL_TBL[64] = {};

int main(int argc, char** argv){
	if(argc != 2) {
		fprintf(stderr,"Please supply a FEN string inside quotation marks\n");
		exit(1);
	}

    INITIALIZE_KING_LOOKUP_TBL();
    INITIALIZE_KNIGHT_LOOKUP_TBL();
    INITIALIZE_RAYS();
	Game game;

    game.playTurn(argv[1]);
}

void INITIALIZE_KING_LOOKUP_TBL(){
	for(unsigned long long i=0; i<64; i++){
		//Kings move to the right
		if((i+1) % 8){
			KING_LOOKUP_TBL[i] |= 1ULL << (i+1);
			// Up to the Right
			if(i+1 < 57) KING_LOOKUP_TBL[i] |= 1ULL << (i+9);
			//Down to the Right
			if(i+1 > 7) KING_LOOKUP_TBL[i] |= 1ULL << (i-7);
		}

		//Kings move to the left
		if((i-1) % 8 != 7){
			KING_LOOKUP_TBL[i] |= 1ULL << (i-1);
			// Left-Up
			if(i-1 < 57) KING_LOOKUP_TBL[i] |= 1ULL << (i+7);
			// Left-Down
			if(i-1 > 7) KING_LOOKUP_TBL[i] |= 1ULL << (i-9);
		}

		//King moves up
		if(i < 56) KING_LOOKUP_TBL[i] |= 1ULL << (i+8);

		//King moves down
		if(i > 7) KING_LOOKUP_TBL[i] |= 1ULL << (i-8);
	}
}

void INITIALIZE_KNIGHT_LOOKUP_TBL(){
	unsigned long long tmpBitBoard;
	int rNew;
	int cNew;

	for(int c = 0; c < 8; c++){
		for(int r = 0; r < 8; r++){
			tmpBitBoard = 0;
			rNew = r + 1;
			cNew = c + 2;
			if (rNew < 8 && cNew < 8){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			rNew = r + 2;
			cNew = c + 1;
			if (rNew < 8 && cNew < 8){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			rNew = r + 2;
			cNew = c - 1;
			if (rNew < 8 && cNew >= 0){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			rNew = r + 1;
			cNew = c - 2;
			if (rNew < 8 && cNew >= 0){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			rNew = r - 1;
			cNew = c - 2;
			if (rNew >= 0 && cNew >= 0){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			rNew = r - 2;
			cNew = c - 1;
			if (rNew >= 0 && cNew >= 0){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			rNew = r - 2;
			cNew = c + 1;
			if (rNew >= 0 && cNew < 8){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			rNew = r - 1;
			cNew = c + 2;
			if (rNew >= 0 && cNew < 8){
				tmpBitBoard |= (1ULL << ((cNew * 8) + rNew));
			}
			KNIGHT_LOOKUP_TBL[(c * 8) + r] = tmpBitBoard;
		}
	}
}

void INITIALIZE_RAYS(){
	int pos;
	for (int i = 0; i < 64; i++) {
		//north
		pos = i;
		RAYS[i][0] = 0;
		while(pos+8 < 63){
			pos += 8;
			RAYS[i][0] |= (1ULL << pos);
		}
		//ne
		pos = i;
		RAYS[i][1] = 0;
		while((pos)%8 != 7 && pos+9 <= 63){
			pos += 9;
			RAYS[i][1] |= (1ULL << pos);
		}
		//e
		pos = i;
		RAYS[i][2] = 0;
		while((pos)%8 != 7){
			pos += 1;
			RAYS[i][2] |= (1ULL << pos);
		}
		//se
		pos = i;
		RAYS[i][3] = 0;
		while(pos-7 >= 0 && (pos-7)%8 != 0){
			pos -= 7;
			RAYS[i][3] |= (1ULL << pos);
		}
		//s
		pos = i;
		RAYS[i][4] = 0;
		while((pos-8) >= 0){
			pos -= 8;
			RAYS[i][4] |= (1ULL << pos);
		}
		//sw
		pos = i;
		while(pos-9 >= 0 && (pos-9)%8 != 7){
			pos -= 9;
			RAYS[i][5] |= (1ULL << pos);
		}
		//w
		pos = i;
		while(pos%8 != 0){
			pos -= 1;
			RAYS[i][6] |= (1ULL << pos);
		}
		//nw
		pos = i;
		while((pos+7)%8 != 7 && (pos+7) < 63){
			pos += 7;
			RAYS[i][7] |= (1ULL << pos);
		}
	}
}
