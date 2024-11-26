#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TOTAL_TICKETS 100
#define MAX_WINDOWS 2 

int tickets = TOTAL_TICKETS;

pthread_mutex_t mutex;
sem_t semaphore;

void* sell_tickets(void* arg)
{
    int window_id = *(int*)arg;

    while (1) {
        sem_wait(&semaphore);
        pthread_mutex_lock(&mutex);

        if (tickets > 0) {
            printf("window %d has ticket number %d\n", window_id, tickets);
            tickets--;
            usleep(3000);
        } else {
            pthread_mutex_unlock(&mutex);
            sem_post(&semaphore);
            break;
        }

        pthread_mutex_unlock(&mutex);
        sem_post(&semaphore);
    }

    return NULL;
}

int main() {
    int i = 0;
    int windows[3] = {0};
    pthread_t threads[3] = {0};
    pthread_mutex_init(&mutex, NULL);
    sem_init(&semaphore, 0, MAX_WINDOWS);

    for (i = 0; i < 3; i++) {
        windows[i] = i + 1;
        pthread_create(&threads, NULL, sell_tickets, &windows[3]);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&semaphore);

    printf("All tickets sold out!\n");
    return 0;
}