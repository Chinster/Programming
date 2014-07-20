#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int getaddrinfo(const char *node, // hostname or IP
                const char *service, // http or port number
                const struct addrinfo *hints, // given info
                struct addrinfo **res); // fill pointer to linked list


int main(int argc, char *argv[])
{
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo; // points to results

    memset(&hints, 0, sizeof hints); // ensure struct is empy
    hints.ai_family = AF_UNSPEC; // IPv4 or IPv6 doesn't matter
    hints.ai_socktype = SOCK_STREAM; // TCP stream
    hints.ai_flags = AI_PASSIVE; // fill IP for me

    if((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }

    // servinfo points to a linked list of 1 or more struct addrinfos
    // do things

    freeaddrinfo(servinfo); // free linked list.
    return 0;
}
