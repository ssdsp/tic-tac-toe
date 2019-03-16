/*
	Shawn Stovall
	Test Suite for AI Functions
	
	2018-05-24
*/

#ifdef TESTING

#include "ai.h"

int main() {	
	printf("Test Suite for the AI Functions\n");
	
	int board[3][3] = {{X, EMPTY, EMPTY},
					   {EMPTY, X, EMPTY},
					   {EMPTY, EMPTY, O}};
	
	spot_rank ai_board[3][3];
					   
	display_board(board);
	
	location loc = {1, 1};
	
	rank_spot(X, loc, board, ai_board);
	
	printf("\n\tai_board[%d][%d].possible_wins = %d", loc.row, loc.col, ai_board[loc.row][loc.col].possible_wins);
	printf("\n\tai_board[%d][%d].win_rank      = %d", loc.row, loc.col, ai_board[loc.row][loc.col].win_rank);
	printf("\n\tai_board[%d][%d].blocking      = %d", loc.row, loc.col, ai_board[loc.row][loc.col].blocking);
	printf("\n\tai_board[%d][%d].win           = %d\n\n", loc.row, loc.col, ai_board[loc.row][loc.col].win);
	
	rank_board(X, board, ai_board);
	place_spot(X, MEDIUM, board, ai_board);
	
	
	display_ai_board(ai_board);
	printf("\n\n");
	display_board(board);
	
	return 0;
}

#endif
