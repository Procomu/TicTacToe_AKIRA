#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#define _DEBUG

// defineを使って変数のように数字を定義します。
#define BOARD_SIZE 10
#define EMPTY_CELL 0
#define BLACK_STONE -1
#define WHITE_STONE 1
#define OUT_OF_CELL 9

int player;	// 0, 1
int stone;	// Xは-1, Oは1
int board[BOARD_SIZE][BOARD_SIZE];	// 空かXかO
char row;	// a, b, c ...
int temp_row;	// 0, 1, 2 ...
int column;	// 0, 1, 2 ...
int putable;	// 0, 1
int drow;	// 0だと続行,1だとドローゲーム
int judge;	// 0だと勝者なし, 1だと勝者あり

/*
 * 変数playerを初期化する。
 */
void initPlayer() {
	 player = 0;
}

/*
 * 変数stoneを初期化する。
 */
void initStone() {
	 stone = BLACK_STONE;
}

/*
 * 配列boardを初期化する。
 */
void initBoard() {
	for(int i=0; i<BOARD_SIZE; i++) {
		for(int j=0; j<BOARD_SIZE; j++) {
			switch(i) {
				// 変数iが'0'もしくは'BOARD_SIZE-1'のときはボードの端っこなので、番兵を配置。
				case 0:
				case BOARD_SIZE - 1:
					board[i][j] = OUT_OF_CELL;
					break;
				default:
					// 空白を配置。
					board[i][j] = EMPTY_CELL;
					// 変数jが'0'もしくは'BOARD_SIZE-1'のときはボードの端っこなので、空白から番兵に置き換え。
					if(0 == j || j == BOARD_SIZE - 1) {
						board[i][j] = OUT_OF_CELL;
					}
					break;
			}
		}
	}
}

/*
 * 盤面を表示
 */
void showBoard() {
	printf("\n");
// defineでDEBUGを宣言してやると、以下の#ifdef内が実行される。
#ifdef DEBUG
// 盤面をきれいに整形せず、生のデータで表示する。
	for(int i=0; i<BOARD_SIZE; i++) {
		for(int j=0; j<BOARD_SIZE; j++) {
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
# else
// 盤面をきれいに整形して表示する。
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
			// 空だったら空白を表示。
			case EMPTY_CELL:
				printf(" ");
				break;
			// -1だったらXを表示。
			case BLACK_STONE:
				printf("X");
				break;
			// 1だったらOを表示。
			case WHITE_STONE:
				printf("O");
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

/*
 * 指定したセルに石を置けるかを判断する。
 */
void putablestone() {
	// セルに石が置けたら変数putableを0に、置けなければ1にする。
	if(EMPTY_CELL == board[temp_row][column]){
		putable = 0;
	}else{
		printf("Please retry\n");
		putable = 1;
	}
}

/*
 * row(行)の入力を処理する。
 */
void inputRow() {
	printf("Please input row (a, b, c ...) : ");
	fflush(stdin);
	scanf("%c", &row);
	// 'a'という文字を数字(文字コード)に直す。
	int c = 'a';
	// 入力された文字-('a'の文字コード+1)の結果をセルの番地とする。
	temp_row = (int)row - c + 1;
	// 変換後の値が0より小さい場合、ボードのサイズより大きい場合は再度入力へ。
	if(temp_row < 1　|| (BOARD_SIZE - 2) < temp_row) {
		printf("Please retry\n");
		inputRow();
	}
	return;
}

/*
 * column(列)の入力を処理する。
 */
void inputColumn() {
	printf("Please input column (1, 2, 3 ...) : ");
	fflush(stdin);
	scanf("%d", &column);
	// 入力された値が1より小さい場合、もしくはボードのサイズより大きい場合は再度入力へ。
	if(column < 1 || (BOARD_SIZE - 2) < column) {
		printf("Please retry\n");
		inputColumn();
	}
	return;
}

/*
 * 勝者が居るかどうかを判断する。
 */
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
		// ボードの外(番兵)だったら、フラグを反転させ、逆向きを走査する。
			if(1 == flag) {
				flag = -1;
				checkWin(flag, count, temp_row, column, index_dir);
			} else if(-1 == flag) {
				// BOARD_SIZE-3とカウントが一致した場合、勝者が居るという判断をする。
				if(BOARD_SIZE - 3 == count) {
					judge = 1;
				} else {
				// BOARD_SIZE-3とカウントが一致しない場合、勝者が居ないという判断をする。
					flag = 1;
					count = 0;
					checkWin(flag, count, temp_row, column, ++index_dir);
				}
			}
		} else if(EMPTY_CELL == board[check_row + (dir_r[index_dir] * flag)][check_column + (dir_c[index_dir] * flag)]) {
		// 空のセルだったら、フラグを初期化し、次の方向を走査する。
			drow = 1;
			flag = 1;
			count = 0;
			checkWin(flag, count, temp_row, column, ++index_dir);
		} else if(stone != board[check_row + (dir_r[index_dir] * flag)][check_column + (dir_c[index_dir] * flag)]) {
		// 相手の石だったら、フラグを初期化し、次の方向を走査する。
			flag = 1;
			count = 0;
			checkWin(flag, count, temp_row, column, ++index_dir);
		} else if(stone == board[check_row + (dir_r[index_dir] * flag)][check_column + (dir_c[index_dir] * flag)]) {
		// 自分の石だったら、同じ方向の走査を続行する。
			int next_row = check_row + (dir_r[index_dir] * flag);
			int next_column = check_column + (dir_c[index_dir] * flag);
			checkWin(flag, ++count, next_row, next_column, index_dir);
		}
	}
	return;
}

/*
 * 勝者を表示する。
 */
void dispWinner() {
	printf("The winner is Player%d!!\n", ++player);
}

/*
 * 石を変える。
 */
void changeStone() {
	// XならOへ、OならXへ変える。
	stone *= -1;
}

/*
 * プレイヤーを変える。
 */
void changePlayer() {
	/*
	 * XORを使っています。
	 * XORとはビット演算です。
	 * フラグが一緒の場合は0に、違う場合は1にします。
	 * 
	 *  0 ^ 0 = 0
	 *  0 ^ 1 = 1
	 *  1 ^ 0 = 1
	 *  1 ^ 1 = 0
	 */
	player ^= 1;
}
 		
/*
 * main関数です。
 * プログラムが動き出したとき、一番初めに呼ばれる関数です。
 */
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
