#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>

int main()
{
    int ret = 0;
    int wait_time = 0;
    int stdin_fd = 0; //标准输入文件描述符 0
    fd_set read_fds = {0};
    struct timeval timeout = {0};
    char buffer[100] = {0};

    while (wait_time < 10) {
        FD_ZERO(&read_fds);
        FD_SET(stdin_fd, &read_fds); 
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;

        ret = select(stdin_fd + 1, &read_fds, NULL, NULL, &timeout);

        if (ret < 0) {
            printf("select error \n");
        } else if (ret == 0) {
            printf("Timeout 3 seconds \n");
            wait_time += 3;
        } else {
            if (FD_ISSET(stdin_fd, &read_fds)) {
                fgets(buffer, sizeof(buffer), stdin);
                printf("enter: %s", buffer);
                wait_time = 0;
            }
        }
    }

    printf("exit after 10 seconds without inputting.\n");
    return 0;
}