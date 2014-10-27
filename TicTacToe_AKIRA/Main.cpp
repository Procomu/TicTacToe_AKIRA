#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define _DEBUG

//	define user value.
#define BOARD_SIZE 10
#define EMPTY_CELL 0
#define BLACK_STONE -1
#define WHITE_STONE 1
#define OUT_OF_CELL 9

int player;	// 0, 1
int stone;	// -1, 1
int board[BOARD_SIZE][BOARD_SIZE];	// -1, 0, 1
char row;	// a, b, c ...
int temp_row;	// 0, 1, 2 ...
int column;	// 0, 1, 2 ...
int putable;	// 0, 1
int drow;	// 0, 1
int judge;	// 0, 1

/*
 * initialize player value
 */
void initPlayer() {
	 player = 0;
}

/*
 * initialize stone value
 */
void initStone() {
	 stone = BLACK_STONE;
}

/*
 * initialize board value
 */
void initBoard() {
	for(int i=0; i<BOARD_SIZE; i++) {
		for(int j=0; j<BOARD_SIZE; j++) {
			switch(i) {
				// 0 and BOARD_SIZE - 1 is Out of Board.
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

/*
 * show board
 */
void showBoard() {
	printf("\n");
#ifdef DEBUG
	for(int i=0; i<BOARD_SIZE; i++) {
		for(int j=0; j<BOARD_SIZE; j++) {
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
# else
	printf("   ");
	for(int i=1; i<BOARD_SIZE - 1; i++) {
		printf("%d ", i);
	}
	printf("\n");
	for(int i=1; i<BOARD_SIZE - 1; i++) {
		printf("  ");
		for(int i=1; i<BOARD_SIZE - 1; i++) {
			printf("--");
		}
		printf("-\n");
		int c = 'a';
		printf("%c ", i - 1 + c);
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
	printf("  ");
	for(int i=1; i<BOARD_SIZE - 1; i++) {
		printf("--");
	}
	printf("-\n");
#endif
}

void putablestone() {
	if(EMPTY_CELL == board[temp_row][column]){
		putable = 0;
	}else{
		printf("Please retry\n");
		putable = 1;
	}
}

void inputRow() {
	printf("Please input row (a, b, c ...) : ");
	fflush(stdin);
	scanf("%c", &row);
	int c = 'a';
	temp_row = (int)row - c + 1;
	if(temp_row<=0) {
		printf("Please retry\n");
		inputRow();
	} else if(BOARD_SIZE-1<=temp_row) {
		printf("Please retry\n");
		inputRow();
	}
	return;
}

void inputColumn() {
	printf("Please input column (1, 2, 3 ...) : ");
	fflush(stdin);
	scanf("%d", &column);
	if(column < 1 || (BOARD_SIZE - 2) < column) {
		printf("Please retry\n");
		inputColumn();
	}
	return;
}

void checkWin(int flag, int count, int check_row, int check_column, int index_dir) {
	if(index_dir < 4) {
		int dir_r[4] ={-1, -1, 0, 1};
		int dir_c[4] ={0, 1, 1, 1};
#ifdef DEBUG
		printf("<DEBUG> check row    : %d\n", check_row + (dir_r[index_dir] * flag));
		printf("<DEBUG> check column : %d\n", check_column + (dir_c[index_dir] * flag));
		printf("\n");
#endif
		if(OUT_OF_CELL == board[check_row + (dir_r[index_dir] * flag)][check_column + (dir_c[index_dir] * flag)]) {
			if(1 == flag) {
				flag = -1;
				checkWin(flag, count, temp_row, column, index_dir);
			} else if(-1 == flag) {
				if(BOARD_SIZE - 3 == count) {
					judge = 1;
				} else {
					flag = 1;
					count = 0;
					checkWin(flag, count, temp_row, column, ++index_dir);
				}
			}
		} else if(EMPTY_CELL == board[check_row + (dir_r[index_dir] * flag)][check_column + (dir_c[index_dir] * flag)]) {
			drow = 1;
			flag = 1;
			count = 0;
			checkWin(flag, count, temp_row, column, ++index_dir);
		} else if(stone != board[check_row + (dir_r[index_dir] * flag)][check_column + (dir_c[index_dir] * flag)]) {
			flag = 1;
			count = 0;
			checkWin(flag, count, temp_row, column, ++index_dir);
		} else if(stone == board[check_row + (dir_r[index_dir] * flag)][check_column + (dir_c[index_dir] * flag)]) {
			int next_row = check_row + (dir_r[index_dir] * flag);
			int next_column = check_column + (dir_c[index_dir] * flag);
			checkWin(flag, ++count, next_row, next_column, index_dir);
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
	drow = 1;
	printf("Game Start!!\n");
	initPlayer();
	initStone();
	initBoard();
	while(1 == drow) {
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
			drow = 0;
			checkWin(1, 0, temp_row, column, 0);
			if(judge) {
				showBoard();
				dispWinner();
				return 0;
			}
			changeStone();
			changePlayer();
		}
	}
	showBoard();
	printf("Drow...\n");
	return 0;
}
