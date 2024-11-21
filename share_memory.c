#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_KEY 0x12345  
#define SHM_SIZE 1024

void producer() 
{
    int shm_id = 0;
    char *shm_addr = NULL;

    if((shm_id = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666)) < 0) {  // 创建共享内存段
        printf("get sharememory failed \n");
        return;
    }

    if((shm_addr = (char *)shmat(shm_id, NULL, 0)) == (char *)-1) { // 将共享内存段连接到当前进程
        printf("attach sharememory failed \n");
        return;
    }

    printf("Producer: writing to shared memory...\n");
    strcpy(shm_addr, "Hello from producer!");

    sleep(5);
    shmdt(shm_addr); // 将共享内存段分离出当前进程
    printf("Producer: done.\n");
}

void consumer() 
{
    int shm_id = 0;
    char *shm_addr = NULL;

    if((shm_id = shmget(SHM_KEY, SHM_SIZE, 0666)) < 0){
        printf("get sharememory failed \n");
        return;
    }

    if((shm_addr = (char *)shmat(shm_id, NULL, 0)) == (char *)-1) {
        printf("attach sharememory failed \n");
        return;
    }

    printf("Consumer: Reading from shared memory...\n");
    printf("Consumer: Data = %s\n", shm_addr);

    shmdt(shm_addr);
    shmctl(shm_id, IPC_RMID, NULL); //销毁共享内存段
    printf("Consumer: Done.\n");
}

int main(int argc, char *argv[]) 
{
    if (argc != 2) {
        printf(stderr, "Usage: %s <producer|consumer>\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "producer") == 0) {
        producer();
    } else if (strcmp(argv[1], "consumer") == 0) {
        consumer();
    } else {
        fprintf(stderr, "Invalid argument. Use 'producer' or 'consumer'.\n");
        return 1;
    }

    return 0;
}

