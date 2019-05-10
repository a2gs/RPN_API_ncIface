#include <stdio.h>
#include <ncurses.h>

#include <librpn.h>

#define ESC_KEY 27

typedef enum{
	CHAR = 1,
	OPERATOR,
	UNDEF
}chtpye_t;

chtpye_t whatIs(int ch)
{

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
