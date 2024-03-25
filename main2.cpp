#define _CRT_SECURE_NO_WARNINGS
#define SIZE_OF_BOARD 17
#define WIDTH_OF_BOARD 85
#define SPACE 6
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "conio2.h"

/* Comment: in the final program declare appropriate constants, e.g.,
   to eliminate from your program numerical values by replacing them
   with well defined identifiers */



void Numbers_upper()//prints upper numbers on the board
{
	int numbers_1_row = 3, numbers_2_row = 3;
	for (int i = 13; i <= 24; i++)
	{
		if (i == 19) { numbers_1_row += SPACE * 2; }
		gotoxy(numbers_1_row, 1);
		printf("%02d", i);
		numbers_1_row += SPACE;
	}
	printf("\n");
}
void Numbers_lower()//prints lower numbers on the board
{
	int numbers_1_row = 3, numbers_2_row = 3;
	printf("\n");
	for (int i = 12; i > 0; i--)
	{
		if (i == 6) { numbers_2_row += SPACE * 2; }
		gotoxy(numbers_2_row, SIZE_OF_BOARD + 2);
		printf("%02d", i);
		numbers_2_row += SPACE;
	}
}
void Clear_Board()//clears board from unnecessary signs on the board
{
	for (int i = WIDTH_OF_BOARD / 2 + SPACE - 3; i <= WIDTH_OF_BOARD / 2 + SPACE - 2; i++)
	{
		for (int j = 3; j < SIZE_OF_BOARD - 1; j++)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}
	for (int i = WIDTH_OF_BOARD / 2 - 3; i <= WIDTH_OF_BOARD / 2 - 2; i++)
	{
		for (int j = 3; j < SIZE_OF_BOARD + 1; j++)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}
}
int Die1()//rolling first dice
{
	int result = rand() % 6 + 1;
	return result;
}
int Die2()//rolling second dice
{
	int result = rand() % 6 + 1;
	return result;
}

void Pawns_Player1()//respawning pawns for player 1
{
	int i;
	for (i = SIZE_OF_BOARD; i >= SIZE_OF_BOARD - 4; i--)//left bottom corner
	{ 
		gotoxy(3, i);
		textcolor(2);
		printf("<>");
	}
	for (i = 3; i < 6; i++)//left top corner
	{
		gotoxy(SPACE*4+3, i);
		textcolor(2);
		printf("<>");
	}
	for (i = 3; i < 8; i++)//right top corner
	{
		gotoxy(SPACE*8+3, i);
		textcolor(2);
		printf("<>");
	}
	for (i = SIZE_OF_BOARD; i >= SIZE_OF_BOARD - 1; i--)//right bottom corner
	{
		gotoxy(SPACE * 13 + 3, i);
		textcolor(2);
		printf("<>");
	}

}
void Pawns_Player2()//respawning pawns for player 2
{
	int i;
	for (i = SIZE_OF_BOARD; i >= SIZE_OF_BOARD - 2; i--)//left bottom corner
	{
		gotoxy(SPACE * 4 + 3, i);
		textcolor(2);
		printf("++");
	}
	for (i = SIZE_OF_BOARD; i >= SIZE_OF_BOARD - 4; i--)//right bottom corner
	{
		gotoxy(SPACE * 8 + 3, i);
		textcolor(2);
		printf("++");
	}
	for (i = 3; i <= 4; i++)//right top corner
	{
		gotoxy(SPACE * 13 + 3, i);
		textcolor(2);
		printf("++");
	}
	for (i = 3; i < 8; i++)//left top corner
	{
		gotoxy(3, i);
		textcolor(2);
		printf("++");
	}
}



void Current_Player(int* current_move)//prints current player who makes a move on the board
{
	gotoxy(WIDTH_OF_BOARD + 10, SIZE_OF_BOARD / 2 + 5);
	printf("Current Move: Player %d", *current_move);
}

void Menu()//prints menu on the board
{
	settitle("Kacper, Pietka, 197587");
	_setcursortype(_NOCURSOR);
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD  + 5);
	cputs("press L to load previous game");
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD + 6);
	cputs("press P to START new game");
	gotoxy(WIDTH_OF_BOARD + 15, SIZE_OF_BOARD / 2 + 2);
	cputs("press Q to exit");
	gotoxy(WIDTH_OF_BOARD + 15, SIZE_OF_BOARD / 2 + 3);
	cputs("press R to reverse");
	gotoxy(WIDTH_OF_BOARD + 8, SIZE_OF_BOARD / 2 - 2);
	printf("PLAYER_1: <>, PLAYER_2: ++");
	gotoxy(WIDTH_OF_BOARD+3, SIZE_OF_BOARD / 2 + 2);
	printf("HOME");

}

void Scan_a_board()//SCANS a board and saves it to file named status_of_the_board.txt
{
	const int size = SIZE_OF_BOARD * WIDTH_OF_BOARD * 9;
	char Player[4];
	char current_board_status[size];
	gotoxy(0, 0);
	gettext(0, 0, WIDTH_OF_BOARD, SIZE_OF_BOARD + 2, current_board_status);
	FILE* fp = fopen("status_of_the_board.txt", "w+");
	if (fp == NULL) {
		perror("Error opening file");
		return;
	}
	int x = 0;
	for (int i = 0; i < size; i += 2) {
		if (x == WIDTH_OF_BOARD)
		{
			fprintf(fp, "\n");
			x = 0;
		}
		if (int(current_board_status[i]) >= 32)
		{
			fprintf(fp, "%c", current_board_status[i]);
			x++;
		}
	}
	gettext(WIDTH_OF_BOARD + 31, SIZE_OF_BOARD / 2 + 5, WIDTH_OF_BOARD + 32, SIZE_OF_BOARD / 2 + 5, Player);
	fprintf(fp, "%c", Player[0]);
	fclose(fp);
}

void Menu_Dices()//creates a place to throw Dices
{
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD + 4);
	printf("Press D to roll dice");
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD + 5);
	printf("Result: ");
}

void Result_Dice(int *Cube1, int *Cube2, int *current_move)//Displays result of the Dice
{
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD + 5);
	printf("Result: %d and %d", *Cube1, *Cube2);
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD + 6);
	printf("Player %d Choose column 1-24 (for example for 1st type 01)", *current_move);
}

void while_key_not_d(int *key)//while loop untill pressed key on the board is not 'd'
{
	*key = 0;
	while (*key != 'd')
	{
		*key = getch();
	}
}

