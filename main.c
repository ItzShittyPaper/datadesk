#include "stdlib.h"
#include "string.h"

#include "func.c"

int ch;
char wch[16];
int i = 0;
FILE *fp;

/* LE FILE OPENING */
/* le variables      */
int file_x;
int file_y;
int i2 = 0;

/* attributes lmao */
bool is_lined = false;
int line_number = 1;
int list_offset = 0;
bool is_bold = false;
bool is_underlined = false;

/* other boolean stuff */
bool is_comment_check = false;

int rec_y1;
int rec_x1;
int rec_y2;
int rec_x2;
int line_length;

char chunk[128];
int border_y;
int border_x;

char *ye;
char *ye2;
char *ye_rec;
char *ye_list;
char *ye_attr;

void commentcheck() {

  ye = strstr(chunk, "/*");
  if (ye != NULL) { is_comment_check = true; }

  ye = strstr(chunk, "*/");
  if (ye != NULL && is_comment_check == true) { is_comment_check = false; i--; }

}

void checkattrs() {

  ye = strstr(chunk, "L");
  if (ye != NULL) {is_lined = true; }

  ye = strstr(chunk, "B");
  if (ye != NULL) {is_bold = true; }

  ye = strstr(chunk, "U");
  if (ye != NULL) {is_underlined = true; }

}

void resetattrs() {

  is_lined = false;
  is_bold  = false;
  is_underlined = false;

}

int main(int argc, char *argv[]) {

  fp = fopen(argv[1], "r");
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  i = -3;

  /* parsing the .ds file */
  while(fgets(chunk, sizeof(chunk), fp) != NULL) {

    commentcheck();

    /* this is the parse routine */
    switch(i) {

      default:
        break;

      case -3:
        sscanf(chunk, "%d", &file_y);
        break;
      case -2:
        sscanf(chunk, "%d", &file_x);
        break;
      case -1:
        if (checktermsize(file_y, file_x) == 1) { fclose(fp); endwin(); return 0; }
        border_y = file_y;
        border_x = file_x;

      case 0:
        /* read the y coordinate                           */
        if (ye_rec == NULL) { sscanf(chunk, "%d", &file_y); }
        break;
      case 1:
        /* second pass: read the x coordinate              */
        sscanf(chunk, "%d", &file_x);
        break;
      case 2:

        /* these commands check for commands like /s or /r */
        ye = strstr(chunk, "/s");
        if (ye != NULL) {

          i = 2;
          checkattrs();
          break;

        }

        ye_rec = strstr(chunk, "/r");
        if (ye_rec != NULL) { i = 3; break; }

        /* lines, horizontal and vertical */
        ye = strstr(chunk, "/h");
        if (ye != NULL) { i = 6; break; }

        ye = strstr(chunk, "/v");
        if (ye != NULL) { i = 8; break; }

        ye = strstr(chunk, "/l");
        if (ye != NULL) { i = 10; break; }

        else { mvprintw(file_y + 1, file_x + 1, chunk); i = -1; break; }

      /* SENTENCE DRAWING ROUTINE */
      case 3:

        ye2 = strstr(chunk, "/e");
        if (ye2 != NULL) { i = -1; resetattrs(); break; }
        else { i = 2; }

        /* print the character / line */
        if (is_lined == true) {
	  mvprintw(file_y + 1 + i2, file_x - 1, "%d", line_number); line_number++; }

	if (is_bold == true)  { attron(A_BOLD); mvprintw(file_y + 1 + i2, file_x + 1, chunk); line_number++; }
  	  mvprintw(file_y + 1 + i2, file_x + 1, chunk);

	if (is_underlined == true)  { attron(A_UNDERLINE); mvprintw(file_y + 1 + i2, file_x + 1, chunk); line_number++; }
  	  mvprintw(file_y + 1 + i2, file_x + 1, chunk);

	attroff(A_BOLD);
	attroff(A_UNDERLINE);

        i2++;
        break;

      /* RECTANGLE DRAWING ROUTINE */
      case 4:
        sscanf(chunk, "%d", &rec_y2);
        break;
      case 5:
        sscanf(chunk, "%d", &rec_x2);
        break;
      case 6:
        ye_rec = strstr(chunk, "/e");
        rectangle(file_y + 1, file_x + 1, rec_y2 + 1, rec_x2 + 1);
        if (ye_rec != NULL) { i = -1; ye_rec = NULL; break; }

      /* HORIZONTAL LINE DRAWING ROUTINE */
      case 7:
        sscanf(chunk, "%d", &line_length);
        mvhline(file_y + 1, file_x + 1, 0, line_length);
        break;
      case 8:
        i = -1;
        break;

      /* VERTICAL LINE DRAWING ROUTINE */
      case 9:
        sscanf(chunk, "%d", &line_length);
        mvvline(file_y + 1, file_x + 1, 0, line_length);
        break;
      case 10:
        i = -1;
        break;

      /* LIST DRAWING ROUTINE */
      case 11:
        ye_list = strstr(chunk, ">");
        if (ye_list != NULL) { list_offset++; i = 10; break; }
        ye_list = strstr(chunk, "<");
        if (ye_list != NULL) { list_offset--; i = 10; break;  }
        ye_list = strstr(chunk, "/e");
        if (ye_list != NULL) { i = -1; break; }

        else {
          mvprintw(file_y + 1 + i2, file_x + 1 + list_offset, chunk);
          i = 10;
          i2++;
        }

    }
    i++;

  }

  refresh();

  /* this is the screen drawing routine                 */
  /* i kno that goto isn't a good function but it works */
  char bordertext[64];
  sprintf(bordertext, "%d", border_x); strcat(bordertext, "x"); sprintf(wch, "%d", border_y); strcat(bordertext, wch);

  state_1_loop:
  rectangle(0, 0, border_y, border_x);
  mvprintw(0, 4, argv[1]);
  mvprintw(0, getmaxx(stdscr) - 10, bordertext);

  refresh();
  ch = getch();

  /* PARSE KEY PRESSES */
  switch (ch) {

    case KEY_F(12):
      mvprintw(0, 4, "Quitting...");
      endwin();
      fclose(fp);
      return 0;

  }

  goto state_1_loop;
  endwin();
  fclose(fp);

  return 0;

}
