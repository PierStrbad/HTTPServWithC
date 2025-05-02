#ifndef starting_header
#define starting_header

#include "../headers/server_structures.h"

struct serverStructure createServer(int protocol, int backlog);
void listeningForRequest(struct serverStructure, char*, int);
int acceptingRequest(struct serverStructure);

#endif