#include "../headers/server_structures.h"
#include "../headers/response_header.h"

pthread_t thread_pool[THREAD_POOL_SIZE];
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition_var = PTHREAD_COND_INITIALIZER;

void* thread_function(void *);

struct serverStructure createServer(int protocol, int backlog) 
{
    struct serverStructure server;
    server.address.sin_family = AF_INET;
    server.address.sin_port = htons(PORT);
    server.address.sin_addr.s_addr = htonl(INADDR_ANY);

    check((server.socket = socket(PF_INET, SOCK_STREAM, protocol)), "(Log) Failed to connect socket", 0);
    check(bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)), "(Log) Failed to bind socket", 0);
    check(listen(server.socket, backlog), "(Log) Failed to start listening", 0);
    
    char hostBuffer[NI_MAXHOST], serviceBuffer[NI_MAXSERV];
    int error = getnameinfo((struct sockaddr *)&server.address, sizeof(server.address), hostBuffer, sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), 0);
    
    if (error != 0) {
        printf("(Log) Error: %s\n", gai_strerror(error));
        exit(1);
    }

    printf("\n(Log) Server is listening on http://%s:%d/\n\n", hostBuffer ,ntohs(server.address.sin_port));
    return server;
}

node_t* head = NULL;
node_t* tail = NULL;

void enqueue(struct Client* client) 
{
    node_t *newnode = malloc(sizeof(node_t));
    newnode->client = client;
    newnode->next = NULL;
    if (tail == NULL) {
        head = newnode;
    } else {
        tail->next = newnode;
    }
    tail = newnode;
}

struct Client* dequeue() 
{
    if (head == NULL) {
        return NULL;
    } else {
        struct Client* result = head->client;
        node_t *temp = head;
        head = head->next;
        if (head == NULL) {
            tail = NULL;
        }
        free(temp);
        return result;
    }
}

int acceptingRequest(struct serverStructure server)
{
    int socket = 0;
    int address_length = sizeof(server.address);
    if ((socket = accept(server.socket, (struct sockaddr *)&server.address, (socklen_t *)&address_length)) == -1) {
        return -1;
    }
    return socket;
}

void* thread_function(void *arg) 
{
    while(true)
    {
        struct Client* client;
        pthread_mutex_lock(&lock);
        if ((client = dequeue()) == NULL) {
            pthread_cond_wait(&condition_var, &lock);
            // try again
            client = dequeue();
        }
        pthread_mutex_unlock(&lock);

        if (client != NULL) {
            constructResponse(client);
        }
    }
}

void listeningForRequest(struct serverStructure server, char* dir, int fd) 
{
    for (int i = 0; i < THREAD_POOL_SIZE; i++) {
        pthread_create(&thread_pool[i], NULL, &thread_function, NULL);
        // pthread_join(thread_pool[i], NULL);
    }

    int clientSocket = 0;
    // Waiting for a client request
    while(true)
    {
        dprintf(fd, "\n===== WAITING =====\n");
        check((clientSocket = acceptingRequest(server)), "(Log) Failed to accept client request", fd);
        
        struct Client* pclient = (struct Client*)malloc(sizeof(struct Client));
        pclient->fd = fd;
        strcpy(pclient->dir, dir);
        pclient->socket = clientSocket;
        pthread_mutex_lock(&lock);
        enqueue(pclient);
        pthread_cond_signal(&condition_var);
        pthread_mutex_unlock(&lock);
    }
}