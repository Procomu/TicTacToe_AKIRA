#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define _DEBUG

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
int judge;

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
				case BOARD_SIZE - 1:
					board[i][j] = OUT_OF_CELL;
					break;
				default:
					board[i][j] = EMPTY_CELL;
					if(0 == j || j == BOARD_SIZE - 1) {
						board[i][j] = OUT_OF_CELL;
					}
					break;
			}
		}
	}
}

void showBoard() {
#ifdef DEBUG
	for(int i=0; i<BOARD_SIZE; i++) {
		for(int j=0; j<BOARD_SIZE; j++) {
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
# else
	for(int i=1; i<BOARD_SIZE - 1; i++) {
		printf("-------\n");
		for(int j=1; j<BOARD_SIZE - 1; j++) {
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
#endif
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
	temp_row = (int)row - 96;
	if(temp_row<=0) {
		if(BOARD_SIZE-1<=temp_row) {
			printf("Please retry\n");
			inputRow();
		}
	}
	return;
}

void inputColumn() {
	printf("Please input column : ");
	fflush(stdin);
	scanf("%d", &column);
	if(column < 1 || (BOARD_SIZE - 2) < column) {
		printf("Please retry\n");
		inputColumn();
	}
	return;
}

void checkWin(int flag, int check_row, int check_column, int index_dir) {
	if(index_dir < 4) {
		int dir_r[4] ={-1, -1, 0, 1};
		int dir_c[4] ={0, 1, 1, 1};
#ifdef DEBUG
		printf("<DEBUG> check   row  : %d\n", temp_row + (dir_r[index_dir] * flag));
		printf("<DEBUG> check column : %d\n", column + (dir_c[index_dir] * flag));
		printf("\n");
#endif
		if(OUT_OF_CELL == board[temp_row + (dir_r[index_dir] * flag)][column + (dir_c[index_dir] * flag)]) {
			if(1 == flag) {
				flag = -1;
				checkWin(flag, temp_row, column, index_dir);
			} else if(-1 == flag) {
				judge = 1;
			}
		} else if(EMPTY_CELL == board[temp_row + (dir_r[index_dir] * flag)][column + (dir_c[index_dir] * flag)]) {
			flag = 1;
			checkWin(flag, temp_row, column, ++index_dir);
		} else if(stone != board[temp_row + (dir_r[index_dir] * flag)][column + (dir_c[index_dir] * flag)]) {
			flag = 1;
			checkWin(flag, temp_row, column, ++index_dir);
		} else if(stone == board[temp_row + (dir_r[index_dir] * flag)][column + (dir_c[index_dir] * flag)]) {
			checkWin(flag, check_row, check_column, index_dir);
		}
	}
	return;
}

void dispWinner() {
	printf("The winner is Player%d!!\n", ++player);
}

void changeStone() {
	stone *= -1;
}

void changePlayer() {
	player ^= 1;
}
 		
int main(int argc, char **argv) {
	printf("Game Start!!\n");
	initPlayer();
	initStone();
	initBoard();
	for(int turn=0; turn<(int)pow(BOARD_SIZE-2, 2.0); turn++) {
		showBoard();
#ifdef DEBUG
		printf("Turn : %d\n", turn);
#endif
		printf("Player %d\n", player + 1);
		inputRow();
		inputColumn();
		putablestone();
		if(0 == putable){
			board[temp_row][column] = stone;
			checkWin(1, temp_row, column, 0);
			if(!judge) {
				showBoard();
				dispWinner();
				return 0;
			}
			changeStone();
			changePlayer();
		}
	}
	printf("Drow...\n");
	return 0;
}
