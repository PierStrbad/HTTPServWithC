#include "./Server.h"

#define PORT 8080

int server_socket = 0;
int fd = 0;
int clientCounter = 0;

struct Server server_constructor(int adreesFamily, int type, int protocol, int port, int backlog)
{
    struct Server server;
    server.address.sin_family = adreesFamily;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(INADDR_ANY);

    server.socket = socket(adreesFamily, type, protocol);
    if (server.socket < 0)
    {
        perror("Failed to connect socket...\n");
        exit(-1);
    }

    if (bind(server.socket, (struct sockaddr *)&server.address, sizeof(server.address)) < 0)
    {
        perror("Failed to bind socket...\n");
        exit(-1);
    }

    if (listen(server.socket, backlog) < 0)
    {
        perror("Failed to start listening...\n");
        exit(-1);
    }
    
    socklen_t length;
    int result = getsockname(server.socket, (struct sockaddr*) &server.address, &length);
    
    if (result < 0) {
        printf("Error: %s\n", gai_strerror(result));
        exit(-1);
    }
    printf("\nServer is listening on http://localhost:%d/\n\n", port);
    
    return server;
}

int establishingFilePathAndDataType(char *filePath, char *method, char *MIMEtype) 
{
    // printf("\t- establishingFilePathAndDataType()\n");
    if (strcmp(method, "GET") != 0)
    {
        printf("%s is an unacceptable method...\n", method);
        return -1;
    }

    ssize_t filePathLength = strlen(filePath);
    for (int i = 2; i < (int)filePathLength; i++) {
        if (filePath[i] == '.') { 
            snprintf(MIMEtype, 16, "%s", &filePath[i]);
            break;
        }
    }
    if(strlen(MIMEtype) < 1)
    {
        if (filePath[filePathLength-1] == '/')
            strcat(filePath, "index.html");
        else
            strcat(filePath, "/index.html");
        snprintf(MIMEtype, 16, ".html");
        filePath[strlen(filePath) + 1] = '\0';
    }
    
    if (access(filePath, F_OK) != 0) {
        printf("(Log) File does not exist. Re-routing client to not found...\n\n");
        snprintf(filePath, 256, "hrmremake/browser/not-found/index.html");
        snprintf(MIMEtype, 16, ".html");
    }

    return 0;

    // ==================================== //
}

int createResponse(char *fullPath, char *MIMEtype, char **response_buffer) 
{
    // printf("\t- createResponse()\n");
    FILE *file = fopen(fullPath, "r");
    char *file_buffer = NULL;

    if (file == NULL)
    {
        size_t problem_response_size = strlen("HTTP/1.1 500 Problem\r\n\r\n");
        *response_buffer = malloc(problem_response_size+1);
        if (*response_buffer == NULL) {
            fprintf(stderr, "Failed to allocate memory...\n");
            dprintf(fd, "Failed to allocate memory...\n");
            return -1;
        }

        strncpy(*response_buffer, "HTTP/1.1 500 Problem\r\n\r\n", problem_response_size);
        (*response_buffer)[problem_response_size] = '\0';
        return 0;
    }
    else
    {
        char response_setup_string[256];
        if (strcmp(MIMEtype, ".html") == 0) {
            snprintf(response_setup_string, sizeof(response_setup_string), "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: keep-alive\r\n\r\n");
        }
        else if (strcmp(MIMEtype, ".css") == 0) {
            snprintf(response_setup_string, sizeof(response_setup_string), "HTTP/1.1 200 OK\r\nContent-Type: text/css; charset=UTF-8\r\nConnection: keep-alive\r\n\r\n");
        }
        else if (strcmp(MIMEtype, ".js") == 0) {
            snprintf(response_setup_string, sizeof(response_setup_string), "HTTP/1.1 200 OK\r\nContent-Type: text/javascript; charset=UTF-8\r\nConnection: keep-alive\r\n\r\n");
        }

        size_t response_setup_size = strlen(response_setup_string);
        
        fseek(file, 0, SEEK_END);
        size_t file_size = ftell(file);
        fseek(file, 0, SEEK_SET);
        
        file_buffer = (char *)malloc(file_size + 1);
        if (file_buffer == NULL)
        {
            fprintf(stderr, "Failed to allocate memory...\n");
            dprintf(fd, "Failed to allocate memory...\n");
            fclose(file);
            free(file_buffer);
            return -1;
        }

        ssize_t read_bytes = fread(file_buffer, 1, file_size, file);
        if (read_bytes < 0) {
            
            fprintf(stderr, "Failed to read data from file...\n");
            dprintf(fd, "Failed to read data from file...\n");
            fclose(file);
            free(file_buffer);
            return -1;
        }
        file_buffer[file_size] = '\0';
        fclose(file);

        size_t new_response_buffer_size = response_setup_size + file_size + 1;
        *response_buffer = (char *)malloc(new_response_buffer_size);
        if (*response_buffer == NULL) {
            fprintf(stderr, "Failed to allocate memory...\n");
            dprintf(fd, "Failed to allocate memory...\n");
            free(file_buffer);
            return -1;
        }
        strcpy(*response_buffer, response_setup_string);
        strcat(*response_buffer, file_buffer);

        free(file_buffer);
    }

    return 0;
}

