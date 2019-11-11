#include <iostream>
#include <algorithm>
#include <time.h>

struct move {
	int move;
}patton;


void displayBoard(char[]);
bool winCondition(char[], char);
bool movesLeft(char[]);
int evaluate(char[], char, char);
int minimax(char[], int, bool, char, char);
void findBestMove(char[], char, char);


int main()
{
	srand(time(NULL));

	char playerCharacter[2] = { 'X','O' };
	char again = 'Y', choice;
	int round = 0;
	//Round % 2 determines : Which players turn it is, which player character is being used
	bool won = false;
	

	do
	{
		char board[9] = { '1','2','3','4','5','6','7','8','9' };
		won = false;
		
		while (won == false)
		{
			std::cout << "\nWelcome to Tim-Tac-Toe!\n\nOne player or two? (1/2) ";
			std::cin >> choice;

			while ((choice != '1' && choice != '2') || std::cin.peek() != '\n') {
				if (std::cin.peek() != '\n')
					std::cin.ignore(200, '\n');

				std::cout << "Invalid option. One player or two? (1/2) ";
				std::cin >> choice;

			}//end input validation statement

			if (choice == '1') {

				
				round = 0;

				std::wcout << "Would you like to go first or second? (1/2) ";
				std::cin >> choice;

				while ((choice != '1' && choice != '2') || std::cin.peek() != '\n') {
					if (std::cin.peek() != '\n')
						std::cin.ignore(200, '\n');

					std::cout << "Invalid option. First or second? (1/2) ";
					std::cin >> choice;

				}//end input validation statement

				//start 1 player vs AI, player moves first
				if (choice == '1') {

					char pl = 'X', ai = 'O';
				
					do {

						displayBoard(board);

						std::cout << "Player, where would you like to move? ";
						std::cin >> choice;

						//input validation loop
						while (std::cin.peek() != '\n' || choice == 'X' || choice == 'x' || choice == 'O' || choice == 'o' ||
							(choice != board[0] && choice != board[1] && choice != board[2] && choice != board[3] && choice != board[4] &&
								choice != board[5] && choice != board[6] && choice != board[7] && choice != board[8]))
						{
							if (std::cin.peek() != '\n')
								std::cin.ignore(200, '\n');

							std::cout << "That is not a valid option. Player " << (round % 2) + 1 << " please make your selection: ";
							std::cin >> choice;
						}//end input validation loop
						
						for (int i = 0; i < 9; i++)
						{
							if (choice == board[i])board[i] = pl;

						}//end board update loop


						if (winCondition(board, pl) == true)
						{
							displayBoard(board);
							std::cout << "\n\nCongratulations Player! You win!\n\n";
							round = 0; //resets rounds
							won = true;

							break;
						}
						round++; //updating round data
						
						//draw condition, it's been 9 rounds, must be scratch if not win
						if (round % 9 == 0)
						{
							displayBoard(board);
							std::cout << "\nIt's a draw!\n\n";
							won = true;
							break; //breaks out of while 
						}//end draw condition
						

						//first ai turn, random move to help offset pattern loss
						if (round == 1) {
							bool madeMove = false;
							
							while (madeMove == false) {

								int k = (rand() % 10) + 48; //will give ASCI value of 1-9 character
								for (int i = 0; i < 9; i++) {
									if (board[i] == k) {
										board[i] = ai;
										madeMove = true;
									}
								}
							}
						}
						//ai moves for any other round
						else {							
							findBestMove(board, pl, ai);

							board[patton.move] = ai;
						}
						if (winCondition(board, ai) == true)
						{
							displayBoard(board);
							std::cout << "\n\nAI Wins!  Better luck next time...\n\n";
							won = true;
							break;
						}
						round++;//updating round data after ai move

					} while (!won); //end 1 player game, player first

				}
			
				else {
					char pl = 'O', ai = 'X';
					do {
						//first ai turn, random move to help offset pattern loss
						if (round == 0) {
							bool madeMove = false;

							while (madeMove == false) {

								int k = (rand() % 10) + 48; //will give ASCI value of 1-9 character
								for (int i = 0; i < 9; i++) {
									if (board[i] == k) {
										board[i] = ai;
										madeMove = true;
									}
								}
							}
						}

						//subsequent AI rounds
						else {
							findBestMove(board, pl, ai);
							board[patton.move] = ai;
						}

						//check for AI win
						if (winCondition(board, ai) == true)
						{
							displayBoard(board);
							std::cout << "\n\nAI Wins!  Better luck next time...\n\n";
							round = 0; //resets rounds
							won = true;

							break;
						}
						round++; //updating round data

						//draw condition, it's been 9 rounds, must be scratch if not win
						if (round % 9 == 0)
						{
							displayBoard(board);
							std::cout << "\nIt's a draw!\n\n";
							won = true;
							break; //breaks out of while 
						}//end draw condition

						displayBoard(board);

						std::cout << "Player, where would you like to move? ";
						std::cin >> choice;

						//input validation loop
						while (std::cin.peek() != '\n' || choice == 'X' || choice == 'x' || choice == 'O' || choice == 'o' ||
							(choice != board[0] && choice != board[1] && choice != board[2] && choice != board[3] && choice != board[4] &&
								choice != board[5] && choice != board[6] && choice != board[7] && choice != board[8]))
						{
							if (std::cin.peek() != '\n')
								std::cin.ignore(200, '\n');

							std::cout << "That is not a valid option. Player " << (round % 2) + 1 << " please make your selection: ";
							std::cin >> choice;
						}//end input validation loop

						for (int i = 0; i < 9; i++)
						{
							if (choice == board[i])board[i] = pl;

						}//end board update loop


						if (winCondition(board, pl) == true)
						{
							displayBoard(board);
							std::cout << "\n\nCongratulations Player! You win!\n\n";
							round = 0; //resets rounds
							won = true;

							break;
						}
						round++; //updating round data


					} while (!won);
				}
			}


			if (choice == '2') {

				won = false;
				round = 0;

				do {

					displayBoard(board);

					std::cout << "\nPlayer " << (round % 2) + 1 << " please make your selection: ";
					std::cin >> choice;

					//input validation loop
					while (std::cin.peek() != '\n' || choice == 'X' || choice == 'x' || choice == 'O' || choice == 'o' ||
						(choice != board[0] && choice != board[1] && choice != board[2] && choice != board[3] && choice != board[4] &&
							choice != board[5] && choice != board[6] && choice != board[7] && choice != board[8]))
					{
						std::cin.ignore(200, '\n');

						std::cout << "That is not a valid option. Player " << (round % 2) + 1 << " please make your selection: ";
						std::cin >> choice;
					}//end input validation loop

					//board update loop
					for (int i = 0; i < 9; i++)
					{
						if (choice == board[i])board[i] = playerCharacter[round % 2];

					}//end board update loop

					if (winCondition(board, playerCharacter[round % 2]) == true)
					{
						displayBoard(board);

						std::cout << "\n\nCongratulations Player " << (round % 2) + 1 << "! You win!\n\n";
						round = 0; //resets rounds, player 1 starts first if new game is selected.
						won = true;

						break;
					}
					round++; //updating round data

					//draw condition, it's been 9 rounds, must be scratch if not win
					if (round % 9 == 0)
					{
						displayBoard(board);
						std::cout << "\nIt's a draw!\n\n";
						won = true;
						break; //breaks out of while 
					}//end draw condition

				} while (!won);

			}//end 2 player game, can be either win or draw.

			
			std::cout << "Would you like to play again? (Y/N) ";
			std::cin >> again;

			while (std::cin.peek() != '\n' || !std::cin || (again != 'Y' && again != 'y' && again != 'N' && again != 'n'))
			{
				if (!std::cin)std::cin.clear();
				std::cin.ignore(200, '\n');

				std::cout << "Invalid option.  Would you like to play again? (Y/N) ";
				std::cin >> again;
			}
		}

	}//end do statement
	while (again == 'Y' || again == 'y');

	std::cout << "\n\nThanks for playing!\n\n";
	return 0;
}


