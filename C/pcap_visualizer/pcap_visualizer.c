#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/pcap.h>
#include <ncurses.h>
#include <errno.h>
#include <signal.h>

pcap_t *capture = NULL;

void sigint_handler(int x)
{
    endwin();
    if (capture)
        pcap_breakloop(capture);
}

void handle_packet(u_char *user, const struct pcap_pkthdr *h,
        const u_char *bytes)
{
    bpf_u_int32 pktlen = h->len;
    if (pktlen > LINES)
        pktlen = LINES;

    attron(COLOR_PAIR(1));
    for (int i = 0; i < LINES; i++)
        mvaddch(i, 40, ' ');

    attron(COLOR_PAIR(2));
    for (int i = 0; i < pktlen; i++)
        mvaddch(i, 40, ' ');
    refresh();
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
    curs_set(0); // It doesn't matter if this fails
}

/* Initialize enough pkt_visuals for screen size */
void init_pktvisual(void)
{
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sigint_handler);

    refresh();
    char errbuf[PCAP_ERRBUF_SIZE];
    capture = pcap_create(NULL, errbuf);
    if (!capture) {
        fprintf(stderr, "Capture create failed: %s\n", errbuf);
        return -1;
    }

    if (pcap_activate(capture) != 0) {
        printf("activate: %m\n");
    }

    init_win();
    init_pktvisual();
    pcap_loop(capture, -1, &handle_packet, NULL);
    pcap_close(capture);
    endwin();
    return 0;
}
