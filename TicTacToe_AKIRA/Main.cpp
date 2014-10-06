#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define EMPTY 0
#define BLACK -1
#define WHITE 1

int board[5][5];		// -1, 0, 1
int stone;			// -1, 1
int player;			// 0, 1
char row;			// a, b, c
int temp_row;			// 0, 1, 2
int column;			// 0, 1, 2

void initBoard();
void initStone();
void initPlayer();
void showBoard();
void input();
int putableStone();
int checkWin(int index_r,int index_c);
void changeStone();
void changePlayer();
void dispWinner();

int main() {
	initBoard();
	initStone();
	initPlayer();
	showBoard();
	input();
	while(-1 == checkWin(0, 0)) {
		showBoard();
		input();
	}
	dispWinner();
	return 0;
}

void initBoard() {
	for(int i=0; i<5; i++) {
		for(int j=0; j<5; j++) {
			board[i][j] = EMPTY;
		}
	}
}

void initStone() {
	stone = BLACK;
}

void initPlayer() {
	player = 0;
}

void showBoard() {
	for(int i=1; i<4; i++) {
		for(int j=1; j<4; j++) {
			switch(board[i][j]) {
			case EMPTY:
				printf("?");
				break;
			case BLACK:
				printf("O");
				break;
			case WHITE:
				printf("X");
				break;
			default:
				break;
			}
		}
		printf("\n");
	}
	printf("\n");
}

void input() {
	row = NULL;
	column = NULL;
	printf("Please input row : ");
	fflush(stdin);
	scanf("%c", &row);
	switch(row) {
		case 'a':
			temp_row = 1;
			break;
		case 'b':
			temp_row = 2;
			break;
		case 'c':
			temp_row = 3;
			break;
		default:
			printf("Wrong row.");
			printf("Prease retry.\n");
			input();
			break;
	}
	printf("Please input column : ");
	scanf("%d", &column);
	switch(column) {
		case 1:
		case 2:
		case 3:
			if(putableStone()) {
				board[temp_row][column] = stone;
				changeStone();
				changePlayer();
			} else {
				printf("Wrong column.");
				printf("Prease retry.\n");
				input();
			}
			break;
		default:
			printf("Wrong column.");
			printf("Prease retry.\n");
			input();
			break;
	}
}

int putableStone() {
	int result = -1;
	if(EMPTY == board[temp_row][column]) {
		int result = 1;
	}
	return result;
}

int checkWin(int index_r, int index_c) {
	int result = -1;
	int dir_r[8] ={0, -1, -1, -1, 0, 1, 1, 1};
	int dir_c[8] ={1, 1, 0, -1, -1, -1, 0, 1};
	if(stone == board[temp_row+dir_r[index_r]][column+dir_r[index_c]]) {
		if(2 == index_r) {
			result = 1;
		} else {
			if(7 > index_r) {
				checkWin(index_r+1, index_c+1);
			}
		}
	} else {
		checkWin(index_r+1, index_c+1);
	}
	return result;
}

void changeStone() {
	stone *= -1;
}

void changePlayer() {
	if(0 == player) {
		player = 1;
	} else if(1 == player) {
		player = 0;
	}
}

void dispWinner() {
	printf("The Winner is PLayer%d", player+1);
}
