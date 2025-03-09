#include "Server.h"

void launch (struct Server *server) 
{
    char buffer[30000], method[10], route[100];
    int address_length = sizeof(server->address);
    int new_socket;
    size_t response_length = strlen("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");

    while(1)
    {
        printf("===== WAITING FOR CONNECTION =====\n");

        if ((new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length)) < 0)
        {
            perror("Failed to accept client...\n");
            exit(1);
        }
        if (read(new_socket, buffer, 30000) < 0)
        {
            perror("Faile to read buffer to socket...\n");
            exit(1);
        }
        printf("%s\n", buffer);
        // storing the first two strings of buffer (response) to method and route
        sscanf(buffer, "%s %s", method, route);
        printf("\n%s\n%s\n\n", method, route);

        char fileUrl[100];
        if (route[strlen(route) - 1] == '/' || strcmp(route, "/index.html") == 0)
        {
            strcpy(fileUrl, "./TestWebSite/index.html");
        }
        else {
            strcpy(fileUrl, route);
        }

        FILE *file = fopen(fileUrl, "r");
        if (file == NULL) {
            const char response[] = "HTTP/1.1 404 Not Found\r\n\n<html><h1>404-NOT FOUND</h1></html>";
            send(new_socket, response, sizeof(response), 0);
        }
        else {
            fseek(file, 0, SEEK_END);
            size_t file_size = ftell(file);
            rewind(file);

            char *response_buffer = (char *)malloc(response_length + 1);
            if (!response_buffer) 
            {
                perror("Failed to allocate memory for response_buffer...");
                exit(1);
            }
            strcpy(response_buffer, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
            size_t current_response_buffer_length = strlen(response_buffer);

            char *file_buffer = (char *)malloc(file_size);
            if (!file_buffer) 
            {
                perror("Failed to allocate memory for response_buffer...");
                exit(1);
            }
            size_t bytesRead = fread(file_buffer, 1, file_size, file);
            file_buffer[bytesRead] = '\0';

            int new_response_buffer_size = current_response_buffer_length + strlen(file_buffer) + 1;
            response_buffer = (char *)realloc(response_buffer, new_response_buffer_size);
            if (!response_buffer) 
            {
                perror("Failed to allocate memory for response_buffer...");
                exit(1);
            }

            strcpy(response_buffer + current_response_buffer_length, file_buffer);
            printf("%s\n", response_buffer);

            if (write(new_socket, response_buffer, strlen(response_buffer)) < 0)
            {
                perror("Failed to write buffer to socket...\n");
                exit(1); 
            }

            free(response_buffer);
            free(file_buffer);
        }


        if(fclose(file) < 0)
        {
            perror("Failed to close file...\n");
            exit(1);
        }
        if(close(new_socket) < 0)
        {
            perror("Failed to close socket...\n");
            exit(1);
        }
        printf("\n\nFile and socket are closed...\n\n");
    }
}

int main () 
{
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_LOOPBACK, 8080, 10, launch);
    server.launch(&server);
}