int Load_previous_game(int* current_move)//Loads previous game and allows to play it
{
	clrscr();
	char Player[4];
	textcolor(2);
	gotoxy(1, 1);
	char previous_status;
	FILE* fp = fopen("status_of_the_board.txt", "r");
	while ((previous_status = fgetc(fp)) != EOF)
	{
		printf("%c", previous_status);
	}
	Menu();
	gettext(1, SIZE_OF_BOARD + 3, 2, SIZE_OF_BOARD + 3, Player);
	if (Player[0] - '0' == 2) { *current_move = 2; }
	else { *current_move = 1; }
	gotoxy(1, SIZE_OF_BOARD + 3);
	clreol();
	return *current_move;

}


//void left_bottom_formula()
//SPACE * ((12 - current_position) % 12) + 3

//void left_top_formula()
//SPACE * (current_position % 13) + 3

//void right_bottom_formula()
//SPACE * (14 - current_position) + 3;

//void right_top_formula()
//SPACE * (current_position - 11) + 3

bool FINISH(int* current_pawns_player1, int* current_pawns_player2)//function which finishes the whole game
{
	if (*current_pawns_player1 <= 0) {
		gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2);
		printf("GAME ENDED!");
		gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 1);
		printf("Player 1 WON!");
		return true;
	}
	else if (*current_pawns_player2 <= 0)
	{
		gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2);
		printf("GAME ENDED!");
		gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 1);
		printf("Player 2 WON!");
		return true;
	}
	return false;
}

void Clear_Who_starts()//Clears who_starts menu
{
	for (int i = 3; i <= 34; i++)
	{
		for (int j = SIZE_OF_BOARD + 4; j < SIZE_OF_BOARD + 10; j++)
		{
			gotoxy(i, j);
			printf(" ");
		}
	}
}


void Player_1_starts_Menu()//Displays that player 1 starts the game
{
	gotoxy(3, SIZE_OF_BOARD + 8);
	printf("Player 1 starts");
	gotoxy(3, SIZE_OF_BOARD + 9);
	printf("Press any key to start");
}

void Player_2_starts_Menu()//Displays that player 1 starts the game
{
	gotoxy(3, SIZE_OF_BOARD + 8);
	printf("Player 2 starts");
	gotoxy(3, SIZE_OF_BOARD + 9);
	printf("Press any key to start");
}

void Clear_Starting_Menu()//clears press P and press L
{
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD + 5);
	clreol();
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD + 6);
	clreol();
}

void Players_current_Home_Menu(int* current_move, int *current_pawns_player1, int* current_pawns_player2)//Display current pawns at home
{
	gotoxy(3, SIZE_OF_BOARD + 5);
	printf("Player 1's pawns at HOME: %d", 15 - *current_pawns_player1);
	gotoxy(3, SIZE_OF_BOARD + 6);
	printf("Player 2's pawns at HOME: %d", 15 - *current_pawns_player2);
}

void Roll_a_dice(int* pCube1, int* pCube2, int* current_move)//allows to roll dices
{
	Current_Player(current_move);
	Scan_a_board();
	int key = 0;
	while (key != 'd')
	{
		key = getch();
	}
	*pCube1 = Die1(), *pCube2 = Die2(); Result_Dice(pCube1, pCube2, current_move);
}

int while_who_starts(int* key, int Player)//while loop until one of the players throw bigger number
{
	int Cube1 = 0, Cube2 = 0;
	do
	{
		gotoxy(3, SIZE_OF_BOARD + 4);
		printf("PLAYER 1, PRESS D TO ROLL A DIE");
		while_key_not_d(key);
		Cube1 = Die1();
		gotoxy(3, SIZE_OF_BOARD + 5);
		printf("RESULT: %d", Cube1);
		*key = 0;
		gotoxy(3, SIZE_OF_BOARD + 6);
		printf("PLAYER 2, PRESS D TO ROLL A DIE");
		while_key_not_d(key);
		Cube2 = Die2();
		gotoxy(3, SIZE_OF_BOARD + 7);
		printf("RESULT: %d", Cube2);
		*key = 0;
		if (Cube1 == Cube2)
		{
			gotoxy(3, SIZE_OF_BOARD + 8);
			printf("Try again");
		}
	} while (Cube1 == Cube2);
	if (Cube1 > Cube2)
	{
		Player_1_starts_Menu();
		Player = 1;
	}
	else
	{
		Player_2_starts_Menu();
		Player = 2;
	}
	return Player;
}

int Who_starts(int* key, int* current_move)//decides who starts the game
{
	Clear_Starting_Menu();
	int Player = 1;

	if (*key == 'p')
	{
		Player = while_who_starts(key, Player);
		*key = getch();
		Clear_Who_starts();
	}
	else if (*key == 'l')
	{
		Player = Load_previous_game(current_move);
		Clear_Starting_Menu();
		return *current_move;
	}
	return Player;
}

void Remove_pawns_left_bottom(int current_position, char Player)
{
	char current_char[4];
	if (current_position <= 12 && current_position >= 7)//left bottom corner
	{
		int step = SPACE * ((12 - current_position) % 12) + 3;
		bool found = false;
		bool is_dot = false;
		int i = 4, y = SIZE_OF_BOARD / 2;
		while (!found && i <= SIZE_OF_BOARD - 2)
		{
			gotoxy(step, y + i);
			gettext(step, y + i, step + 1, y + i, current_char);
			if (current_char[0] == Player) { found = true; }
			else { i++; }
		}
		gotoxy(step, y + i - 1);
		gettext(step, y + i - 1, step, y + i - 1, current_char);
		if (current_char[0] == '.') { is_dot = true; }
		gotoxy(step, y + i);
		if (is_dot) { printf(".."); }
		else if (found){ printf("/\\"); }
	}
}
void Remove_pawns_right_bottom(int current_position, char Player)
{
	char current_char[4];
	if (current_position <= 6 && current_position >= 1)
	{
		int step = SPACE * (14 - current_position) + 3;
		bool found = false;
		bool is_dot = false;
		int i = 4, y = SIZE_OF_BOARD / 2;
		while (!found && i <= 10)
		{
			gotoxy(step, y + i);
			gettext(step, y + i, step + 1, y + i, current_char);
			if (current_char[0] == Player){ found = true; }
			else { i++; }
		}
		gotoxy(step, y + i - 1);
		gettext(step, y + i - 1, step + 1, y + i - 1, current_char);
		if (current_char[0] == '.') { is_dot = true; }
		gotoxy(step, y + i);
		if (is_dot) { printf(".."); }
		else if (found){ printf("/\\"); }
	}
}
void Remove_pawns_left_top(int current_position, char Player)
{
	char current_char[4];
	if (current_position <= 18 && current_position >= 13)//left top corner
	{
		int step = SPACE * (current_position % 13) + 3;
		bool found = false;
		bool is_dot = false;
		int i = SIZE_OF_BOARD/2;
		while (!found)
		{
			gotoxy(step, i);
			gettext(step, i, step + 1, i, current_char);
			if (current_char[0] == Player) { found = true; }
			else { i--; }
		}
		gotoxy(step, i + 1);
		gettext(step, i + 1, step, i + 1, current_char);
		if (current_char[0] == '.') { is_dot = true; }
		gotoxy(step, i);
		if (is_dot) { printf(".."); }
		else if (found){ printf("\\/"); }
	}
}
void Remove_pawns_right_top(int current_position, char Player)
{
	char current_char[4];
	if (current_position <= 24 && current_position >= 19)
	{
		int step = SPACE * (current_position - 11) + 3;
		bool found = false;
		bool is_dot = false;
		int i = SIZE_OF_BOARD/2;
		while (!found)
		{
			gotoxy(step, i);
			gettext(step, i, step + 1, i, current_char);
			if (current_char[0] == Player) { found = true; }
			else { i--; }
		}
		gotoxy(step, i  + 1);
		gettext(step, i  + 1, step + 1, i + 1, current_char);
		if (current_char[0] == '.') { is_dot = true; }
		gotoxy(step, i);
		if (is_dot) { printf(".."); }
		else if (found) { printf("\\/"); }
	}
}
void Remove_pawns(int current_position, int *current_move)//Removes pawns from clicked column
{
	char Player = '<';
	if (*current_move == 2)
	{

		Player = '+';
	}
	Remove_pawns_left_bottom(current_position, Player);
	Remove_pawns_right_bottom(current_position, Player);
	Remove_pawns_left_top(current_position, Player);
	Remove_pawns_right_top(current_position, Player);

}