//displays the TTT board
void displayBoard(char x[])
{
	system("CLS");	//clears the screen, I just think it looks nicer.

	std::cout << "\nTim-Tac-Toe!\n\n";

	std::cout << "   |   |   " << std::endl;
	std::cout << " " << x[0] << " | " << x[1] << " | " << x[2] << " " << std::endl;
	std::cout << "   |   |   " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "   |   |   " << std::endl;
	std::cout << " " << x[3] << " | " << x[4] << " | " << x[5] << " " << std::endl;
	std::cout << "   |   |   " << std::endl;
	std::cout << "-----------" << std::endl;
	std::cout << "   |   |   " << std::endl;
	std::cout << " " << x[6] << " | " << x[7] << " | " << x[8] << " " << std::endl;
	std::cout << "   |   |   " << std::endl;
}

//checks for win
// x is board value
// y is player character
bool winCondition(char x[], char y)
{
	if (
		(x[0] == y && x[1] == y && x[2] == y) ||
		(x[3] == y && x[4] == y && x[5] == y) ||
		(x[6] == y && x[7] == y && x[8] == y) ||
		(x[0] == y && x[3] == y && x[6] == y) ||
		(x[1] == y && x[4] == y && x[7] == y) ||
		(x[2] == y && x[5] == y && x[8] == y) ||
		(x[0] == y && x[4] == y && x[8] == y) ||
		(x[2] == y && x[4] == y && x[6] == y)
		)return true;
	return false;
}

