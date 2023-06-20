#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

char board[10];
char field[3][3];

void singleplayer();
void multiplayer();
void computer();
bool checkFull();
bool checkWin(char);
char GetInput(bool x);

//clears the output screen
void clearConsole()
{
	system("cls");
}

//Function to reset the board for a new game.
void resetBoard()
{
	for (int i = 0; i < 10; i++)
	{
		board[i] = ' ';
		if (i >= 1)
		{
			field[((i - 1) / 3)][((i - 1) % 3)] = '0' + i;
		}
	}
	
}

//Function to diplay menu before game starts
void menu()
{
	//infinte loop so that it runs till correct input. return statement takes it out of the function.
	while (true)
	{
		resetBoard();
		char inputmenu;
		cout << "MENU\n\n1: Singleplayer\n2: Multiplayer\n3: Quit\n\n\nInput: ";
		cin >> inputmenu;
		if (inputmenu == '1')
			singleplayer();
		else if (inputmenu == '2')
			multiplayer();
		else if (inputmenu == '3' || inputmenu == 'q')
			return;
		else
		{
			clearConsole();
			cout << "\nInvalid Input!"<<endl;
		}
	}
}

//Function to print the board.
void drawBoard()
{
	clearConsole();
	cout << "\n\n\n"
		<< "     " << field[0][0] << " | " << field[0][1] << " | " << field[0][2] << endl
		<< "    ---|---|---" << endl
		<< "     " << field[1][0] << " | " << field[1][1] << " | " << field[1][2] << endl
		<< "    ---|---|---" << endl
		<< "     " << field[2][0] << " | " << field[2][1] << " | " << field[2][2] << endl;
}

//Function for player vs computer.
void singleplayer()
{
	clearConsole();
	char input = ' ';
	string name;
	cout << "Please enter your name\n\n\nInput: ";
	cin >> name;
	//infinite loop. runs till game finishes.
	while (true)
	{
		drawBoard();
		//function call to check if computer has won.
		if (checkWin('O'))
		{
			cout << "\nComputer has won\n\n";
			return;
		}
		//function call to check if game has ended in a tie.
		if (checkFull())
		{
			cout << "\nTie\n\n";
			return;
		}
		//Function call to take input from player
		input = GetInput(true);
		drawBoard();
		//If user inputs q then game is exited
		if (input == 'q')
		{
			return;
		}
		//function call to check if player has won. (Player cant win. Atmost tie can occur)
		if (checkWin('X'))
		{
			cout << endl << name << " has won\n\n";
			return;
		}
		//Function call for computer to make its move.
		computer();
	}
}

//Function for player vs player
void multiplayer()
{
	char input = ' ';
	bool player1Turn = true;
	string P1;
	string P2;
	cout << "Please enter name for Player 1\n\n\nInput: ";
	cin >> P1;
	cout << "Please enter name for Player 2\n\n\nInput: ";
	cin >> P2;
	//Infinte loop runs till game ends.
	while (true)
	{
		drawBoard();
		//function call to check if player1 has won.
		if (checkWin('X'))
		{
			cout << endl << P1 << " has won!\n\n";
			return;
		}
		//function call to check if player2 has won.
		else if (checkWin('O'))
		{
			cout << endl << P2 << " has won!\n\n";
			return;
		}
		//function call to check if game ended in tie.
		if (checkFull())
		{
			cout << "Tie\n\n";
			return;
		}
		//function call to get input from player. If value is true player1s turn else player2s turn
		input = GetInput(player1Turn);
		//Checks if user input q to quit the game.
		if (input == 'q')
		{
			return;
		}
		//Gives turn to other player when turn is over.
		player1Turn = !player1Turn;
	}
}

//Function to take input from user and store it in the 2D array
char GetInput(bool x)
{
	while (true)
	{
		cout << "\n\nInput: ";
		char input = ' ';
		cin >> input;
		//Changing data type from char to integer
		int inputNumber = input - '0';
		//checks if input is correct or if user pressed q to quit game.
		if (inputNumber > 9 || inputNumber < 1)
		{
			if (input == 'q')
				return input;
			else
				cout << "\nInvalid Input!"<<endl;
		}
		//checks if the user tried to input in a box already being used.
		else if (board[inputNumber] != ' ')
		{
			cout << "\nThis field is already used"<<endl;
		}
		//else input is correct
		else
		{
			//checks whose turn it is player 1 or 2.
			//stores values into 2D array.
			if (x)
			{
				board[inputNumber] = 'X';
				field[((inputNumber - 1) / 3)][((inputNumber - 1) % 3)] = 'X';
			}
			else
			{
				board[inputNumber] = 'O';
				field[((inputNumber - 1) / 3)][((inputNumber - 1) % 3)] = 'O';
			}
			return input;
		}
	}
}

//Function for computer to compute where to place 'O' in its turn.
void computer()
{
	//checks is there is an empty box on the board
	if (checkFull())
		return;
	srand(time(nullptr));
	//checks if placing O on any space will win the game for the computer. Aggressive move
	for (int i = 1; i < 10; i++)
	{
		if (board[i] == ' ')
		{
			board[i] = 'O';
			field[((i - 1) / 3)][((i - 1) % 3)] = 'O';
			if (checkWin('O'))
				return;
			else
			{
				board[i] = ' ';
				field[((i - 1) / 3)][((i - 1) % 3)] = ' ';
			}
		}
	}
	//checks if player X is winning and needs to be stopped at any box. Defencive move
	for (int i = 1; i < 10; i++)
	{
		if (board[i] == ' ')
		{
			board[i] = 'X';
			field[((i - 1) / 3)][((i - 1) % 3)] = 'X';
			if (checkWin('X'))
			{
				board[i] = 'O';
				field[((i - 1) / 3)][((i - 1) % 3)] = 'O';
				return;
			}
			else
			{
				board[i] = ' ';
				field[((i - 1) / 3)][((i - 1) % 3)] = ' ';
			}
		}
	}
	//Set to field in the middle with a chance when it is still free
	int middle = rand() % 4;
	if (board[5] == ' ' && middle != 1)
	{
		board[5] = 'O';
		field[1][1] = 'O';
		return;
	}
	//Select random field to vary cpu moves.
	while (true)
	{
		srand(time(nullptr));
		int i = rand() % 9 + 1;
		if (board[i] == ' ')
		{
			board[i] = 'O';
			field[((i - 1) / 3)][((i - 1) % 3)] = 'O';
			return;
		}
	}
}

//Function to check if any sequence is made on the board and if any of the players won the game
bool checkWin(char sign)
{
	if (field[0][0] == sign && field[0][1] == sign && field[0][2] == sign || field[0][0] == sign && field[1][0] == sign && field[2][0] == sign || field[0][0] == sign && field[1][1] == sign && field[2][2] == sign || field[0][1] == sign && field[1][1] == sign && field[2][1] == sign || field[0][2] == sign && field[1][2] == sign && field[2][2] == sign || field[0][2] == sign && field[1][1] == sign && field[2][0] == sign || field[1][0] == sign && field[1][1] == sign && field[1][2] == sign || field[2][0] == sign && field[2][1] == sign && field[2][2] == sign)
	{
		return true;
	}
	return false;
}

//To check if the board is full or it has any empty boxes left on it
bool checkFull()
{
	for (int i = 1; i <= 9; i++)
	{
		if (board[i] == ' ')
		{
			return false;
		}
	}
	return true;
}

int main()
{
	srand(time(nullptr));
	menu();
	return 0;
}