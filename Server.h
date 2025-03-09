#ifndef Server_h
#define Server_h

#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>

struct Server 
{
    int domain;
    int service;
    int protocol;
    u_long interface;
    int port;
    int backlog;
    int socket;
    char *websiteDirectoryPath;

    struct sockaddr_in address;
    void (*launch)(struct Server *server);
};

struct Response 
{
    char *string;
    size_t size;
};

struct Server server_constructor(int domain, int service, int protocol, u_long interface, int port, int backlog, char *websiteDirectoryPath, void (*launch)(struct Server *server));

#endif