void if_current_sign_vertical_line(int Player, int i)//checks if current sign is a vertical line
{
	printf("?");
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD - i);
	printf("||");
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD - i - 1);
	if (Player == '<') { printf("<>"); }
	else { printf("++"); }
}

void Move_Bar_Pawns()//Moves bar pawns to the middle
{
	char current_sign[4];
	int i = 1;
	char Player = '+';
	while (i <= 6)
	{
		gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD  - i);
		gettext(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD  - i, WIDTH_OF_BOARD / 2 + 1, SIZE_OF_BOARD - i, current_sign);
		if (current_sign[0] == '<' || current_sign[0] == '+')
		{
			if (current_sign[0] == '<') { Player = '<'; }
			char current_sign[4];
			gettext(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD - i - 1, WIDTH_OF_BOARD / 2 + 1, SIZE_OF_BOARD - i - 1, current_sign);
			if (current_sign[0] == '|')
			{
				if_current_sign_vertical_line(Player, i);
			}
		}
		i++;
	}
}


void if_hit(int steps, int y, int i, char char_under[4], int current_step, char Player)//checks if the pawn is on the bar
{
	gotoxy(steps, y - current_step + i);
	gettext(steps, y - current_step + i, steps + 1, y - current_step + i, char_under);
	if (Player == '<') { printf("<>"); }
	else { printf("++"); }
	i = 2;
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + i);
	gettext(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + i, WIDTH_OF_BOARD / 2 + 1, SIZE_OF_BOARD / 2 + i, char_under);
	while (char_under[0] != '|')
	{
		i++;
		gettext(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + i, WIDTH_OF_BOARD / 2 + 1, SIZE_OF_BOARD / 2 + i, char_under);
	}
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + i);
	if (Player == '<') { printf("++"); }
	else { printf("<>"); }
}

void HIT(int* current_move, int move, int current_step, int steps)//HIT functions which moves pawns to the bar if hit
{
	int y = SIZE_OF_BOARD;
	int i = 1;
	bool hit = false;
	char char_under[4];
	char enemy_Player = '<';
	char Player = '+';
	if (*current_move == 1)
	{
		enemy_Player = '+';
		Player = '<';
	}
	if (move >= 13) { y = current_step + 4; i -= 2; }
	gotoxy(steps, y - current_step);
	gettext(steps, y - current_step + i, steps + 1,  y - current_step + i, char_under);
	if (char_under[0] == enemy_Player)
	{
		hit = true;
		Remove_pawns(move, current_move);
	}
	if (hit){
		if_hit(steps, y, i, char_under, current_step, Player);
	}
}


void CLEAR_BAR(int* current_move)//clears bar after hit pawn went back to the board
{
	char current_sign[4];
	if (*current_move == 1)
	{
		gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2);
		gettext(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2, WIDTH_OF_BOARD / 2 + 1, SIZE_OF_BOARD / 2 + 2, current_sign);
		if (current_sign[0] == '<') {
			gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2);
			printf("||");
		}
	}
	else
	{
		gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2);
		gettext(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2, WIDTH_OF_BOARD / 2 + 1, SIZE_OF_BOARD / 2 + 2, current_sign);
		if (current_sign[0] == '+') {
			gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2);
			printf("||");
		}
	}
}



