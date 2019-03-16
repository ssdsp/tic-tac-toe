/*
	Shawn Stovall
	AI Functions
	
	2018-05-19
*/

#include "ai.h"

// Rank each spot on the AI's internal game board.
void rank_board(piece xo, piece board[DIMENSION][DIMENSION], spot_rank ai_board[DIMENSION][DIMENSION]) {
	int row, col;
	
	for (row = 0; row < DIMENSION; row++)
		for (col = 0; col < DIMENSION; col++) {
			rank_spot(xo, (location) {row, col}, board, ai_board);
		}
}

// Rank a spot on the AI's interal game board.
void rank_spot(piece xo, location loc, piece board[DIMENSION][DIMENSION], spot_rank ai_board[DIMENSION][DIMENSION]) {
	if (board[loc.row][loc.col] != EMPTY)
		copy_spot_rank(&ai_board[loc.row][loc.col], (spot_rank) {0, 0, 0});
	else if (is_along_diag(loc))
		copy_spot_rank(&ai_board[loc.row][loc.col], add_rank(scan_vh(xo, loc, board), scan_diag(xo, loc, board)));
	else
		copy_spot_rank(&ai_board[loc.row][loc.col], scan_vh(xo, loc, board));
}

// Check if the spot is along a diagonal.
int is_along_diag(location loc) {
	if (loc.row == loc.col || (loc.row + loc.col) == (DIMENSION - 1))
		return 1;
	else
		return 0;
}

// Scan vertically and horizontally and return a rank based on result.
spot_rank scan_vh(piece xo, location loc, piece board[DIMENSION][DIMENSION]) {
	int h_total = 0;
	int v_total = 0;
	int row, col;
	piece opposite, current;
	int opp_in_row = 0;
	spot_rank rank = {0, 0, 0, 0};
	
	// Find the opposing player.
	if (xo == X)
		opposite = O;
	else
		opposite = X;
	
	// Check horizontally for possible win.
	for (col = 0; col < DIMENSION; col++) {
		h_total += board[loc.row][col];
		if (board[loc.row][col] == opposite)
			opp_in_row = 1;
	}
	
	// Check vertically for possible win.
	for (row = 0; row < DIMENSION; row++) {
		v_total += board[row][loc.col];
		if (board[row][loc.col] == opposite)
			opp_in_row = 1;
	}
	
	// Get the total possible wins at this position.
	if (xo == X) {
		if ((h_total X_COMPARE 0) && (v_total X_COMPARE 0))
			rank.possible_wins = 2;
		else if ((h_total X_COMPARE 0) || (v_total X_COMPARE 0))
			rank.possible_wins = 1;
	} else {
		if ((h_total O_COMPARE 0) && (v_total O_COMPARE 0))
			rank.possible_wins = 2;
		else if ((h_total O_COMPARE 0) || (v_total O_COMPARE 0))
			rank.possible_wins = 1;
	}
	
	// Set the set the line with the highest probability to win to current.
	if (xo == X)
		current = (v_total X_COMPARE h_total) ? v_total : h_total;
	else
		current = (v_total O_COMPARE h_total) ? v_total : h_total;

	// Sets the win rank as the sum of the vertical and horizontal totals.
	rank.win_rank = v_total + h_total;

	// If putting piece in the spot blocks the opponent, set the blocking flag.
	if (xo == X)
		rank.blocking = (((O_WIN - v_total) == O) || ((O_WIN - h_total) == O));
	else
		rank.blocking = (((X_WIN - v_total) == X) || ((X_WIN - h_total) == X));
	
	// Check to see if there is a win close at hand.
	if (xo == X)
		rank.win = (((X_WIN - v_total) == X) || ((X_WIN - h_total) == X));
	else
		rank.win = (((O_WIN - v_total) == O) || ((O_WIN - h_total) == O));
	
	return rank;
}

// Scans the diagonals of the board.
spot_rank scan_diag(piece xo, location loc, piece board[DIMENSION][DIMENSION]) {	
	if (loc.row == (DIMENSION / 2) && loc.col == (DIMENSION / 2))
		return add_rank(scan_ldiag(xo, board), scan_rdiag(xo, board));
	else if (loc.row == loc.col)
		return scan_ldiag(xo, board);
	else
		return scan_rdiag(xo, board);
}

// Scans the board's left diagonal line (Starting at (0, 0)).
spot_rank scan_ldiag(piece xo, piece board[DIMENSION][DIMENSION]) {
	int total = 0;
	int row, col;
	int opp_in_row;
	piece opposite = (xo == X) ? O : X;
	spot_rank rank;
	
	// Scan the left diagonal of the board.
	for (row = 0, col = 0; row < DIMENSION; row++, col++) {
		total += board[row][col];
		if (board[row][col] == opposite)
			opp_in_row = 1;
	}
	
	// Calculate possible wins.
	if (xo == X) {
		if (total X_COMPARE 0)
			rank.possible_wins = 1;
	} else {
		if (total O_COMPARE 0)
			rank.possible_wins = 1;
	}
	
	rank.win_rank = total;
	
	// Check for blocking opportunity.
	if (xo == X)
		rank.blocking = ((O_WIN - total) == O);
	else
		rank.blocking = ((X_WIN - total) == X);
	
	// Check for winning opportunity.
	if (xo == X)
		rank.win = ((X_WIN - total) == X);
	else
		rank.win = ((O_WIN - total) == O);
	
	return rank;
}

