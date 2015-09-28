#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/pcap.h>
#include <ncurses.h>
#include <errno.h>
#include <signal.h>
#include <sys/time.h>

#define check(A, M, args...) \
    if (!(A)) {              \
        perror(M, ##args);   \
        goto error;          \
    }
pcap_t *capture = NULL;
int refresh_ready = false;

void sigint_handler(int sig)
{
    endwin();
    if (capture)
        pcap_breakloop(capture);
}

void sigalrm_handler(int sig)
{
    refresh_ready = true;
}

void handle_packet(u_char *user, const struct pcap_pkthdr *h,
        const u_char *bytes)
{
    static int col = 0;
    bpf_u_int32 pktlen = h->len;
    if (pktlen > LINES)
        pktlen = LINES;

    if (col >= COLS) {
        col = 0;
    }

    attron(COLOR_PAIR(1));
    for (int i = 0; i < LINES; i++)
        mvaddch(i, col, ' ');

    attron(COLOR_PAIR(2));
    for (int i = 0; i < pktlen; i++)
        mvaddch(i, col, ' ');
    col++;


    if (refresh_ready) {
        refresh();
        refresh_ready = false;
    }
}

/* Initialize ncurses screen */
void init_win(void)
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal doesn't support colors\n");
        exit(1);
    }
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_WHITE);
    curs_set(0); // It doesn't matter if this fails, removes cursor
    refresh();
}

int init_pcap(void)
{
    char errbuf[PCAP_ERRBUF_SIZE];
    capture = pcap_create(NULL, errbuf);
    check(capture != NULL, "pcap_create");
    check(pcap_activate(capture) == 0, "pcap_activate");

    return 0;
error:
    return -1;
}

int init_sighandlers(void)
{
    struct sigaction sigint_action = {
        .sa_handler = &sigint_handler,
        .sa_flags = SA_NODEFER,
    };
    check(sigemptyset(&sigint_action.sa_mask) != -1, "sigemptyset");
    check(sigaction(SIGINT, &sigint_action, NULL) != -1, "sigaction");

    struct sigaction sigalrm_action = {
        .sa_handler = &sigalrm_handler,
        .sa_flags = SA_NODEFER,
    };
    check(sigemptyset(&sigalrm_action.sa_mask) != -1, "sigemptyset");
    check(sigaction(SIGVTALRM, &sigalrm_action, NULL) != -1, "sigaction");

    struct itimerval itimer = {
        .it_interval = { .tv_sec = 0, .tv_usec = 30000 },
        .it_value = { .tv_sec = 0, .tv_usec = 10000 },
    };
    check(setitimer(ITIMER_VIRTUAL, &itimer, NULL) != -1, "setitimer");

    return 0;
error:
    return -1;
}

int main(int argc, char *argv[])
{
    if (init_pcap() == -1)
        return -1;
    init_win();
    if (init_sighandlers() == -1)
        return -1;

    pcap_loop(capture, -1, &handle_packet, NULL);

    pcap_close(capture);
    endwin();
    return 0;
}
