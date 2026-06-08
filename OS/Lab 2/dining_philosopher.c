#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopsticks[N];
pthread_mutex_t room; // Used to prevent deadlocks (allowing only N-1 philosophers in the room)

void* philosopher(void* num) {
    int id = *(int*)num;

    for (int i = 0; i < 3; i++) { // Each philosopher eats 3 times before finishing
        printf("Philosopher %d is thinking.\n", id);
        sleep(1);

        pthread_mutex_lock(&room); // Enter the dining room
        
        sem_wait(&chopsticks[id]); // Pick up left chopstick
        sem_wait(&chopsticks[(id + 1) % N]); // Pick up right chopstick
        
        printf("Philosopher %d is eating.\n", id);
        sleep(2);

        sem_post(&chopsticks[id]); // Put down left chopstick
        sem_post(&chopsticks[(id + 1) % N]); // Put down right chopstick
        
        pthread_mutex_unlock(&room); // Leave the dining room
    }
    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    pthread_mutex_init(&room, NULL);
    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
        ids[i] = i;
    }

    // Creating philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, philosopher, &ids[i]);
    }

    // Waiting for all philosophers to finish
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }
    pthread_mutex_destroy(&room);

    return 0;
}
