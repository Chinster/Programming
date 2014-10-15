struct addrinfo {
    int             ai_flags;
    int             ai_family;      // AF_INET, AF_INET6, AF_UNSPEC
    int             ai_socktype;
    int             ai_protocol;
    size_t          ai_addrlen;
    struct sockaddr *ai_addr;
    char            *ai_canonname;

    struct addrinfo *ai_next;       //linked list
};

struct sockaddr {
    unsigned short  sa_family;      // address family, AF_XXXX
    char            sa_data[14];    // 14 bytes of protocol addresses; dest addr+port
};

// IPv4 Only.
// parallel struct with sockaddr. sockaddr_in and sockaddr can be casted to each other.
struct sockaddr_in {
    short int           sin_family;  // address family, AF_INET
    unsigned short int  sin_port;    // Port number. Network Byte Order. htons()
    struct in_addr      sin_addr;    // Internet address
    unsigned char       sin_zero[8]; // padding
};


// IPv4 Address.
struct in_addr {
    uint32_t s_addr; // 32-bit int in Network Byte Order
};

// IPv6 Only.
struct sockaddr_in6 {
    u_int16_t       sin6_family;    //address family, AF_INET6
    u_int16_t       sin6_port;      // port number, Network Byte Order
    u_int32_t       sin6_flowinfo;  // IPv6 flow information
    struct in6_addr sin6_addr;      // IPv6 address
    u_int32_t       sin6_scope_id;  // Scrope ID
};

//IPv6 Address.
struct in6_addr {
    unsigned char   s6_addr[16];    // Ipv6 address
};

// Large enough to hold both IP addr structures
struct sockaddr_storage {
    sa_family_t ss_family;  // address family

    // padding, implementation specific
    char        _ss_pad1[_SS_PAD1SIZE];
    int64_t     _ss_align;
    char        _ss_pad2[_SS_PAD2SIZE];
};

struct timeval {
    int tv_sec;
    int tv_usec;
};