int writingAndSendingAResoponse(int socket, char* filePath, char* MIMEtype) 
{
    // printf("\t- writingAndSendingAResoponse()\n");
    char *response_buffer = NULL;
    if(createResponse(filePath, MIMEtype, &response_buffer) == -1) {
        return -1;
    }
    
    if (response_buffer == NULL) {
        fprintf(stderr, "Failed to create response...\n");
        dprintf(fd, "Failed to create response...\n");
        return -1;
    }

    if (send(socket, response_buffer, strlen(response_buffer), 0) < 0)
    {
        fprintf(stderr, "Failed to send response...\n");
        dprintf(fd, "Failed to send response...\n");
        return -1;
    }

    free(response_buffer);
    return 0;
}

int sendResponse(int socket, char* method, char* route)
{
    // printf("\t- sendResponse()\n");
    char filePath[512];
    char MIMEtype[16];
    snprintf(filePath, sizeof(filePath), "%s", route);

    if(establishingFilePathAndDataType(filePath, method, MIMEtype) == -1) 
    {
        fprintf(stderr, "Failed to establish file path and data type...\n");
        dprintf(fd, "Failed to establish file path and data type...\n");
        return -1;
    }
    if(writingAndSendingAResoponse(socket, filePath, MIMEtype) == -1) {
        return -1;
    }
    return 0;
}

void* reciveAndSendData(struct ClientSocketDetails* client) 
{
    // printf("\t- reciveAndSendData()\n");
    if (client == NULL) {
        printf("The client is empty...\n");
        return NULL;
    }

    ssize_t recieved_bytes = recv(client->socket, client->reguestBuffer, MAX_REQUEST_SIZE - 1, 0);
    if (recieved_bytes < 0)
    {
        fprintf(stderr, "Failed to read reguestBuffer to socket...\n");
        dprintf(fd, "Failed to read reguestBuffer to socket...\n");
        return NULL;
    }
    client->reguestBuffer[recieved_bytes] = '\0';

    dprintf(fd, "%s\n", client->reguestBuffer);
    sscanf(client->reguestBuffer, "%s %s", client->method, client->route);
    client->method[strlen(client->method) + 1] = '\0';
    client->route[strlen(client->route) + 1] = '\0';

    ssize_t dirLength = strlen(client->dir);
    ssize_t routeLength = strlen(client->route);

    char* temp_route = (char *)malloc(routeLength + dirLength + 1);
    if (temp_route == NULL) {
        printf("(Log) Failed to allocate memory using malloc for temp_route...\n");
        return NULL;
    }

    strcpy(temp_route, client->dir);
    strcat(temp_route, client->route);
    temp_route[routeLength + dirLength] = '\0';
    strcpy(client->route, temp_route);

    dprintf(fd, "Request accepted, sending response...\n");
    if(sendResponse(client->socket, client->method, client->route) == -1) {
        printf("Failed to send response to client...\n");
        dprintf(fd, "Failed to send response to client...\n");
        free(temp_route);
        return NULL;
    }
    free(temp_route);
    return NULL;
}

