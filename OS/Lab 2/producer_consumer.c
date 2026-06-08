#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int buf[5], in=0, out=0;
sem_t empty, full;
pthread_mutex_t m;

void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty); pthread_mutex_lock(&m);
        buf[in] = i; printf("Produced: %d\n", i); in = (in + 1) % 5;
        pthread_mutex_unlock(&m); sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); pthread_mutex_lock(&m);
        printf("Consumed: %d\n", buf[out]); out = (out + 1) % 5;
        pthread_mutex_unlock(&m); sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t p, c;
    sem_init(&empty, 0, 5); sem_init(&full, 0, 0); pthread_mutex_init(&m, NULL);
    pthread_create(&p, NULL, producer, NULL); pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL); pthread_join(c, NULL);
    return 0;
}