void Check_if_wrong_column_right_bottom(int* move, char enemy_Player)
{
	if (*move <= 6 && *move >= 1)
	{
		char current_sign[4];
		int enemy_pawns = 0;
		int sign = 0;
		for (int x = 0; x < 6; x++)
		{
			gotoxy(SPACE * (14 - *move) + 3, SIZE_OF_BOARD - x);
			gettext(SPACE * (14 - *move) + 3, SIZE_OF_BOARD - x, SPACE * (14 - *move) + 4, SIZE_OF_BOARD - x, current_sign);
			if (current_sign[0] == enemy_Player)
			{
				enemy_pawns++;
			}
			else if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				sign++;
			}
		}
		if (enemy_pawns > 1 || sign == 0)
		{
			*move = 0;
		}
	}
}
void Check_if_wrong_column_left_bottom(int* move, char enemy_Player)
{
	if (*move <= 12 && *move >= 7)
	{
		int steps = SPACE * ((12 - *move) % 12) + 3;
		char current_sign[4];
		int enemy_pawns = 0;
		int sign = 0;
		for (int x = 0; x < 6; x++)
		{
			gotoxy(steps, SIZE_OF_BOARD - x);
			gettext(steps, SIZE_OF_BOARD - x, steps + 1, SIZE_OF_BOARD - x, current_sign);
			if (current_sign[0] == enemy_Player)
			{
				enemy_pawns++;
			}
			else if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				sign++;
			}
		}
		if (enemy_pawns > 1 || sign == 0)
		{
			*move = 0;
		}
	}
}
void Check_if_wrong_column_left_top(int* move, char enemy_Player)
{
	if (*move <= 18 && *move >= 13)
	{
		int steps = SPACE * (*move % 13) + 3;
		char current_sign[4];
		int enemy_pawns = 0;
		int sign = 0;
		for (int x = 3; x < 9; x++)
		{
			gotoxy(steps,  x);
			gettext(steps, x, steps + 1, x, current_sign);
			if (current_sign[0] == enemy_Player)
			{
				enemy_pawns++;
			}
			else if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				sign++;
			}
		}
		if (enemy_pawns > 1 || sign == 0)
		{
			*move = 0;
		}
	}
}
void Check_if_wrong_column_right_top(int* move, char enemy_Player)
{
	if (*move <= 24 && *move >= 19)
	{
		int steps = SPACE * (*move - 11) + 3;
		char current_sign[4];
		int enemy_pawns = 0;
		int sign = 0;
		for (int x = 3; x < 9; x++)
		{
			gotoxy(steps,  x);
			gettext(steps, x, steps + 1, x, current_sign);
			if (current_sign[0] == enemy_Player)
			{
				enemy_pawns++;
			}
			else if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				sign++;
			}
		}
		if (enemy_pawns > 1 || sign == 0)
		{
			*move = 0;
		}
	}
}
void Check_if_wrong_column(int *current_move, int *move1, int *move2)//checks if clicked column has possible moves
{
	char enemy_Player = '<';
	if (*current_move == 1)
	{
		enemy_Player = '+';
	}
	Check_if_wrong_column_right_bottom(move1, enemy_Player);
	Check_if_wrong_column_right_bottom(move2, enemy_Player);
	Check_if_wrong_column_left_bottom(move1, enemy_Player);
	Check_if_wrong_column_left_bottom(move2, enemy_Player);
	Check_if_wrong_column_left_top(move1, enemy_Player);
	Check_if_wrong_column_left_top(move2, enemy_Player);
	Check_if_wrong_column_right_top(move1, enemy_Player);
	Check_if_wrong_column_right_top(move2, enemy_Player);
}

bool HOME_PlAYER_1(int* current_pawns_player1)//checks if player 1 has sufficient number of pawns(15)
{
	char current_sign[4];
	int starting_column = 19;//19 is 19th column on the board(starting position HOME player 1
	int pawns = 0;
	for (int x = 0; x < 6; x++)
	{
		int start = SPACE * (starting_column - 11) + 3;
		for (int i = SIZE_OF_BOARD / 2; i >= 3; i--)
		{
			gotoxy(start, i);
			gettext(start, i, start + 1, i, current_sign);
			if (current_sign[0] == '<')
			{
				pawns++;
			}
		}
		starting_column++;
	}
	if (pawns == *current_pawns_player1)
	{
		return true;
	}
	return false;
}

bool HOME_PlAYER_2(int *current_pawns_player2)//checks if player 2 has sufficient number of pawns(15)
{
	char current_sign[4];
	int starting_column = 6;//6 is 6th column on the board(starting position HOME player 2)
	int i = SIZE_OF_BOARD / 2 + 3;
	int pawns = 0;
	for (int x = 0; x < 6; x++)
	{
		int start = SPACE * (14 - starting_column) + 3;
		for (int i = SIZE_OF_BOARD / 2 + 3; i <= SIZE_OF_BOARD; i++)
		{
			gotoxy(start, i);
			gettext(start, i, start + 1, i, current_sign);
			if (current_sign[0] == '+')
			{
				pawns++;
			}
		}
		starting_column--;
	}
	if (pawns == *current_pawns_player2)
	{
		return true;
	}
	return false;
}

void ENTRY_HOME(int* current_move, int *move1, int *move2, int current_position, int* current_pawns_player1, int* current_pawns_player2)//allows players to entry Home
{
	int x = WIDTH_OF_BOARD + 6;
	int y = SIZE_OF_BOARD;
	Players_current_Home_Menu(current_move,current_pawns_player1,current_pawns_player2);
	if (*current_move == 1)
	{
		gotoxy(x, y - 1);
		printf("PRESS h TO GO HOME");
		if (*move1 >= 25)
		{
			gotoxy(x, y);
			printf("Possible move: h");
		}
		else if (*move2 >= 25)
		{
			gotoxy(x, y + 1);
			printf("Possible move: h");
		}
	}
	else
	{
		gotoxy(x, y - 1);
		printf("PRESS h TO GO HOME");
		if (*move1 <= 0)
		{
			gotoxy(x, y);
			printf("Possible move: h");
		}
		else if (*move2 <= 0)
		{
			gotoxy(x, y + 1);
			printf("Possible move: h");

		}
	}
}

void Clear_Possible_moves()//Clears possible moves menu
{
	gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 3);
	clreol();
	gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 4);
	clreol();
}

bool Display_Possible_moves(int *current_move, int *pmove1, int *pmove2, int current_position)//Displays possible moves on the screen
{
	bool possible = false;
	Check_if_wrong_column(current_move, pmove1, pmove2);
	gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD);
	if (*pmove1 <= 24 && *pmove1 >= 1 && *pmove1 != current_position) { printf("Possible move: %02d ", *pmove1); gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 1); possible = true; }
	else { printf("Possible move: - "); gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 1); }
	if (*pmove2 <= 24 && *pmove2 >= 1 && *pmove2 != current_position && *pmove2 != *pmove1) { printf("Possible move: %02d ", *pmove2); gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 2); possible = true; }
	else { printf("Possible move: - "); }
	return possible;
}

void No_Possible_moves_menu()//Displays that you should pick a different column
{
	gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 3);
	printf("YOU PICKED WRONG COLUMN!");
	gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 4);
	printf("Pick Different one");
}

void move_calculation(int* current_move, int* move1, int* move2, int current_position, int *pCube1, int *pCube2)
{//calculates which moves after chosen column
	if (*current_move == 1)
	{
		*move1 = *pCube1 + current_position;
		*move2 = *pCube2 + current_position;
		if (*move1 <= current_position && *move2 <= current_position)
		{
			*move1 = 0;
			*move2 = 0;
		}
	}
	else if (*current_move == 2)
	{
		*move1 = current_position - *pCube1;
		*move2 = current_position - *pCube2;
		if (*move1 >= current_position && *move2 >= current_position)
		{
			*move1 = 0;
			*move2 = 0;
		}
	}
}

int current_position_keys(int key1, int key2)
{//calculates returns to which column player can move
	int move = (key1 - '0') * 10 + (key2 - '0');
	return move;
}