// Scans the board's right diagonal line (Starting at (0, DIMENSION - 1)).
spot_rank scan_rdiag(piece xo, piece board[DIMENSION][DIMENSION]) {
	int total = 0;
	int row, col;
	int opp_in_row;
	int opposite = (xo == X) ? O : X;
	spot_rank rank;
	
	// Scan the right diagonal of the board.
	for (row = 0, col = (DIMENSION - 1); row < DIMENSION; row++, col--) {
		total += board[row][col];
		if (board[row][col] == opposite)
			opp_in_row = 1;
	}
	
	// Calculate possible wins.
	if (xo == X) {
		if (total X_COMPARE 0)
			rank.possible_wins = 1;
	} else {
		if (total O_COMPARE 0)
			rank.possible_wins = 1;
	}
	
	rank.win_rank = total;
	
	// Check for blocking opportunity.
	if (xo == X)
		rank.blocking = ((O_WIN - total) == O);
	else
		rank.blocking = ((X_WIN - total) == X);
	
	// Check for winning opportunity.
	if (xo == X)
		rank.win = ((X_WIN - total) == X);
	else
		rank.win = ((O_WIN - total) == O);
	
	return rank;
}

// Adds ranks together.
spot_rank add_rank(spot_rank rank1, spot_rank rank2) {
	spot_rank result;
	
	result.possible_wins = rank1.possible_wins + rank2.possible_wins;
	result.win_rank = rank1.win_rank + rank2.win_rank;
	result.blocking = rank1.blocking || rank2.blocking;
	result.win = rank1.win || rank2.win;
	
	return result;
}

void place_spot(piece xo, dif difficulty, piece board[DIMENSION][DIMENSION]) {
	spot_rank ai_board[DIMENSION][DIMENSION];  // Create the board for spot processing.
	spot_rank highest = {0, 0, 0, 0};          // Create a holder spot rank struct for the highest ranked spot.
	int row, col;                              // Looping counters.
	int choice_row, choice_col;                // Ultimate choice for piece placement.
	int win_row, win_col;                      // If there is a win on the board, hold the spot in these.
	int block_row, block_col;                  // If there is a block on the board, hold the spot in these.
	int win_flag, block_flag;                  // Flag if there is a win or block on the board.
	
	// Set both win and block flags to 0 (False).
	win_flag = block_flag = 0;
	
	// Rank the game board and store it in the AI board.
	rank_board(xo, board, ai_board);
	
	
	for (row = 0; row < DIMENSION; row++) {
		for (col = 0; col < DIMENSION; col++) {
			// The following two if statements are executed on all difficulties.
			
			// If there is a win, flag it and catalog it.
			if (ai_board[row][col].win) {
				win_row = row;
				win_col = col;
				win_flag = 1;
			}
			
			// If there is a spot with more possible wins, that is the highest priority.
			if (ai_board[row][col].possible_wins > highest.possible_wins) {
				choice_row = row;
				choice_col = col;
				highest = ai_board[row][col];
			}
			
			// On MEDIUM difficulty and higher, block the player from winning.
			if (difficulty >= MEDIUM) {
				if (ai_board[row][col].blocking) {
					block_row = row;
					block_col = col;
					block_flag = 1;
				}
			}
			
			// On HARD difficulty, strategically pick the spot that will most likely lead to a win.
			if (difficulty == HARD) {
				if (xo == X) {
					if ((ai_board[row][col].possible_wins >= highest.possible_wins) && (ai_board[row][col].win_rank X_COMPARE highest.win_rank)) {
						choice_row = row;
						choice_col = col;
						highest = ai_board[row][col];
					}
				} else {
					if ((ai_board[row][col].possible_wins >= highest.possible_wins) && (ai_board[row][col].win_rank O_COMPARE highest.win_rank)) {
						choice_row = row;
						choice_col = col;
						highest = ai_board[row][col];
					}
				}
			}
		}
	}
	
	// If there is a win, that is the choice.
	// If there is no win, but a block, that is the choice.
	// Otherwise, use the highest ranking spot as the choice.
	if (win_flag) {
		choice_row = win_row;
		choice_col = win_col;
	} else if (block_flag) {
		choice_row = block_row;
		choice_col = block_col;
	}
	
	board[choice_row][choice_col] = xo;
}

// Function to perform a deep copy of a spot_rank struct.
void copy_spot_rank(spot_rank* dest, spot_rank source) {
	dest->possible_wins = source.possible_wins;
	dest->win_rank      = source.win_rank;
	dest->blocking      = source.blocking;
	dest->win           = source.win;
}

/* * * * * * * * * * * * * * * * * * * * * * * * *
 *               Testing Functions               *
 * * * * * * * * * * * * * * * * * * * * * * * * */
 
 void display_ai_board(spot_rank ai_board[DIMENSION][DIMENSION]) {
	// Declare counters
	int row;
	int col;
	int spacer;
	
	// Loop through board and display it.
	for (row = 0; row < DIMENSION; row++) {
		for (col = 0; col < DIMENSION; col++) {
			printf(" %d,%d ", ai_board[row][col].possible_wins, ai_board[row][col].win_rank);
			if (col != DIMENSION - 1)
				printf("\xBA");
			else
				printf("\n");
		}
		
		if (row != DIMENSION - 1) {
			for (spacer = 0; spacer < DIMENSION - 1; spacer++)
				printf("\xCD\xCD\xCD\xCD\xCD\xCE");
		
			printf("\xCD\xCD\xCD\xCD\xCD\n");
		}
	}
}
