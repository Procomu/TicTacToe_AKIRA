#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
 * define is User-defined functions.
*/
#define EMPTY 0
#define BLACK_STONE -1
#define WHITE_STONE 1
#define OUT_OF_CELL 9

// Global values
int board[5][5];		// -1, 0, 1
int stone;			// -1, 1
int player;			// 0, 1
int judge;

// Function declaration
void initBoard();
void initStone();
void initPlayer();
void showBoard();
int inputRow();
int inputColumn();
void putableStone(int column, int row);
int checkWin();
void changeStone();
void changePlayer();
void dispWinner();

int main() {
	initBoard();
	initPlayer();
	initStone();
	printf("Start Game!\n\n");
	while(!judge) {
		showBoard();
		printf("Player %d\n", player+1);
		putableStone(inputColumn(), inputRow());
		changePlayer();
		changeStone();
	}
	return 0;
}

void initBoard() {
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			switch(i) {
				case 0:
				case 4:
					board[i][j] = OUT_OF_CELL;
					break;
				case 1:
				case 2:
				case 3:
					board[i][j] = EMPTY;
					break;
				default:
					break;
			}
		}
	}
}

void initStone() {
	stone = BLACK_STONE;
}

void initPlayer() {
	player = 0;
}

void showBoard() {
	for(int i=1; i<4; i++) {
		printf("-------\n");
		for(int j=1; j<4; j++) {
			printf("|");
			switch(board[i][j]) {
			case EMPTY:
				printf("?");
				break;
			case BLACK_STONE:
				printf("O");
				break;
			case WHITE_STONE:
				printf("X");
				break;
			default:
				break;
			}
		}
		printf("|\n");
	}
	printf("-------\n");
}

int inputRow() {
	int result = -1;
	char row;
	printf("Please input row(a, b, c) : ");
	fflush(stdin);
	scanf("%c", &row);
	switch(row) {
		case 'a':
			result = 1;
			return result;
			break;
		case 'b':
			result = 2;
			return result;
			break;
		case 'c':
			result = 3;
			return result;
			break;
		default:
			printf("Please retry.\n");
			inputRow();
			break;
	}
}

int inputColumn() {
	int result = -1;
	int column;
	printf("Please input column(1, 2, 3) : ");
	fflush(stdin);
	scanf("%d", &column);
	switch(column) {
	case 1:
	case 2:
	case 3:
		result = column;
		return result;
		break;
	default:
		printf("Please retry.\n");
		inputColumn();
		break;
	}
}

void putableStone(int column, int row) {
	char rowChar[] = {'a', 'b', 'c'};
	if(EMPTY == board[row][column]) {
		board[row][column] = stone;
	} else {
		printf("Not empty this cell\nrow : %c, column : %d\n", rowChar[row-1], column);
		putableStone(inputColumn(), inputRow());
	}
	return;
}

void checkWin() {
}

void changeStone() {
	stone *= -1;
}

void changePlayer() {
	/* 
	 * '^' is XOR mark.
	 * 0 ^ 0 = 0
	 * 0 ^ 1 = 1
	 * 1 ^ 0 = 1
	 * 1 ^ 1 = 0
	*/
	player ^= 1;
}

void dispWinner() {
	printf("The Winner is PLayer%d", player+1);
}
