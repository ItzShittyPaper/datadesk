#include "ncurses.h"
#include "func.h"

void rectangle(int y1, int x1, int y2, int x2) {

    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);

}

int reporterror() {

  mvprintw(0, 4, "                                 ");
  mvprintw(0, 4, "Syntax error!");
  endwin();
  return 1;

}

int checktermsize(int req_y, int req_x) {

	int ncurses_max_y;
	int ncurses_max_x;

	/* check le terminal size */
	getmaxyx(stdscr, ncurses_max_y, ncurses_max_x);
	if(ncurses_max_x < req_x) { endwin(); printf("Your Terminal is too small, exiting... \n"); return 1; }
	else if(ncurses_max_y < req_y) { endwin(); printf("Your Terminal is too small, exiting... \n"); return 1; }
	else { return 0; }

}
