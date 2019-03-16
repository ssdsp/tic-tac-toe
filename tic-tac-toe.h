/*
	Shawn Stovall
	Tic-Tac-Toe header
	
	2018-05-19
*/

#ifndef TIC_TAC_TOE_H_
#define TIC_TAC_TOE_H_

#include "stdio.h"

// Representations

#define X           1
#define O          -1
#define EMPTY       0
#define NONE        0
#define DIMENSION   3
#define X_WIN       DIMENSION * X
#define O_WIN       DIMENSION * O
#define X_COMPARE   >=
#define O_COMPARE   <=

typedef int piece;

// Struct for holding the location a of spot on the board.
typedef struct location {
	int row;
	int col;
} location;

// Prototypes

void display_board(piece board[DIMENSION][DIMENSION]);
location select_location(piece board[DIMENSION][DIMENSION]);
void set_turn(piece xo, location loc, piece board[DIMENSION][DIMENSION]);
piece check_for_win(piece board[DIMENSION][DIMENSION]);
piece check_for_hwin(piece board[DIMENSION][DIMENSION]);
piece check_for_vwin(piece board[DIMENSION][DIMENSION]);
piece check_for_dwin(piece board[DIMENSION][DIMENSION]);
void populate_board(piece board[DIMENSION][DIMENSION]);
int is_board_full(piece board[DIMENSION][DIMENSION]);
int occupied(location loc, piece board[DIMENSION][DIMENSION]);
char convert_xo(piece xo);

#endif
