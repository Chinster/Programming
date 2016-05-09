/**
 * Create an ncurses window. These emulate a windowing system.
 */
#include <ncurses.h>

WINDOW *update_win(WINDOW **win, int height, int width, int starty, int startx);

int main(int argc, char *argv[])
{
    WINDOW *my_win;
    initscr();
    cbreak();

    keypad(stdscr, TRUE);

    int height = 3;
    int width = 10;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;
    printw("Press F1 to exit");
    refresh();

    my_win = newwin(height, width, starty, startx);
    box(my_win, 0, 0);
    wrefresh(my_win);

    int ch;
    while ((ch = getch()) != KEY_F(1)) {
        switch (ch) {
            case KEY_LEFT:
                update_win(&my_win, height, width, starty, startx--);
                break;
            case KEY_RIGHT:
                update_win(&my_win, height, width, starty, startx++);
                break;
            case KEY_UP:
                update_win(&my_win, height, width, starty--, startx);
                break;
            case KEY_DOWN:
                update_win(&my_win, height, width, starty++, startx);
                break;
        }
    }

    endwin();
    return 0;
}

WINDOW *update_win(WINDOW **win, int height, int width, int starty, int startx)
{
    wborder(*win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(*win);
    delwin(*win);

    *win = newwin(height, width, starty, startx);
    box(*win, 0, 0);

    wrefresh(*win);

    return *win;
}
