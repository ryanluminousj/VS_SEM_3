#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX 10

int buffer = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

void* producer(void* arg) {
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&mutex);
        if (buffer == 1) {
            printf("Producer: Buffer full, going to sleep...\n");
            pthread_cond_wait(&cond, &mutex);
        }
        buffer = 1;
        printf("Producer: Produced an item, waking up consumer...\n");
        pthread_cond_signal(&cond); // Wake up consumer
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < MAX; i++) {
        pthread_mutex_lock(&mutex);
        if (buffer == 0) {
            printf("Consumer: Buffer empty, going to sleep...\n");
            pthread_cond_wait(&cond, &mutex);
        }
        buffer = 0;
        printf("Consumer: Consumed an item, waking up producer...\n");
        pthread_cond_signal(&cond); // Wake up producer
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
