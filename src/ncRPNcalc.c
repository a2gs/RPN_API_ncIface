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
		return(ESC);

	if((ch >= 48 && 57 <= ch) || ch == 44 || ch == 46) /* 0 - 9 and . , */
		return(NUM);

	if((ch >= 65 && 90 <= ch) || (ch >= 97 && 122 <= ch)) /* A - Z || a - z */
		return(CHAR);

	if(ch == 33 || ch == 42 || ch == 43 || ch == 45 || ch == 47 || ch == 33) /* * + - / ! */
		return(OPERATOR);

	return(UNDEF);
}

int main(int argc, char *argv[])
{
#define MAX_USER_INPUT 100
	int ch = 0;
	chtpye_t chType = 0;
	char userInput[MAX_USER_INPUT + 1] = {'\0'};
	unsigned int userInputIndex = 0;
	char *pUserInput = NULL;
	long double ld = 0.0;
	char getout = 0;
	rpn_t calculator;

	initscr();
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


		/* desenha a tela */
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
				userInput[userInputIndex] = '\0';
				userInputIndex--;
				break;

			default:
				break;
		}
	}

	endwin();
	delwin(stdscr);

	return(0);
}
