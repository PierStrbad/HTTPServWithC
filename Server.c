#include "Server.h"

#define PORT 8080

int server_socket = 0;
int fd = 0;

struct Server server_constructor(int domain, int type, int protocol, char* ip, 
    int port, int backlog, char* websiteDirectoryPath)
{
    struct Server server;

    server.ip = ip;
    server.port = port;
    server.backlog = backlog;
    server.websiteDirectoryPath = websiteDirectoryPath;

    server.address.sin_family = domain;
    server.address.sin_port = htons(server.port);
    server.address.sin_addr.s_addr = htonl(INADDR_ANY);

    server.socket = socket(PF_INET, type, protocol);
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

    if (listen(server.socket, server.backlog) < 0)
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
    printf("\nServer is listening on http://localhost:%d/\n\n", server.port);
    
    return server;
}

bool establishingFilePathAndDataType(char *filePath, char *method, char *route, char *MIMEtype, size_t dir_path_size) 
{   
    if (strcmp(method, "GET") != 0)
    {
        printf("%s is an unacceptable method...\n", method);
        return false;
    }

    size_t route_length = strlen(route);
    size_t index_size = strlen("/index.html");
    int index = 0, slashIndex = 0;

    for (int i = 0; i < route_length; i++) 
    {
        if (route[i] == '.') { index = i; break; }
        if (route[i] == '/') { slashIndex = i; }
    }
    if (index > 0)
    {
        snprintf(MIMEtype, 16, "%s", &route[index]);
        if (strcmp(&route[slashIndex], "/not_found.css") == 0) {
            strncpy(filePath + dir_path_size, "/not-found/not_found.css", 256 - strlen(filePath) - 1);
            filePath[strlen(filePath) + 1] = '\0';
        }
        else if (strcmp(MIMEtype, ".css") == 0) {
            strncpy(filePath + dir_path_size, route, 256 - strlen(filePath) - 1);
            filePath[strlen(filePath) + 1] = '\0';
        }
        else if (strcmp(MIMEtype, ".js") == 0) {
            strncpy(filePath + dir_path_size, route, 256 - strlen(filePath) - 1);
            filePath[strlen(filePath) + 1] = '\0';
        }
    }
    else 
    {   
        snprintf(MIMEtype, 16, ".html");
        if (strcmp(route, "/")) {
            strcpy(filePath + dir_path_size, "/index.html");
        }
        else {
            char routeWithIndex[index_size + route_length + 8];
            strcpy(routeWithIndex, route);
            strcpy(routeWithIndex + route_length, "/index.html");
            routeWithIndex[index_size + route_length + 1] = '\0';
            strncpy(filePath + dir_path_size, routeWithIndex, 256 - strlen(filePath) - 1);
        }

        filePath[strlen(filePath) + 1] = '\0';
    }
    
    if (access(filePath, F_OK) != 0) {
        printf("%s\n", filePath);
        printf("File does not exist. Routing to not fount...\n");
        snprintf(filePath, 256, "hrmremake/browser/not-found/index.html");
        snprintf(MIMEtype, 16, ".html");
    }

    return true;
}

int createResponse(char *fullPath, char *MIMEtype, char **response_buffer) 
{
    FILE *file = fopen(fullPath, "r");
    char *file_buffer = NULL;

    if (file == NULL)
    {
        size_t problem_response_size = strlen("HTTP/1.1 500 Problem\r\n\r\n");
        *response_buffer = malloc(problem_response_size+1);
        if (*response_buffer == NULL) {
            fprintf(stderr, "Failed to allocate memory...\n");
            dprintf(fd, "Failed to allocate memory...\n");
            return 0;
        }

        strncpy(*response_buffer, "HTTP/1.1 500 Problem\r\n\r\n", problem_response_size);
        (*response_buffer)[problem_response_size] = '\0';
        return 1;
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
            return 0;
        }

        ssize_t read_bytes = fread(file_buffer, 1, file_size, file);
        if (read_bytes < 0) {
            
            fprintf(stderr, "Failed to read data from file...\n");
            dprintf(fd, "Failed to read data from file...\n");
            fclose(file);
            free(file_buffer);
            return 0;
        }
        file_buffer[file_size] = '\0';
        fclose(file);

        size_t new_response_buffer_size = response_setup_size + file_size + 1;
        *response_buffer = (char *)malloc(new_response_buffer_size);
        if (*response_buffer == NULL) {
            fprintf(stderr, "Failed to allocate memory...\n");
            dprintf(fd, "Failed to allocate memory...\n");
            free(file_buffer);
            return 0;
        }
        strcpy(*response_buffer, response_setup_string);
        strcat(*response_buffer, file_buffer);

        free(file_buffer);
    }

    return 1;
}

