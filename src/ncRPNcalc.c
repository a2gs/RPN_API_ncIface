#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h> /* for HUGE_VAL */
#include <ncurses.h>

#include <librpn.h>

#define ESC_KEY 27

typedef enum{
	NUM = 1,
	CHAR,
	OPERATOR,
	ESC,
	ENTER,
	BACKSPACE,
	UNDEF
}chtpye_t;

chtpye_t whatIs(int ch)
{
	if(ch == ESC_KEY)
		return(ESC);

	if(ch == KEY_ENTER)
		return(ENTER);

	if(ch == KEY_BACKSPACE || ch == KEY_DC)
		return(BACKSPACE);

	if((ch >= 48 && ch <= 57) || ch == 44 || ch == 46) /* 0 - 9 and . , */
		return(NUM);

	if((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) /* A - Z || a - z */
		return(CHAR);

	if(ch == 33 || ch == 42 || ch == 43 || ch == 45 || ch == 47 || ch == 33) /* * + - / ! */
		return(OPERATOR);

	return(UNDEF);
}

int main(int argc, char *argv[])
{
#define MAX_USER_INPUT 100
	int ch = 0;
	unsigned int i = 0;
	chtpye_t chType = 0;
	char userInput[MAX_USER_INPUT + 1] = {'\0'};
	unsigned int userInputIndex = 0;
	char *pUserInput = NULL;
	long double ld = 0.0;
	char getout = 0;
	rpn_t calculator;

	initscr();

	if((LINES < 24) || (COLS < 80)){
		endwin();
		printf("O terminal precisa ter no minimo 80x24\n");
		return(-1);
	}

	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	set_escdelay(0);

	getout = 0;
	ld = 0.0;
	userInputIndex = 0;
	pUserInput = NULL;
	memset(userInput, 0, MAX_USER_INPUT + 1);

	startRPNCalculator(&calculator);

	while(getout != 1){
		clear();

		/* draw the screen */
		mvprintw(0, 0, "Binary operations: + - * / 'pow' 'logx'");

		mvprintw(2, 0, "Unary operations:");
		mvprintw(3, 0, "!\tFactorial");
		mvprintw(4, 0, "'sin'\tSin");
		mvprintw(5, 0, "'cos'\tCossin");
		mvprintw(6, 0, "'tg'\tTangent");
		mvprintw(7, 0, "'loge'\tExponencial log");
		mvprintw(8, 0, "'lg'\tDecimal log");
		mvprintw(9, 0, "'1/x'\tInverse");

		mvprintw(11, 0, "Stack operations:");
		mvprintw(12, 0, "'DROP'");
		mvprintw(13, 0, "'SWAP'");
		mvprintw(14, 0, "'CLSSTACK'");

		mvprintw(26, 0, "Input:");
		mvprintw(26, 7, userInput);

		mvprintw(LINES - 1, 0, "[ESC] Exit | [ENTER] Insert stack");

		mvprintw(LINES - 1, 50, "STACK:");

		for(i = 0; getStack(&calculator, i, &ld) != RPNNOK; i++){
			mvprintw(LINES - 1 - i, 57, "%d) %.20Le", i, ld);
		}
		if(i == 0)
			mvprintw(LINES - 1, 57, "<EMPTY>");

		move(26, 7 + userInputIndex);

		refresh();

		ch = getch();

		chType = whatIs(ch); /* because switch(){case '[a-zA-Z]': ... } doesn't allow functions at labels */

		switch(chType){
			case NUM:
				if(ch == ',') ch = '.';

				userInput[userInputIndex] = ch;
				userInputIndex++;
				break;

			case CHAR:
				userInput[userInputIndex] = ch;
				userInputIndex++;
				break;

			case OPERATOR:
				/* lets see if there is a number before the operator typed. strtold() help us to this */
				ld = strtold(userInput, &pUserInput);
				if((ld == HUGE_VALF || ld == HUGE_VALL || ld == 0) && errno == ERANGE){
					/* TODO: value converted erro */
				}
				if(ld != 0.0){
					if(insertStackValue(&calculator, &ld) == RPNNOK){
						/* TODO */
					}
				}
				if(insertStackOperator(&calculator, *pUserInput) == RPNNOK){
					/* TODO */
				}

				break;

			case ESC:
				getout = 1;
				break;

			case ENTER:
				ld = strtold(userInput, NULL);
				if((ld == HUGE_VALF || ld == HUGE_VALL || ld == 0) && errno == ERANGE){
					/* TODO: value converted erro */
				}

				if(insertStackValue(&calculator, &ld) == RPNNOK){
					/* TODO */
				}
				break;

			case BACKSPACE:
				if(userInputIndex == 0)
					continue;

				userInputIndex--;
				userInput[userInputIndex] = '\0';
				break;

			default:
				break;
		}
	}

	endwin();
	delwin(stdscr);

	return(0);
}
