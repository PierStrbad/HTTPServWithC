#ifndef Server_h
#define Server_h

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <netdb.h>
#include <curl/curl.h>
#include <stdbool.h>
#include <dirent.h>
#include <errno.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/wait.h>

#define MAX_REQUEST_SIZE 35000

struct Server 
{
    int socket;
    int maxClientNumber[10];
    struct sockaddr_in address;
};

struct Response 
{
    char *string;
    size_t size;
};

struct ClientSocketDetails 
{
    int socket;
    char method[16];
    char route[256];
    char dir[256];
    char reguestBuffer[MAX_REQUEST_SIZE];
};

#endif