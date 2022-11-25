// Gomoku.cpp : This file contains the 'main' function. Program execution begins and ends there.
// IHTFP.

#include <iostream>
#include <iomanip>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define capacity 50
#define maxSize 19

//Auxiliary
void nl(int j) {
    for (int i = 0; i < j; i++) {
        cout << endl;
    }
}
void sleeper(int delay) {
	for (int i = 0; i < delay * 100000; i++);
}

//win/draw conditions
bool horizontalCheck(char board[][maxSize], int size, int winCount, char playerSymbol[], int turn, int row, int col)
{
	int count = 0;

	if (col + winCount - 1 >= size) {
		return false;
	} else {
		for (int i = 0; i < winCount; i++) {
			if (board[row][col + i] == playerSymbol[turn])
				count++;
		}

		if (count == winCount) {
			return true;
		}

	}

	return false;
}
bool verticalCheck(char board[][maxSize], int size, int winCount, char PS[], int turn, int ri, int ci)
{
	int count = 0;
	if (ri + winCount - 1 >= size)
		return false;
	else
	{
		for (int i = 0; i < winCount; i++)
		{
			if (board[ri + i][ci] == PS[turn])
				count++;
		}
		if (count == winCount)
			return true;
		else
			return false;
	}
}
bool Diagonal1Check(char board[][maxSize], int size, int winCount, char playerSymbol[], int turn, int ri, int ci)
{
	int count = 0;
	if (ci - winCount + 1 >= size and ri + winCount - 1 >= size)
		return false;
	else
	{
		for (int i = 0; i < winCount; i++)
		{
			if (board[ri + i][ci - i] == playerSymbol[turn])
				count++;
		}
		if (count == winCount)
			return true;
	}
	return false;
}
bool Diagonal2Check(char board[][maxSize], int size, int winCount, char playerSymbol[], int turn, int ri, int ci)
{
	int count = 0;
	if (ci + winCount - 1 >= size or ri + winCount - 1 >= size)
		return false;
	else
	{
		for (int i = 0; i < winCount; i++)
		{
			if (board[ri + i][ci + i] == playerSymbol[turn])
				count++;
		}
		if (count == winCount)
			return true;

	}
	return false;
}
bool isWin(char B[][maxSize], int dim, int WC, char PS[], int turn)
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{		
			if (Diagonal1Check(B, dim, WC, PS, turn, ri, ci) or
				Diagonal2Check(B, dim, WC, PS, turn, ri, ci) or
				horizontalCheck(B, dim, WC, PS, turn, ri, ci) or
				verticalCheck(B, dim, WC, PS, turn, ri, ci)) {
				return true;
			}
		}
	}
	return false;
}
bool drawCheck(char board[][maxSize], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board[i][j] == '-')
				return false;
		}
	}
	return true;
}

//game logic
void initSP(char board[][maxSize], int& size, int& winCount, char playerSymbol[capacity], char pName[capacity]) {
	cout << "Board size: "; cin >> size;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = '-';
		}
	}

	cout << "Player name: ";
	cin >> pName;
	cout << "Player symbol: ";
	cin >> playerSymbol[0];
	playerSymbol[1] = 'X';

	cout << "Series required to win: "; cin >> winCount;
}
void initMP(char board[][maxSize], int & size, int & NoP, int & winCount, char playerSymbol[], char pName[][capacity], int & turn) {
    cout << "Board size: "; cin >> size;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = '-';
		}
	}

	cout << "Number of players: "; cin >> NoP;

	for (int i = 0; i <= NoP - 1; i++) {
		cout << "Player "<< i+1 <<  " name: ";
		cin >> pName[i];
		cout << "Player " << i+1 << " symbol: ";
		cin >> playerSymbol[i];
	}

	cout << "Series required to win: "; cin >> winCount;

	turn = rand()%NoP;
}
void printBoard(char board[][maxSize], int size) {
	system("cls");
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j]<<" ";
		}
		nl(2);
	}
}
void displayPlayerMessage(char name[]) {
	cout << name << "'s turn."; nl(1);
}
void inputCoordinate(int& row, int& col) {
	cout << "Row: "; cin >> row;
	cout << "Col: "; cin >> col;
	row--, col--;
}
bool isValidMove(char board[][maxSize], int size, int row, int col) {
	return (row >= 0 and row < size and col >= 0 and col < size and (board[row][col] == '-'));
}
void changeBoard(char board[][maxSize], int row, int col, char sym) {
	board[row][col] = sym;
}
void TurnChange(int& turn, int NoP) {
	turn++;
	if (turn == NoP) {
		turn = 0;
	}
}

