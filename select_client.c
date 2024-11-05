#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int socket_fd = 0;
    struct sockaddr_in serv_addr = {0};
    char buffer[BUFFER_SIZE] = {0};
    char message[BUFFER_SIZE] = {0};

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket failed \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address \n");
        return -1;
    }

    if (connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection failed \n");
        return -1;
    }

    while (1) {
        printf("Enter message: ");
        fgets(message, BUFFER_SIZE, stdin);

        send(socket_fd, message, strlen(message), 0);
        read(socket_fd, buffer, BUFFER_SIZE);
        printf("Server: %s\n", buffer);
    }

    return 0;
}