int reciveAndSendDataOnSeparateThread(struct ClientSocketDetails* client) 
{   
    pthread_t thread;
    int result = pthread_create(&thread, NULL, reciveAndSendData, client);
    if (result != 0) {
        fprintf(stderr, "Failed to create thread. Error code: %d\n", result);
        dprintf(fd, "Failed to create thread. Error code: %d\n", result);
        return -1;
    }

    pthread_join(thread, NULL);
    return 0;
}

/* // ============================= // /*
    THIS NEEDS A LOT OF WORK!!!
*/ // ============================= // */

int acceptIncommingConnections(struct Server* server, ssize_t address_length, char* dir) 
{
    int client_socket = 0;
    if ((client_socket = accept(server->socket, (struct sockaddr*)&server->address, (socklen_t *)&address_length)) == -1)
    {
        fprintf(stderr, "Failed to accept client...\n");
        dprintf(fd, "Failed to accept client...\n");
        return -1;
    }

    struct ClientSocketDetails* client = (struct ClientSocketDetails*)malloc(sizeof(struct ClientSocketDetails));
    if (client == NULL) {
        printf("(Log) Failed to allocate memory using malloc for client dets\n");
        return -1;
    }
    client->socket = client_socket;
    strcpy(client->dir, dir);

    ssize_t recieved_bytes = recv(client->socket, client->reguestBuffer, MAX_REQUEST_SIZE - 1, 0);
    if (recieved_bytes < 0)
    {
        fprintf(stderr, "Failed to read reguestBuffer to socket...\n");
        dprintf(fd, "Failed to read reguestBuffer to socket...\n");
        free(client);
        return -1;
    }
    client->reguestBuffer[recieved_bytes] = '\0';

    dprintf(fd, "%s\n", client->reguestBuffer);
    sscanf(client->reguestBuffer, "%s %s", client->method, client->route);
    client->method[strlen(client->method) + 1] = '\0';
    client->route[strlen(client->route) + 1] = '\0';

    // New client connected
    if (strcmp(client->route, "/")) {
        printf("Serving client number %d on socket: %d\n", clientCounter, client_socket);
        clientCounter++;
        free(client);
    }

    if (reciveAndSendDataOnSeparateThread(client) == -1) {
        return -1;
    }

    free(client);
    close(client_socket);
    return 0;
}

void handle_sigint(int sig) {
    printf("\n(Log) Exiting program\n");
    exit(0);
}

void cleanup() {
    printf("(Log) End of session\n");
    printf("(Log) Starting the cleanup\n");
    close(fd);
    close(server_socket);
}

int main (int argc, char **argv) 
{
    atexit(cleanup);

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(-1);
    }
    if (argc < 2) {
        printf("Missing project build directory...\n");
        exit(-1);
    }
    DIR *dir = opendir(argv[1]);
    if (dir) {
        printf("\nSuccessfully located the project build directory...\n");
        closedir(dir);
    } else {
        printf("Failed to locate/open project build directory...\n");
        exit(-1);
    }

    if ((fd = open("./logs/logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        fprintf(stderr, "Cannot open log file...\n");
        exit(-1);
    }

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, PORT, 10);
    server_socket = server.socket;

    ssize_t address_length = sizeof(server.address);
    
    // Waiting for a client request
    while(true)
    {
        dprintf(fd, "\n===== WAITING =====\n");
        dprintf(fd, "Waiting for client request...\n\n");

        if (clientCounter > 10) {
            printf("Reached maximum number of connected clients!\n");
            break;
        }
        else {
            if (acceptIncommingConnections(&server, address_length, argv[1]) == -1) {
                printf( "(Log) Failed to accept the connection...\n");
                exit(-1);
            }
        }
    }
    exit(0);
}
