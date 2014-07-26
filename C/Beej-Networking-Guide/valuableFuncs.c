htons(); // host to network short
htonl(); // host to network long
ntohs();
ntohl();

int getaddrinfo(const char *node,
        const char *service,
        const struct addrinfo *hints,
        struct addrinfo **res);
int socket(int domain, int type, int protocol);
int bind(int sockfd, struct sockaddr *my_addr, int addrlen); // Unless you don't care what port you are on client
int connect(int sockfd, struct sockaddr *serv_addr, int addrlen);
int listen(int sockfd, int backlog); // backlog=maxQueuedConnections
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
int send(int sockfd, const void *msg, int len, int flags);
int recv(int sockfd, void *buf, int len, int flags);
int sendto(int sockfd, const void *msg, int len, unsigned int flags, const struct sockaddr *to, socklen_t tolen);
int recvfrom(int sockfd, void *buf, int len, unsigned int flags, struct sockaddr *from, int *fromlen);
int close(int sockfd);
int shutdown(int sockfd, int how);

int getpeername(int sockfd, struct sockaddr *addr, int *addrlen); // addr holds info.
int gethostname(char *hostname, size_t size); // returns computer name? into hostname
gethostbyname();


//CPU intensive non-blocking socket.
fcntl(int sockfd, F_SETFL, O_NONBLOCK);
// monitor a socket, quite slow. see libevent for alternatives
int select(int numfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);


