#ifndef starting_header_h
#define starting_header_h

#include "../headers/server_structures.h"

struct serverStructure createServer(int protocol, int backlog);
void listeningForRequest(struct serverStructure, char*, int);

#endif