void multiPlayer() {
	char board[maxSize][maxSize];
	char pName[capacity][capacity];
	char pSym[capacity];
	int turn = 0, size, NoP = 0, winCount;
	initMP(board, size, NoP, winCount, pSym, pName, turn);
	bool gameEnded = false;
	bool draw = false;
	do {
		printBoard(board, size);
		int row = 0, col = 0;
		displayPlayerMessage(pName[turn]);
		do {
			inputCoordinate(row, col);
			if (!isValidMove(board, size, row, col)) {
				cout<<"Can't move there.";nl(1);
			}
		} while (!isValidMove(board, size, row, col));
		changeBoard(board, row, col, pSym[turn]);

		if(drawCheck(board, size)) {
			gameEnded = true;
			draw = true;
			cout << "Draw."; nl(2);
		}
		else if (isWin(board, size, winCount, pSym, turn)) {
			system("cls");
			printBoard(board, size);
			gameEnded = true;
		}

		if (!gameEnded) {
			TurnChange(turn, NoP);
		}

	} while (!gameEnded);

	if (gameEnded and !draw) {
		cout << pName[turn] << " won!"; nl(2);
	}

}

void computerMove(char board[][maxSize], int size, int& row, int& col, int winCount, char playerSymbol[]) {
	
	//if winning, win
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			if (board[r][c] == '-') {
				board[r][c] = playerSymbol[1];
				if (isWin(board, size, winCount, playerSymbol, 1)) {
					row = r; col = c;
					return;
				}
				else {
					board[r][c] = '-';
				}
			}
		}
	}

	//if opponent winning, stop him
	for (int r = 0; r < size; r++) {
		for (int c = 0; c < size; c++) {
			if (board[r][c] == '-') {
				board[r][c] = playerSymbol[0];
				if (isWin(board, size, winCount, playerSymbol, 0)) {
					row = r; col = c;
					return;
				}
				else {
					board[r][c] = '-';
				}
			}
		}
	}

	// else randomly pick
	do
	{
		row = rand() % size;
		col = rand() % size;
	} while (!isValidMove(board, size, row, col));
}
void singlePlayer() {
	char board[maxSize][maxSize];
	char pName[capacity];
	char pSym[capacity];
	int turn, size, NoP = 2, winCount;
	turn = rand() % 2;
	initSP(board, size, winCount, pSym, pName);
	bool gameEnded = false;
	bool draw = false;
	do {
		printBoard(board, size);
		int row = 0, col = 0;
		
		if (turn == 0) {
			displayPlayerMessage(pName);
			do {
				inputCoordinate(row, col);
				if (!isValidMove(board, size, row, col)) {
					cout << "Can't move there."; nl(1);
				}
			} while (!isValidMove(board, size, row, col));
		}
		else {
			cout << "Computer's turn."; nl(1);
			sleeper(100000);
			computerMove(board, size, row, col, winCount, pSym);
		}
		
		changeBoard(board, row, col, pSym[turn]);

		if(drawCheck(board, size)) {
			gameEnded = true;
			draw = true;
			cout << "Draw."; nl(2);
		} else if (isWin(board, size, winCount, pSym, turn)) {
			system("cls");
			printBoard(board, size);
			gameEnded = true;
		}
		if (!gameEnded) {
			TurnChange(turn, NoP);
		}
	} while (!gameEnded);

	if (gameEnded and !draw) {
		if (turn == 0) {
			cout << pName << " won!"; nl(2);
		}
		else {
			cout << "Computer won!"; nl(2);
		}
	}
}

int main()
{
	srand(time(0));
	int mode = 0;
	cout << "Singleplayer(1) or Multiplayer(2): ";
	bool done = false;
	while (!done) {
		cin >> mode;
		switch (mode) {
		case 1:
			singlePlayer();
			done = true;
			break;
		case 2:
			multiPlayer();
			done = true;
			break;
		default:
			cout << "invalid input, try again: ";
			break;
		}
	}

    return 0;
}
