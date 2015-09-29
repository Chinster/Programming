#include <ncurses.h>
#include <string.h>

int main()
{
    char mesg[] = "Input: ";
    char str[80];
    int row, col;

    initscr();
    attron(A_BLINK);

    getmaxyx(stdscr, row, col);
    mvprintw(row / 2, (col - strlen(mesg)) / 2, "%s", mesg);

    getstr(str);

    mvprintw(LINES - 2, 0, "You Entered: %s", str);
    getch();
    endwin();

    return 0;
}
