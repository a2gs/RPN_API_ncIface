#include <stdio.h>
#include <ncurses.h>

#include <librpn.h>

#define ESC_KEY 27

typedef enum{
	NUM = 1,
	CHAR,
	OPERATOR,
	UNDEF
}chtpye_t;

chtpye_t whatIs(int ch)
{
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
	int ch = 0;
	chtpye_t chType = 0;

	initscr();
	keypad(stdscr, TRUE);
	cbreak();
	noecho();
	set_escdelay(0);



	while(1){
		clear();


		/* desenha a tela */
		refresh();

		ch = getch();

		chType = whatIs(ch); /* because switch(){case} doesn't allow functions at labels */

		switch(chType){
			case NUM:
				break;

			case CHAR:
				break;

			case OPERATOR:
				break;

			default:
				break;
		}
	}

	endwin();
	delwin(stdscr);

	return(0);
}