bool Check_Home_players(int* pCube1, int* pCube2, int* current_move, int* current_pawns_player1, int* current_pawns_player2, int current_position, int*pmove1, int*pmove2)
{//checks if players can move to the home
	int possible = false;
	if (HOME_PlAYER_1(current_pawns_player1) && *current_move == 1 && (*pmove1 >= 25 || *pmove2 >= 25)) { ENTRY_HOME(current_move, pmove1, pmove2, current_position, current_pawns_player1, current_pawns_player2); possible = true; }
	else if (HOME_PlAYER_2(current_pawns_player2) && *current_move == 2 && (*pmove1 <= 0 || *pmove2 <= 0)) { ENTRY_HOME(current_move, pmove1, pmove2, current_position, current_pawns_player1, current_pawns_player2);  possible = true; }
	
	return possible;
}


int Possible_Moves(int *pCube1, int *pCube2, int* cm, int *current_pawns_player1, int* current_pawns_player2)
{//possible moves for the player to make a move on the board
	if (*pCube1 > 0 || *pCube2 > 0)
	{
		int key1 = getch(), key2 = getch();
		Clear_Possible_moves();
		int cp = current_position_keys(key1, key2);//current possiton
		int m1 = 0, m2 = 0;//move1 and move2 
		int* pm1 = &m1, *pm2 = &m2;//pointeer to move1 and pointer to move2
		bool p = false;//possible bool
		move_calculation(cm, pm1, pm2, cp, pCube1, pCube2);
		p = Display_Possible_moves(cm, pm1, pm2, cp);
		bool ph = false;//possible home move bool
		ph = Check_Home_players(pCube1, pCube2, cm, current_pawns_player1, current_pawns_player2, cp, pm1, pm2);
		if (!p && !ph)//checks if none of them is possible and allows to change chosen column
		{
			No_Possible_moves_menu();
			cp = Possible_Moves(pCube1, pCube2, cm, current_pawns_player1, current_pawns_player2);
		}
		if (p || ph) { Remove_pawns(cp, cm); }
		return cp;
	}
}

bool Display_Bar_possible_moves(int *pmove1, int *pmove2)
{//Displays possible moves from the bar after being hit
	bool can_move1 = true, can_move2 = true;
	gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD);
	if (*pmove1 > 0 && *pmove1 != 25 && *pmove1 != 0) { printf("Possible move: %02d", *pmove1); }
	else { printf("Possible move: --"); can_move1 = false; }
	gotoxy(WIDTH_OF_BOARD + 6, SIZE_OF_BOARD + 1);
	if (*pmove2 > 0 && *pmove2 != 25 && *pmove2 != 0) { printf("Possible move: %02d", *pmove2); }
	else { printf("Possible move: --"); can_move2 = false; }
	if (!can_move1 && !can_move2)
	{
		return false;
	}
	return true;
}

void if_cant_move_bar(int *current_move, int*pCube1, int*pCube2)
{
	int cp = 0;
	if (*current_move == 2) { *current_move = 1; Roll_a_dice(pCube1, pCube2, current_move); }
	else {*current_move = 2; Roll_a_dice(pCube1, pCube2, current_move);}
}

void Bar_possible_moves(int* pCube1, int* pCube2, int* current_move, int *move)
{//Possible moves from the bar after being hit
	int* key = 0;
	bool can_move= true;
	int move1, move2;
	if (*current_move == 2){
		move1 = *pCube1 + *move;
		move2 = *pCube2 + *move;
	}
	else
	{
		move1 = *move - *pCube1;
		move2 = *move - *pCube2;
	}
	int *pmove1 = &move1;
	int *pmove2 = &move2;
	Check_if_wrong_column(current_move, pmove1, pmove2);
	can_move = Display_Bar_possible_moves(pmove1, pmove2);
	if (!can_move)
	{
		if_cant_move_bar(current_move,pCube1,pCube2);
	}
}


void Make_a_move_right_bottom(int move, char current_sign[], int *current_move)
{//Makes a move to righ bottom square of the board
	char Player = '<';
	int steps = SPACE * (14 - move) + 3;
	if (*current_move == 2) { Player = '+'; }
	if (move <= 6 && move >= 1)
	{
		bool found = false;
		int i = 0;
		while (!found)
		{
			gotoxy(steps, SIZE_OF_BOARD - i);
			gettext(steps, SIZE_OF_BOARD - i, steps + 1, SIZE_OF_BOARD - i, current_sign);
			if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				gotoxy(steps, SIZE_OF_BOARD - i);
				found = true;
			}
			i++;
		}
		if (found) {
			if (Player == '<') { printf("<>"); }
			else { printf("++"); }
			HIT(current_move, move, i - 1, steps);
		}
	}
}
void Make_a_move_left_bottom(int move, char current_sign[], int *current_move)
{//Makes a move to left bottom square of the board
	char Player = '<';
	if (*current_move == 2) { Player = '+'; }
	if (move <= 12 && move >= 7)
	{
		int steps = SPACE * ((12 - move) % 12) + 3;
		bool found = false;
		int i = 0;
		while (!found)
		{
			gotoxy(steps, SIZE_OF_BOARD - i);
			gettext(steps, SIZE_OF_BOARD - i, steps + 1, SIZE_OF_BOARD - i, current_sign);
			if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				gotoxy(steps, SIZE_OF_BOARD - i);
				found = true;
			}
			i++;
		}
		if (found) {
			if (Player == '<') { printf("<>"); }
			else { printf("++"); }
			HIT(current_move, move, i - 1, steps);
		}

	}
}
void Make_a_move_left_top(int move, char current_sign[], int *current_move)
{//Makes a move to left top square of the board
	char Player = '<';
	if (*current_move == 2) { Player = '+'; }
	if (move <=18  && move >= 13)
	{
		int steps = SPACE * (move % 13) + 3;
		bool found = false;
		int i = 0;
		while (!found)
		{
			gotoxy(steps, i + 3);
			gettext(steps, i + 3, steps + 1, i + 3, current_sign);
			if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				gotoxy(steps, i + 3);
				textcolor(2);
				found = true;
			}
			i++;
		}
		if (found) {
			if (Player == '<') { printf("<>"); }
			else { printf("++"); }
			HIT(current_move, move, i + 3 - 1, steps);
		}

	}
}
void Make_a_move_right_top(int move, char current_sign[], int* current_move)
{//Makes a move to righ top square of the board
	char Player = '<';
	if (*current_move == 2) { Player = '+'; }
	if (move <= 24 && move >= 19)
	{
		int steps = SPACE * (move - 11) + 3;
		bool found = false;
		int i = 0;
		while (!found)
		{
			gotoxy(steps, i + 3);
			gettext(steps, i + 3, steps + 1, i + 3, current_sign);
			if (current_sign[0] == '.' || current_sign[0] == '/' || current_sign[0] == '\\')
			{
				gotoxy(steps, i + 3);
				textcolor(2);
				found = true;
			}
			i++;
		}
		if (found) {
			if (Player == '<') { printf("<>"); }
			else { printf("++"); }
			HIT(current_move, move, i + 3 - 1, steps);
		}
	}
}

