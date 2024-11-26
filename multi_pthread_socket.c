#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void* handle_client(void* client_socket)
{
    int socket = 0;
    int bytes_read = 0; 
    char buffer[BUFFER_SIZE] = {0};

    socket = *(int*)client_socket;

    while (1) {
        memset(buffer, 0 , BUFFER_SIZE);
        bytes_read = recv(socket, buffer, BUFFER_SIZE, 0);
        if (bytes_read <= 0) {
            printf("client disconnect \n");
            break;
        } 

        printf("received: %s", buffer);
        send(socket, buffer, bytes_read, 0);
    }

    close(socket);
    return NULL;
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 创建服务器套接字
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 设置服务器地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定套接字
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 监听连接
    if (listen(server_fd, 10) == -1) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d...\n", PORT);

    while (1) {
        // 接受客户端连接
        client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len);
        if (client_socket == -1) {
            perror("Accept failed");
            continue;
        }

        // 打印客户端地址
        printf("Connected with client: %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // 创建线程处理客户端
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void*)&client_socket) != 0) {
            perror("Thread creation failed");
            close(client_socket);
        }

        // 分离线程，主线程不需要等待
        pthread_detach(thread_id);
    }

    // 关闭服务器套接字
    close(server_fd);
    return 0;
}