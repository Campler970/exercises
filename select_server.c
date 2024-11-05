#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

int main() {
    int server_fd = 0, new_socket = 0, result = 0, i = 0, max_fd = 0, fd = 0, addrlen = 0;
    int client_socket[MAX_CLIENTS] = {0};
    struct sockaddr_in address = {0};
    char buffer[BUFFER_SIZE] = {0};
    char send_buffer[BUFFER_SIZE] = {0};
    fd_set read_fds = {0};
    struct timeval timeout = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        printf("Socket failed \n");
        return -1;
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        printf("Bind failed \n");
        close(server_fd);
        return -1;
    }

    if (listen(server_fd, 3) < 0) {
        printf("Listen failed \n");
        close(server_fd);
        return -1;
    }
    printf("Listening on port %d...\n", PORT);

    while (1) {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);
        max_fd = server_fd;

        for (i = 0; i < MAX_CLIENTS; i++) {
            fd = client_socket[i];
            if (fd > 0)
                FD_SET(fd, &read_fds);
            if (fd > max_fd)
                max_fd = fd;
        }

        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        result = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (result < 0) {
            printf("select failed \n");
            break;
        } else if (result == 0) {
            printf("Timeout \n");
            continue;
        } else {
             if (FD_ISSET(server_fd, &read_fds)) {
                addrlen = sizeof(address);
                if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
                    printf("Accept failed \n");
                    return -1;
                }

                printf("New connection, socket fd is %d, ip is : %s, port : %d\n", new_socket,
                       inet_ntoa(address.sin_addr), ntohs(address.sin_port));

                for (i = 0; i < MAX_CLIENTS; i++) {
                    if (client_socket[i] == 0) {
                        client_socket[i] = new_socket;
                        printf("Adding to list of sockets as %d\n", i);
                        break;
                    }
                }
            }
            for (i = 0; i < MAX_CLIENTS; i++) {
                fd = client_socket[i];
                if (FD_ISSET(fd, &read_fds)) {
                    if (read(fd, buffer, BUFFER_SIZE) == 0) {
                        close(fd);
                        client_socket[i] = 0;
                    } else {
                        printf("Message from client: %s\n", buffer);
                        sprintf(send_buffer, "server send is %s", buffer);
                        send(fd, send_buffer, strlen(send_buffer), 0);
                    }
                }
            }
        }
    }
}