//checks to see if moves are left
bool movesLeft(char x[]) {
	
	//if any space returns anything other than x or o then there are moves left
	for (int i = 0; i < 9; i++) {
		if (x[i] < 58)
			return true;
	}

	return false;
}

//evaluates board conditions, returns 10 if player wins, -10 if AI wins, 0 if nobody wins
int evaluate(char x[], char pl, char ai) {
	if (
		(x[0] == pl && x[1] == pl && x[2] == pl) ||
		(x[3] == pl && x[4] == pl && x[5] == pl) ||
		(x[6] == pl && x[7] == pl && x[8] == pl) ||
		(x[0] == pl && x[3] == pl && x[6] == pl) ||
		(x[1] == pl && x[4] == pl && x[7] == pl) ||
		(x[2] == pl && x[5] == pl && x[8] == pl) ||
		(x[0] == pl && x[4] == pl && x[8] == pl) ||
		(x[2] == pl && x[4] == pl && x[6] == pl)
		)return 10;

	if (
		(x[0] == ai && x[1] == ai && x[2] == ai) ||
		(x[3] == ai && x[4] == ai && x[5] == ai) ||
		(x[6] == ai && x[7] == ai && x[8] == ai) ||
		(x[0] == ai && x[3] == ai && x[6] == ai) ||
		(x[1] == ai && x[4] == ai && x[7] == ai) ||
		(x[2] == ai && x[5] == ai && x[8] == ai) ||
		(x[0] == ai && x[4] == ai && x[8] == ai) ||
		(x[2] == ai && x[4] == ai && x[6] == ai)
		)return -10;

	
}

//minimax - bool isMax is used to determine whose turn it is
int minimax(char x[], int depth, bool isMax, char pl, char ai) {
	int score = evaluate(x, pl, ai);
	int temp2;
	char temp;

	//if maximizer has won return 10
	if (score == 10)
		return 10;

	//if minimizer has won, return -10
	if (score == -10)
		return -10;

	//if the game ends in a tie, return 0
	if (movesLeft(x) == false)
		return 0;
	
	//If this is the maximizers turn
	if (isMax) {
		
		int best = -1000;
		
		
		//check the cells for empty spots
		for (int i = 0; i < 9; i++) {

			//find an empty spot
			if (x[i] < 58) {
				
				//make the spot the player
				x[i] = pl;

				//call the win condition to see if it's a player win if they take the spot
				best = std::max(best, minimax(x, depth + 1, !isMax, pl, ai));

				//return the cell to it's previous state
				temp2 = 49 + i;
				temp = temp2;
				x[i] = temp;
			}
		}

		return best;

	}

	//if this is the minimizers turn
	else {
		
		int best = 1000;

		//check for empty cells
		for (int i = 0; i < 9; i++) {

			if (x[i] < 58) {

				//change the cell to ai character and evaluate the board condition
				x[i] = ai;
								
				//call the win condition and evaluate
				best = std::min(best, minimax(x, depth + 1, isMax, pl, ai));

				//return the cell to it's previous state
				
				temp2 = 49+i;
				temp = temp2;
				x[i] = temp;
			}

		}

		return best;

	}

	
}

//minimax script for finding the best move
void findBestMove(char x[], char pl, char ai) {

	int bestVal = -1000;
	int bestMove = -1;
	char temp;
	int temp2;
	

	//check for empty cell
	for (int i = 0; i < 9; i++) {

		//check for empty cells
		if (x[i] < 58) {
			

			//create the move
			x[i] = pl;

			//check the move
			int moveVal = minimax(x, 0, false, pl, ai);
			
			temp2 = 49 + i;
			temp = temp2;
			x[i] = temp;
			
			if (moveVal > bestVal) {

				patton.move = i;
				bestVal = moveVal;

			}


		}
		
	}

}