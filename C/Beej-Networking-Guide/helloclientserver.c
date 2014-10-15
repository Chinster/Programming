#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include <sys/types.h> // Used by listen()
#include <sys/socket.h>


#define PORT "5280" // Port to connect to

#define BACKLOG 10

void *get_in_addr(struct sockaddr *sa);

int main(int argc, char *argv[])
{
    return 0;
}

/* Returns an IPv4 or IPv6 address based on struct.
 */
void *get_in_addr(struct sockaddr *sa)
{
    // Check if IPv4
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6 *)sa)->sin6_addr);
}
