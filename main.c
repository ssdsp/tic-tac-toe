/*
	Shawn Stovall
	Tic-Tac-Toe Game
	
	2018-05-15
*/

#include "ai.h"

int main() {
	int board[DIMENSION][DIMENSION];
	int whose_turn = X;  // Keep track of whose turn it is.
	int winner;          // Keep track of the status of a win on the board.
	int full;            // Flag for a full board.
	int ai_or_human;     // 1 to play against Human, 2 to play against AI.
	char again;          // Argument to store the result of the "Play again?" query.
	
	// Loop once, and then keep using while the user wants to play.
	do {
		// Populate the board with empties at the beginning of a cycle.
		populate_board(board);
		
		do {
			printf("Would you like to play against a (1) HUMAN or an (2) AI? ");
			scanf("%d", &ai_or_human);
			
			if (ai_or_human != 1 && ai_or_human != 2)
				printf("\nThat is an invalid choice.\n\n");
		} while (ai_or_human != 1 && ai_or_human != 2);
		
		printf("\n");
		
		if (ai_or_human == 1) {
			do {
				// Display board, ask for, and set, the input, and clear screen after each turn.
				display_board(board);
				printf("\n%c: ", convert_xo(whose_turn));
				set_turn(whose_turn, select_location(board), board);
				system("cls");
			
				// Alternate whose turn it is.
				if (whose_turn == O)
					whose_turn = X;
				else
					whose_turn = O;
			
				// Check for a winning pattern.
				winner = check_for_win(board);
				full = is_board_full(board);
			} while (!winner && !full);
		} else {
			// Choose the AI game piece.
			srand(time(NULL));
			piece ai_piece = (rand() % 2) ? X : O;
			int difficulty;
			
			// Have player choose difficulty.
			do {
				printf("Would you like to play at (1) EASY, (2) MEDIUM, or (3) HARD difficulty? ");
				scanf("%d", &difficulty);
				
				if (difficulty < 1 || difficulty > 3)
					printf("\nThat is an invalid choice.\n\n");
			} while (difficulty < 1 || difficulty > 3);
			
			difficulty -= 1;
			
			// X will always go first.
			printf("X always goes first.\n");
			
			printf("The AI is %c.\n\n", convert_xo(ai_piece));
			
			// AI game loop.
			do {
				// If AI gets the X piece, have it go first.
				// If the player gets the X piece, have them go first.
				if (ai_piece == X) {
					place_spot(X, difficulty, board);
					display_board(board);
					printf("\n");
					
					winner = check_for_win(board);
					full = is_board_full(board);
					
					if (winner || full) {
						system("cls");
						break;
					}
						
					set_turn(O, select_location(board), board);
					printf("\n");
				} else {
					display_board(board);
					printf("\n");
					
					set_turn(X, select_location(board), board);
					printf("\n");
					
					winner = check_for_win(board);
					full = is_board_full(board);
					
					if (winner || full) {
						system("cls");
						break;
					}
					
					place_spot(O, difficulty, board);
				}
				
				winner = check_for_win(board);
				full = is_board_full(board);
				
				system("cls");
			} while (!winner && !full);
		}
	
		// Display the final board, ask the user if they want to play again, and clear the screen.
		display_board(board);
		
		if (full && !winner)
			printf("\nThe game is tied!  You're both losers!\n");
		else
			printf("\n%c is the winner!\n", convert_xo(winner));
		
		
		printf("\nWould you like to play again? (Y to go again, anything else to quit) ");
		scanf("\n%c", &again);
		
		system("cls");
	} while (again == 'Y' || again == 'y');
	
	printf("\nHave a nice day!\n");
	
	return 0;
}
