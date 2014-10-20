#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BOARD_SIZE 5
#define EMPTY_CELL 0
#define BLACK_STONE -1
#define WHITE_STONE 1
#define OUT_OF_CELL 9

int player;
int stone;
int board[BOARD_SIZE][BOARD_SIZE];
char row;
int temp_row;
int column;
int putable;

void initPlayer() {
	 player = 0;
}

void initStone() {
	 stone = BLACK_STONE;
}

void initBoard() {
	for(int i=0; i<BOARD_SIZE; i++) {
		for(int j=0; j<BOARD_SIZE; j++) {
			switch(i) {
				case 0:
				case 4:
					board[i][j] = OUT_OF_CELL;
					break;
				case 1:
				case 2:
				case 3:
					board[i][j] = EMPTY_CELL;
					break;
				default:
					break;
			}
		}
	}
}

void showBoard() {
	for(int i=1; i<4; i++) {
		printf("-------\n");
		for(int j=1; j<4; j++) {
			printf("|");
			switch(board[i][j]) {
			case EMPTY_CELL:
				printf(" ");
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

void putablestone() {
	if(EMPTY_CELL == board[temp_row][column]){
		putable = 0;
	}else{
		putable = 1;
	}
}

void inputRow() {
	printf("Please input row : ");
	fflush(stdin);
	scanf("%c", &row);
	switch(row){
		case'a':
			temp_row = 1;
			break;
		case'b':
			temp_row = 2;
			break;
		case'c':
			temp_row = 3;
			break;
		default:
			printf("Please retry¥n");
			inputRow();
			break;
	}
	return;
}

void inputColumn() {
	printf("Please input column : ");
	fflush(stdin);
	scanf("%d",&column);
	switch(column){
		case 1:
		case 2:
		case 3:
			break;
		default:
			printf("Pease retry¥n");
			inputColumn();
			break;
	}
	return;
} 

int checkWin(int flag, int check_row, int check_column, int index_dir_r, int index_dir_c) {
	int dir_r[4] = {-1, -1, 0, 1};
	int dir_c[4] = {0, 1, 1, 1};
	if(OUT_OF_CELL == board[temp_row + dir_r[index_dir_r * flag]][column + dir_c[index_dir_c * flag]]) {
	if(1 == flag) {
	} else if(-1 == flag) {
		return 1;
	}
	} else if(EMPTY_CELL == board[temp_row + dir_r[index_dir_r * flag]][column + dir_c[index_dir_c * flag]]) {
	} else if(stone != board[temp_row + dir_r[index_dir_r * flag]][column + dir_c[index_dir_c * flag]]) {
	} else if(stone == board[temp_row + dir_r[index_dir_r * flag]][column + dir_c[index_dir_c * flag]]) {
	}
	return 0;
}

void dispWinner() {
	printf("The winner is Player%d!!¥n", ++player);
}

void changeStone() {
	stone *= -1;
}

void changePlayer() {
	player ^= 1;
}
 		
int main(int argc, char **argv) {
	printf("Game Start!!¥n");
	initPlayer();
	initStone();
	initBoard();
	for(int turn=0; turn<(BOARD_SIZE-2)^2; turn++) {
		showBoard();
		inputRow();
		inputColumn();
		putablestone();
		if(0 == putable){
			board[temp_row][column] = stone;
			if(checkWin) {
				break;
			}
			changeStone();
			changePlayer();
		}
	}
	showBoard();
	dispWinner();
	return 0;
}
