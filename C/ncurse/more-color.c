#include <stdlib.h>
#include <ncurses.h>

int main()
{
    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal doesn't support colors\n");
        return 1;
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_WHITE);

    attron(COLOR_PAIR(1));
    mvaddch(40, 40, ' ');
    attroff(COLOR_PAIR(1));
    move(0, 0);

    printw("Type any char to see it in bold\n");
    int ch = getch();

    if (ch == KEY_F(1)) {
        printw("F1 key pressed");
    } else {
        printw("The pressed key is ");
        attron(A_BOLD);
        printw("%c", ch);
        attroff(A_BOLD);
    }

    refresh();
    getch();
    endwin();
    return 0;
}
