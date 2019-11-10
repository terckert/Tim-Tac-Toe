#include <iostream>


void displayBoard(char[]);
bool winCondition(char[], char);


int main()
{
	char playerCharacter[2] = { 'X','O' };	
	char again = 'Y', choice;

	int round = 0;
	//Round % 2 determines : Which players turn it is, which player character is being used

	do
	{
		char board[9] = { '1','2','3','4','5','6','7','8','9' };
		
		while (winCondition(board, playerCharacter[round % 2]) == false)
		{
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

				break;
			}
			round++; //updating round data

			//draw condition, it's been 9 rounds, must be scratch if not win, starting player swaps next round.
			if (round % 9 == 0)
			{
				displayBoard(board);
				std::cout << "\nIt's a draw!\n\n";
				break; //breaks out of while 
			}//end draw condition


		}//end game, can be either win or draw.


		std::cout << "Would you like to play again? (Y/N) ";
		std::cin >> again;

		while (std::cin.peek() != '\n' || !std::cin || (again != 'Y' && again != 'y' && again != 'N' && again != 'n'))
		{
			if (!std::cin)std::cin.clear();
			std::cin.ignore(200, '\n');

			std::cout << "Invalid option.  Would you like to play again? (Y/N) ";
			std::cin >> again;
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
