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
	DEL,
	UNDEF
}chtpye_t;

chtpye_t whatIs(int ch)
{
	if(ch == ESC_KEY)
		return(ESC);

	if(ch == KEY_ENTER || ch == '\n')
		return(ENTER);

	if(ch == KEY_BACKSPACE)
		return(BACKSPACE);

	if((ch >= 48 && ch <= 57) || ch == 44 || ch == 46) /* 0 - 9 and . , */
		return(NUM);

	if((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) /* A - Z || a - z */
		return(CHAR);

	if(ch == 33 || ch == 42 || ch == 43 || ch == 45 || ch == 47 || ch == 33) /* * + - / ! */
		return(OPERATOR);

	if(ch == KEY_DC)
		return(DEL);

	return(UNDEF);
}

chtpye_t isStringOrNumber(char *str)
{
	chtpye_t init = UNDEF;
	chtpye_t walker = UNDEF;
	unsigned int i = 0;

	init = whatIs(str[0]);

	for(i = 1; str[i] != '\0'; i++){
		walker = whatIs(str[i]);

		if(walker == OPERATOR) /* Numbers with ending operator is allowed (like "98347.598735/". (strtold() will help us to this) */
			walker = NUM;

		if(init != walker)
			return(UNDEF);
	}

	return(init);

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
	chtpye_t inputed = UNDEF;
	WINDOW *operatiosWin = NULL, *stackWin = NULL;
	rpn_t calculator;
	int stackMaxLines = 0;

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
	stackMaxLines = LINES-1;
	memset(userInput, '\0', MAX_USER_INPUT + 1);

	startRPNCalculator(&calculator);

	operatiosWin = newwin(17, 50, 0, 0);
	stackWin     = newwin(stackMaxLines, 70, 0, 51);

	while(getout != 1){
		clear();
		wclear(stackWin);

		/* draw the screen */
		box(operatiosWin, 0, 0);
		box(stackWin,     0, 0);
		mvwprintw(operatiosWin, 1, 1, "Binary operations: + - * / 'powxy' 'logxy' 'Rxy'");

		mvwprintw(operatiosWin, 3, 1, "Unary operations:");
		mvwprintw(operatiosWin, 4, 1, "!\tFactorial");
		mvwprintw(operatiosWin, 5, 1, "'sin'\tSin");
		mvwprintw(operatiosWin, 6, 1, "'cos'\tCossin");
		mvwprintw(operatiosWin, 7, 1, "'tg'\tTangent");
		mvwprintw(operatiosWin, 8, 1, "'loge'\tExponencial log");
		mvwprintw(operatiosWin, 9, 1, "'lg10'\tDecimal log");
		mvwprintw(operatiosWin, 10, 1, "'inv'\tInverse (1/x)");
		mvwprintw(operatiosWin, 11, 1, "'pow2x'\tPower 2^x");
		mvwprintw(operatiosWin, 12, 1, "'R'\tRoot (2)");

		mvwprintw(operatiosWin, 12, 1, "Stack operations:");
		mvwprintw(operatiosWin, 13, 1, "'DROP'");
		mvwprintw(operatiosWin, 14, 1, "'SWAP'");
		mvwprintw(operatiosWin, 15, 1, "'CLSSTACK'");

		mvwprintw(stackWin, stackMaxLines - 2, 1, "STACK:");

		for(i = 0; getStackLIFO(&calculator, i, &ld) != RPNNOK; i++){
			mvwprintw(stackWin, stackMaxLines - 2 - i, 8, "%d) %.20Lg", i, ld);
		}
		if(i == 0)
			mvwprintw(stackWin, stackMaxLines - 2, 8, "<EMPTY>");

		refresh();
		wrefresh(stackWin);

		mvprintw(LINES - 5, 0, "[ESC] Exit");
		mvprintw(LINES - 4, 0, "[DEL] Clear input");
		mvprintw(LINES - 3, 0, "[ENTER] Insert stack");

		mvprintw(LINES - 1, 0, "Input:");
		mvprintw(LINES - 1, 7, userInput);

		move(LINES - 1, 7 + userInputIndex);

		wrefresh(operatiosWin);
		wrefresh(stackWin);
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
				if(insertStackOperator(&calculator, pUserInput) == RPNNOK){
					/* TODO */
				}

				userInputIndex = 0;
				memset(userInput, '\0', MAX_USER_INPUT + 1);

				break;

			case ESC:
				getout = 1;
				break;

			case ENTER:
				inputed = isStringOrNumber(userInput);

				if(inputed == NUM){
					/* if userInput a number ... */
					ld = strtold(userInput, NULL);
					if((ld == HUGE_VALF || ld == HUGE_VALL || ld == 0) && errno == ERANGE){
						/* TODO: value converted erro */
						continue;
					}

					if(insertStackValue(&calculator, &ld) == RPNNOK){
						/* TODO */
					}
				}else if(inputed == CHAR){
					if      (strcasecmp(userInput, "DROP"    ) == 0){
						drop(&calculator);
					}else if(strcasecmp(userInput, "SWAP"    ) == 0){
						swap(&calculator);
					}else if(strcasecmp(userInput, "CLSSTACK") == 0){
						cleanStack(&calculator);
					}else{
						/* Operators */
					}
				}else{
				}

				userInputIndex = 0;
				memset(userInput, '\0', MAX_USER_INPUT + 1);

				break;

			case DEL:
				userInputIndex = 0;
				memset(userInput, '\0', MAX_USER_INPUT + 1);

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

	delwin(operatiosWin);
	delwin(stackWin);
	delwin(stdscr);
	endwin();

	return(0);
}