void Moves(int move, int* current_move)
{//Moves pawns all over the board
	char current_sign[4];
	Make_a_move_right_bottom(move, current_sign, current_move);
	Make_a_move_left_bottom(move, current_sign, current_move);
	Make_a_move_left_top(move, current_sign, current_move);
	Make_a_move_right_top(move, current_sign, current_move);
	CLEAR_BAR(current_move);
	Move_Bar_Pawns();
}

int Second_Move_Player1(int move, int* current_move, int* Cube1, int* Cube2, int current_position, int *current_pawns_player1, int *current_pawns_player2)
{//Player 1 makes a second move
	char current_sign[4];
	Moves(move, current_move);
	if (*Cube1 == *Cube2)
	{
		return 1;
	}
	else if (move - current_position == *Cube1 && *Cube1 != 0)
	{
		*Cube1 = 0;
		Possible_Moves(Cube1, Cube2, current_move, current_pawns_player1,current_pawns_player2);
	}
	else if (move - current_position == *Cube2 && *Cube2 != 0)
	{
		*Cube2 = 0;
		Possible_Moves(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2);
	}
}

int Second_Move_Player2(int move, int* current_move, int* Cube1, int* Cube2, int current_position, int* current_pawns_player1, int *current_pawns_player2)
{//Player 2 makes a second move
	char current_sign[4];
	Moves(move, current_move);
	if (*Cube1 == *Cube2)
	{
		return 1;
	}
	else if (current_position - move == *Cube1 && *Cube1 != 0)
	{
		*Cube1 = 0;
		Possible_Moves(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2);
	}
	else if (current_position - move == *Cube2 && *Cube2 != 0)
	{
		*Cube2 = 0;
		Possible_Moves(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2);
	}
}


void if_key_h_second_move(int* pCube1, int* pCube2, int* current_move, int current_position, int* current_pawns_player1, int* current_pawns_player2)
{//happens if pressed key was 'h' and allows to make a second move
	if (*current_move == 1)
	{
		(*current_pawns_player1)--;
		if (*pCube1 > 0 || *pCube2 > 0)
		{
			Second_Move_Player1(25, current_move, pCube1, pCube2, current_position, current_pawns_player1, current_pawns_player2);
		}
		else
		{
			*current_move = 2;
			Roll_a_dice(pCube1, pCube2, current_move);
		}
	}
	else if (*current_move == 2) {
		(*current_pawns_player2)--;
		if (*pCube1 > 0 || *pCube2 > 0)
		{
			Second_Move_Player2(0, current_move, pCube1, pCube2, current_position, current_pawns_player1, current_pawns_player2);
		}
		else
		{
			*current_move = 1;
			Roll_a_dice(pCube1, pCube2, current_move);
		}
	}
}

void if_key_not_h_second_move(int move, int* pCube1, int* pCube2, int* current_move, int current_position, int* current_pawns_player1, int* current_pawns_player2)
{//happens if pressed key was not 'h' and allows to make a second move
	if (*current_move == 1)
	{
		if (*pCube1 > 0 || *pCube2 > 0)
		{
			Second_Move_Player1(move, current_move, pCube1, pCube2, current_position, current_pawns_player1, current_pawns_player2);
		}
		else
		{
			*current_move = 2;
			Roll_a_dice(pCube1, pCube2, current_move);
		}
	}
	else if (*current_move == 2) {
		if (*pCube1 > 0 || *pCube2 > 0)
		{
			Second_Move_Player2(move, current_move, pCube1, pCube2, current_position, current_pawns_player1, current_pawns_player2);
		}
		else
		{
			*current_move = 1;
			Roll_a_dice(pCube1, pCube2, current_move);
		}
	}
}

int Make_a_Second_Move(int* pCube1, int* pCube2, int* current_move, int current_position, int*current_pawns_player1, int* current_pawns_player2)
{//allows player to make a second move
	int key1, key2;
	key1 = getch();
	if (key1 == 'h')
	{
		if_key_h_second_move(pCube1, pCube2, current_move, current_position, current_pawns_player1, current_pawns_player2);
	}
	else
	{
		key2 = getch();
		int move = (key1 - '0') * 10 + (key2 - '0');
		if_key_not_h_second_move(move, pCube1, pCube2, current_move, current_position, current_pawns_player1, current_pawns_player2);
	}
	return 1;
}


void PossibleMovesMakeaSecondMove(int* Cube1, int* Cube2, int* current_move, int* current_pawns_player1, int* current_pawns_player2, int current_position)
{//two functions squeezed together to save some space
	Possible_Moves(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2);
	Make_a_Second_Move(Cube1, Cube2, current_move, current_position, current_pawns_player1, current_pawns_player2);
}

void Move_Player1(int move, int *current_move, int *Cube1, int *Cube2, int current_position, int loop, int* current_pawns_player1, int* current_pawns_player2)
{//Player 1 makes a move
	Moves(move, current_move);
	if (*Cube1 == *Cube2)
	{
		int i = 0;
		while (i != (3 - loop))
		{
			PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, current_position);
			i++;
		}
		*Cube1 = 0;
		*Cube2 = 0;
	}
	else if (move - current_position == *Cube1)
	{
		*Cube1 = 0;
		PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, current_position);
	}
	else if (move - current_position == *Cube2)
	{
		*Cube2 = 0;
		PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, current_position);
	}
}

void Move_Player2(int move, int* current_move, int* Cube1, int* Cube2, int current_position, int loop, int *current_pawns_player1, int *current_pawns_player2)
{//Player 2 make a move
	Moves(move, current_move);
	if (*Cube1 == *Cube2)
	{
		int i = 0;
		while (i != (3 - loop))
		{
			PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, current_position);
			i++;
		}
		*Cube1 = 0;
		*Cube2 = 0;
	}
	else if (current_position - move == *Cube1)
	{
		*Cube1 = 0;
		PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, current_position);
	}
	else if (current_position - move == *Cube2)
	{
		*Cube2 = 0;
		PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, current_position);
	}
}

