#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/*
 * define is User-defined functions.
*/
#define BOARD_SIZE 5
#define EMPTY_CELL 0
#define BLACK_STONE -1
#define WHITE_STONE 1
#define OUT_OF_CELL 9

// Global values
int board[BOARD_SIZE][BOARD_SIZE];		// -1, 0, 1
int stone;			// -1, 1
int player;			// 0, 1
int judge;
int turn;			// 0-8

// Function declaration
void initBoard();
void initStone();
void initPlayer();
void showBoard();
int inputRow();
int inputColumn();
void putableStone(int column, int row);
void checkWin();
void _checkWin(int flag, int count, int row, int column, int idx_r, int idx_c);
void changeStone();
void changePlayer();
void dispWinner();


int main() {
//	int row;
//	int column;
	initBoard();
	initPlayer();
	initStone();
	printf("Start Game!\n");
	while(9 > turn) {
		if(!judge) {
			printf("\n");
			printf("Turn : %d\n", turn);
			showBoard();
			printf("Player %d\n", player+1);
			//		row = inputRow();
			//		column = inputColumn();
			putableStone(inputRow(), inputColumn());
			checkWin();
			/*
			putableStone(row, column);
			_checkWin(1, 0, row, column, 0, 0);
			*/
			turn++;
		} else {
			break;
		}
	}
	dispWinner();
	return 0;
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

void putableStone(int row, int column) {
	char rowChar[] = {'a', 'b', 'c'};
	if(EMPTY_CELL == board[row][column]) {
		board[row][column] = stone;
	} else {
		printf("Not EMPTY_CELL this cell\nrow : %c, column : %d\n", rowChar[row-1], column);
		putableStone(inputRow(), inputColumn());
	}
	return;
}

void checkWin() {
	int check = 0;
	// check row
	for(int row=1; row<BOARD_SIZE-1; row++) {
		for(int column=1; column<BOARD_SIZE-1; column++) {
			if(stone != board[row][column]) {
				break;
			} else {
				check++;
			}
		}
		if(3 == check) {
			judge = 1;
			break;
		}
		check = 0;
	}
	// check column
	for(int row=1; row<BOARD_SIZE-1; row++) {
		for(int column=1; column<BOARD_SIZE-1; column++) {
			if(stone != board[row][column]) {
				break;
			} else {
				check++;
			}
		}
		if(3 == check) {
			judge = 1;
			break;
		}
		check = 0;
	}
	// check skew1
	for(int i=1; i<BOARD_SIZE-1; i++) {
		if(stone != board[i][i]) {
			break;
		} else {
			check++;
		}
	}
	if(3 == check) {
		judge = 1;
		return;
	}
	// check skew2
	for(int i=BOARD_SIZE-2; i>0; i--) {
		if(stone != board[i][i]) {
			break;
		} else {
			check++;
		}
	}
	if(3 == check) {
		judge = 1;
		return;
	}
	check = 0;
	changePlayer();
	changeStone();
}

void _checkWin(int flag, int count, int row, int column, int idx_r, int idx_c) {
	int dir_r[6] ={-1, -2, -1, -2, 0, 0};
	int dir_c[6] ={0, 0, 1, 2, 1, 2};
	if(3 != count) {
		if(stone == board[row+(dir_r[idx_r]*flag)][column+(dir_c[idx_c]*flag)]) {
			_checkWin(flag, ++count, row, column, ++idx_r, ++idx_c);
			return;
		} else if(OUT_OF_CELL == board[row+(dir_r[idx_r]*flag)][column+(dir_c[idx_c]*flag)]) {
			if(-1 != flag) {
				flag = -1;
				_checkWin(flag, count, row, column, idx_r, idx_c);
			} else {
				flag = 1;
				count = 0;
				_checkWin(flag, count, row, column, ++idx_r, ++idx_c);
			}
			return;
		}
	} else {
		judge = 1;
		return;
	}
	changePlayer();
	changeStone();
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
	showBoard();
	printf("The Winner is Player%d\n", player+1);
}