int writingAndSendingAResoponse(int socket, char* filePath, char* MIMEtype) 
{
    char *response_buffer = NULL;
    if(!createResponse(filePath, MIMEtype, &response_buffer)) {
        return 0;
    }
    
    if (response_buffer == NULL) {
        fprintf(stderr, "Failed to create response...\n");
        dprintf(fd, "Failed to create response...\n");
        return 0;
    }

    if (send(socket, response_buffer, strlen(response_buffer), 0) < 0)
    {
        fprintf(stderr, "Failed to send response...\n");
        dprintf(fd, "Failed to send response...\n");
        return 0;
    }

    free(response_buffer);
    return 1;
}

bool sendResponse(int socket, char* method, char* route, char* siteDirectory)
{
    char filePath[256];
    char MIMEtype[16];
    snprintf(filePath, sizeof(filePath), "%s", siteDirectory);
    size_t dir_length = strlen(siteDirectory);

    if(!establishingFilePathAndDataType(filePath, method, route, MIMEtype, dir_length)) 
    {
        fprintf(stderr, "Failed to establish file path and data type...\n");
        dprintf(fd, "Failed to establish file path and data type...\n");
        return false;
    }
    if(!writingAndSendingAResoponse(socket, filePath, MIMEtype)) {
        return false;
    }
    return true;
}

void* reciveAndSendData(void* arg) 
{
    struct ClientSocketDetails* client = (struct ClientSocketDetails*) arg;

    ssize_t recieved_bytes = recv(client->socket, client->request_buffer, MAX_REQUEST_SIZE - 1, 0);
    if (recieved_bytes < 0)
    {
        fprintf(stderr, "Failed to read request_buffer to socket...\n");
        dprintf(fd, "Failed to read request_buffer to socket...\n");
        close(client->socket);
        free(client);
        pthread_exit(NULL);
        exit(1);
    }
    client->request_buffer[recieved_bytes] = '\0';

    dprintf(fd, "%s\n", client->request_buffer);
    sscanf(client->request_buffer, "%s %s", client->method, client->route);
    client->method[strlen(client->method) + 1] = '\0';
    client->route[strlen(client->route) + 1] = '\0';

    dprintf(fd, "Request accepted, sending response...\n");
    if(!sendResponse(client->socket, client->method, client->route, client->siteDirectory)) {
        printf("Failed to send response to client...\n");
        dprintf(fd, "Failed to send response to client...\n");
        exit(1);
    }
    close(client->socket);
    free(client);
    pthread_exit(NULL);
}

void reciveAndSendDataOnSeparateThread(int client_socket, char *webSiteDirPath) 
{
    pthread_t id;
    struct ClientSocketDetails* client = (struct ClientSocketDetails*)malloc(sizeof(struct ClientSocketDetails));

    if (client == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        dprintf(fd, "Memory allocation failed!\n");
        exit(1);
    }
    client->socket = client_socket;
    strcpy(client->siteDirectory, webSiteDirPath);

    int thread = pthread_create(&id, NULL, reciveAndSendData, client);
    if (thread != 0) {
        fprintf(stderr, "Failed to create thread. Error code: %d\n", thread);
        dprintf(fd, "Failed to create thread. Error code: %d\n", thread);
        free(client);
        exit(1);
    }
    pthread_join(id, NULL);
}

void handle_sigint(int sig) {
    printf("\nExiting program...\n");
    close(fd);
    close(server_socket);
    exit(0);
}

void cleanup() {
    close(fd);
    close(server_socket);
}

int main (int argc, char **argv) 
{
    atexit(cleanup);

    if (signal(SIGINT, handle_sigint) == SIG_ERR) {
        perror("Failed to set signal handler");
        exit(0);
    }
    if (argc < 2) {
        printf("Missing project build directory...\n");
        exit(0);
    }
    DIR *dir = opendir(argv[1]);
    if (dir) {
        printf("\nSuccessfully located the project build directory...\n");
        closedir(dir);
    } else {
        printf("Failed to locate/open project build directory...\n");
        exit(1);
    }

    if ((fd = open("logs.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
        fprintf(stderr, "Cannot open log file...\n");
        exit(-1);
    }

    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, "", PORT, 10, argv[1]);
    server_socket = server.socket;

    int address_length = sizeof(server.address);
    int client_socket = 0;
    
    // Waiting for a client request
    while(true)
    {
        dprintf(fd, "\n===== WAITING =====\n");
        dprintf(fd, "Waiting for client request...\n\n");

        // At this part the program stops and listens for a connection
        if ((client_socket = accept(server.socket, (struct sockaddr *)&server.address, (socklen_t *)&address_length)) < 0)
        {
            fprintf(stderr, "Failed to accept client...\n");
            dprintf(fd, "Failed to accept client...\n");
            break;
        }

        // Create multiple threads
        reciveAndSendDataOnSeparateThread(client_socket, server.websiteDirectoryPath);
    }

    close(fd);
    close(server.socket);
    exit(0);
}