void if_key_h_move(int* Cube1, int* Cube2, int* current_move, int current_position, int loop, int* current_pawns_player1, int* current_pawns_player2)
{//happens after pressed key was 'h' to move to home
	if (*current_move == 1)
	{
		(*current_pawns_player1)--;
		if (*Cube1 > 0 || *Cube2 > 0)
		{
			Move_Player1(25, current_move, Cube1, Cube2, current_position, loop, current_pawns_player1, current_pawns_player2);
			*current_move = 2;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
	}
	else if (*current_move == 2)
	{
		(*current_pawns_player2)--;
		if (*Cube1 > 0 || *Cube2 > 0)
		{
			Move_Player2(0, current_move, Cube1, Cube2, current_position, loop, current_pawns_player1, current_pawns_player2);
			*current_move = 1;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
	}
}

void if_key_not_h_move(int move, int* Cube1, int* Cube2, int* current_move, int current_position, int loop, int* current_pawns_player1, int* current_pawns_player2)
{//happens after pressed key was not h to move to home
	if (*current_move == 1)
	{
		if (*Cube1 > 0 || *Cube2 > 0)
		{
			Move_Player1(move, current_move, Cube1, Cube2, current_position, loop, current_pawns_player1, current_pawns_player2);
			*current_move = 2;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
	}
	else if (*current_move == 2)
	{
		if (*Cube1 > 0 || *Cube2 > 0)
		{
			Move_Player2(move, current_move, Cube1, Cube2, current_position, loop, current_pawns_player1, current_pawns_player2);
			*current_move = 1;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
	}
}

void Make_a_Move(int *Cube1, int *Cube2, int *current_move, int current_position, int loop, int *current_pawns_player1, int* current_pawns_player2)
{//allows player to make a move on the board
	int key1, key2;
	key1 = getch();
	if (key1 == 'h')
	{
		if_key_h_move(Cube1, Cube2, current_move, current_position, loop,current_pawns_player1,current_pawns_player2);
	}
	else
	{
		key2 = getch();
		int move = current_position_keys(key1, key2);
		if_key_not_h_move(move, Cube1, Cube2, current_move, current_position, loop, current_pawns_player1, current_pawns_player2);
	}
}

void PossibleMovesMakeaMove(int* Cube1, int* Cube2, int* current_move, int *current_position, int loop, int* current_pawns_player1, int* current_pawns_player2)
{//two functions connected together to save characters
	Possible_Moves(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2);
	Make_a_Move(Cube1, Cube2, current_move, *current_position, loop, current_pawns_player1, current_pawns_player2);
}

void Make_a_Bar_Move(int* Cube1, int* Cube2, int* current_move, int current_position)
{//Makes a bar move back to the board
	int key1, key2;
	key1 = getch();
	key2 = getch();
	int move = current_position_keys(key1, key2);
	Moves(move, current_move);
	if (*current_move == 1)
	{
		if (*Cube1 != *Cube2)
		{
			if (current_position - move == *Cube1)
			{
				*Cube1 = 0;
			}
			else if (current_position - move == *Cube2)
			{
				*Cube2 = 0;
			}
		}
	}
	else
	{
		if (*Cube1 != *Cube2)
		{
			if (move - current_position == *Cube1)
			{
				*Cube1 = 0;
			}
			else if (move - current_position == *Cube2)
			{
				*Cube2 = 0;
			}
		}
	}
}

char Bar_gettext(char bar[4])// get text from the bar
{
	gotoxy(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2);
	gettext(WIDTH_OF_BOARD / 2, SIZE_OF_BOARD / 2 + 2, WIDTH_OF_BOARD / 2 + 1, SIZE_OF_BOARD / 2 + 2, bar);
	return bar[0];
}

int while_coming_out_loop_player1(char bar[2], int *current_move, int *current_position, int *Cube1, int *Cube2, int player)
{//while loop untill bar is empty from <
	int loop = 0;
	while (bar[0] == '<' && *current_move == 1)
	{
		Bar_possible_moves(Cube1, Cube2, current_move, current_position);
		Make_a_Bar_Move(Cube1, Cube2, current_move, player);
		bar[0] = Bar_gettext(bar);
		loop++;

	}
	return loop;
}

int while_coming_out_loop_player2(char bar[2], int* current_move, int* current_position, int* Cube1, int* Cube2, int player)
{//while loop untill bar is empty from +
	int loop = 0;
	while (bar[0] == '+' && *current_move == 2)
	{
		Bar_possible_moves(Cube1, Cube2, current_move, current_position);
		Make_a_Bar_Move(Cube1, Cube2, current_move, player);
		bar[0] = Bar_gettext(bar);
		loop++;

	}
	return loop;
}

void Bar_Moves_Player1(char bar[2], int* current_move, int* current_position, int* Cube1, int* Cube2, int player, int* current_pawns_player1, int* current_pawns_player2)
{//Moves bar pawns player 1 to the board while bar is empty
	int loop;
	if (bar[0] == '<' && *current_move == 1)
	{
		loop = while_coming_out_loop_player1(bar, current_move, current_position, Cube1, Cube2, player);
		if (*Cube1 == *Cube2 && (*Cube1 != 0 && *Cube2 != 0))
		{
			PossibleMovesMakeaMove(Cube1, Cube2, current_move, current_position, loop, current_pawns_player1, current_pawns_player2);
		}
		else if (loop < 2)
		{
			PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, *current_position);
			*current_move = 2;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
		else
		{
			*current_move = 2;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
	}
}

void Bar_Moves_Player2(char bar[2], int* current_move, int* current_position, int* Cube1, int* Cube2, int player, int* current_pawns_player1, int* current_pawns_player2)
{//Moves bar pawns player 2 to the board while bar is empty
	int loop;
	if (bar[0] == '+' && *current_move == 2)
	{
		loop = while_coming_out_loop_player2(bar, current_move, current_position, Cube1, Cube2, player);
		if (*Cube1 == *Cube2 && (*Cube1 != 0 && *Cube2 != 0))
		{
			PossibleMovesMakeaMove(Cube1, Cube2, current_move, current_position, loop, current_pawns_player1, current_pawns_player2);
		}
		else if (loop < 2)
		{
			PossibleMovesMakeaSecondMove(Cube1, Cube2, current_move, current_pawns_player1, current_pawns_player2, *current_position);
			*current_move = 1;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
		else
		{
			*current_move = 1;
			Roll_a_dice(Cube1, Cube2, current_move);
		}
	}
}

void Coming_Out(int* current_move, int* Cube1, int* Cube2, int* key,int* current_pawns_player1, int*current_pawns_player2)//NIE MOZNA WYRZUCIC KOSTKA PO
{//Function which allows player to come out from the middle bar after being hit
	char bar[4];
	int player = 25;
	int* current_position = &player;
	bar[0] = Bar_gettext(bar);
	if (*current_move == 1)
	{
		bar[0] = Bar_gettext(bar);
		Bar_Moves_Player1(bar,current_move, current_position, Cube1, Cube2, player, current_pawns_player1, current_pawns_player2);
	}
	else if (*current_move == 2)
	{
		bar[0] = Bar_gettext(bar);
		*current_position = 0;
		Bar_Moves_Player2(bar, current_move, current_position, Cube1, Cube2, player, current_pawns_player1, current_pawns_player2);
		
	}
}

int Middle_of_the_board(int j)//vertical line at the middle of the board
{
	if (j == WIDTH_OF_BOARD / 2 - 1 || j == WIDTH_OF_BOARD / 2 || j == WIDTH_OF_BOARD / 2 + 1 || j == WIDTH_OF_BOARD - 2 || j == WIDTH_OF_BOARD / 2 - 2)
	{
		printf("|");
		return 1;
	}
	return 0;
}
int dots(int j, int i)//dots as place to hold pawns
{
	if ((j % (SPACE * 2) == 3 && i > SIZE_OF_BOARD / 2 + 1 && j != WIDTH_OF_BOARD / 2 + SPACE - 2) || (j % (SPACE) == 3 && i < SIZE_OF_BOARD / 2 - 1 && j != WIDTH_OF_BOARD / 2 + SPACE - 2 && j != WIDTH_OF_BOARD / 2 + SPACE + 2) || (j % (SPACE) == 2 && i < SIZE_OF_BOARD / 2 - 1 && j != WIDTH_OF_BOARD / 2 - SPACE + 2 && j != WIDTH_OF_BOARD / 2 + SPACE - 5) || (j % (SPACE) == 3 && i < SIZE_OF_BOARD / 2 - 1 && j != WIDTH_OF_BOARD / 2 - SPACE + 2 && j != WIDTH_OF_BOARD / 2 + SPACE - 4) || (j % (SPACE * 2) == 2 && i > SIZE_OF_BOARD / 2 + 1 && j != WIDTH_OF_BOARD / 2 - SPACE + 2))
	{
		printf(".");
		return 1;
	}
	return 0;
}
int hashtags(int j, int i)//hashtags around the board
{
	if (i == 0 || i == (SIZE_OF_BOARD - 1) || j == (WIDTH_OF_BOARD - 1) || j == 0)
	{
		printf("#");
		return 1;
	}
	return 0;
}
int frtontslash1(int j, int i)//frontslashes as a place to hold pawns
{
	if ((j % (SPACE * 2) == 3 && i < SIZE_OF_BOARD / 2 - 1 && j != WIDTH_OF_BOARD / 2 - SPACE + 2))
	{
		printf("/");
		return 1;
	}
	return 0;
}
int frtontslash2(int j, int i)//frontslashes as a place to hold pawns
{
	if (j % (SPACE) == 2 && i > SIZE_OF_BOARD / 2 + 1 && j != WIDTH_OF_BOARD / 2 - SPACE + 2 && j != WIDTH_OF_BOARD / 2 + SPACE - 4)
	{
		printf("/");
		return 1;
	}
	return 0;
}
int backslash1(int j, int i)//backslashes as a place to hold pawns
{
	if ((j % (SPACE * 2) == 2 && i < SIZE_OF_BOARD / 2 - 1 && j != WIDTH_OF_BOARD / 2 - SPACE + 2))
	{
		printf("\\");
		return 1;
	}
	return 0;
}
int backslash2(int j, int i)//backslashes as a place to hold pawns
{
	if (j % (SPACE) == 3 && i > SIZE_OF_BOARD / 2 + 1 && j != WIDTH_OF_BOARD / 2 - SPACE + 2 && j != WIDTH_OF_BOARD / 2 + SPACE - 3)
	{
		printf("\\");
		return 1;
	}
	return 0;
}
void Print_Board()//Function which prints the whole board
{
	for (int i = 0; i < SIZE_OF_BOARD; i++)
	{
		for (int j = 0; j < WIDTH_OF_BOARD; j++)
			if (hashtags(j, i) == 1);
			else if (Middle_of_the_board(j) == 1);
			else if (backslash1(j, i) == 1);
			else if (frtontslash1(j, i) == 1);
			else if (dots(j, i) == 1);
			else if (backslash2(j, i) == 1);
			else if (frtontslash2(j, i) == 1);
			else { printf(" "); }
		printf("\n");
	}
}
void Board()//Takes everything together and prints whole board to play
{
	Numbers_upper();
	Print_Board();
	Numbers_lower();
	Clear_Board();
	Pawns_Player1();
	Pawns_Player2();
}




void Coming_out_Current_Player(int *current_move, int *pCube1, int*pCube2, int*key, int *current_pawns_player1, int *current_pawns_player2)
{
	Current_Player(current_move);
	Coming_Out(current_move, pCube1, pCube2, key, current_pawns_player1, current_pawns_player2);
	Current_Player(current_move);
	Coming_Out(current_move, pCube1, pCube2, key, current_pawns_player1, current_pawns_player2);
	Current_Player(current_move);
}

void while_game(int* current_move, int current_position, int* key, int* current_pawns_player1, int* current_pawns_player2, int*pCube1, int *pCube2)
{//UNTILL GAME ENDS LOOP GOES
	do {
		Coming_out_Current_Player(current_move, pCube1, pCube2, key, current_pawns_player1, current_pawns_player2);
		current_position = Possible_Moves(pCube1, pCube2, current_move, current_pawns_player1, current_pawns_player2);
		*key = 0;
		Make_a_Move(pCube1, pCube2, current_move, current_position, 0, current_pawns_player1, current_pawns_player2);
		Scan_a_board();
		Players_current_Home_Menu(current_move, current_pawns_player1, current_pawns_player2);
		if (FINISH(current_pawns_player1, current_pawns_player2)) { break; }
	} while (*key != 'q');
}

void game(int* current_move, int current_position, int* key, int* current_pawns_player1, int* current_pawns_player2)
{//GAME FUNCTION
	int Cube1 = 0, Cube2 = 0;
	int* pCube1 = &Cube1, *pCube2 = &Cube2;//POINTERS TO CUBES
	Roll_a_dice(pCube1, pCube2, current_move);
	while_game(current_move, current_position, key, current_pawns_player1, current_pawns_player2, pCube1, pCube2);
	return;
}


int main() {
	textcolor(2);
	srand(time(0));
	int key = 0, cur_move = 1, current_position = 0, current_pawns_player1 = 15, current_pawns_player2 = 15;
	int* pointer_key = &key, *current_move = &cur_move, *pcurrent_pawns_player1 = &current_pawns_player1, *pcurrent_pawns_player2 = &current_pawns_player2;
	Menu();
	Board();
	do { key = getch(); } while (key != 'p' && key != 'l' && key != 'q');
	if (key == 'q') { return 0; }
	*current_move = Who_starts(pointer_key, current_move);
	Menu_Dices();
	key = 0;
	game(current_move, current_position, pointer_key, pcurrent_pawns_player1, pcurrent_pawns_player2);
	return 0;
}