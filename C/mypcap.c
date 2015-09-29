#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pcap/pcap.h>
#include <errno.h>

void handle_packet(u_char *user, const struct pcap_pkthdr *h, const u_char *bytes) {
    bpf_u_int32 pktlen = h->len;
    /*
    for (int i = 0; i < pktlen; i++) {
        printf("█", bytes[i]);
    }
    */
    //printf("\n");
}

int main(int argc, char *argv[])
{
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *capture = pcap_create(NULL, errbuf);
    if (!capture) {
        fprintf(stderr, "Capture create failed: %s\n", errbuf);
        return -1;
    }

    if (pcap_activate(capture) != 0) {
        printf("activate: %m\n");
    }

    pcap_loop(capture, -1, &handle_packet, "me");
    pcap_close(capture);
    return 0;
}
