#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_CUSTOMERS 5
#define NUMBER_OF_CHAIRS 3

sem_t barberReady;
sem_t customers;
pthread_mutex_t seatMutex;
int freeWaitSeats = NUMBER_OF_CHAIRS;

void* barber_func(void* arg) {
    while (1) {
        printf("Barber is sleeping.\n");
        sem_wait(&customers);
        pthread_mutex_lock(&seatMutex);
        
        freeWaitSeats++;
        sem_post(&barberReady);
        pthread_mutex_unlock(&seatMutex);

        printf("Barber is cutting hair.\n");
        sleep(2); // Time taken to cut hair
    }
    return NULL;
}

void* customer_func(void* arg) {
    int id = *(int*)arg;
    
    sleep(rand() % 3); // Random arrival time

    pthread_mutex_lock(&seatMutex);
    if (freeWaitSeats > 0) {
        freeWaitSeats--;
        printf("Customer %d is waiting. Free seats: %d\n", id, freeWaitSeats);
        sem_post(&customers);
        pthread_mutex_unlock(&seatMutex);
        
        sem_wait(&barberReady);
        printf("Customer %d is getting a haircut.\n", id);
    } else {
        printf("Customer %d left, no seats available.\n", id);
        pthread_mutex_unlock(&seatMutex);
    }
    return NULL;
}

int main() {
    pthread_t barber;
    pthread_t customer_threads[MAX_CUSTOMERS];
    int customer_ids[MAX_CUSTOMERS];

    sem_init(&barberReady, 0, 0);
    sem_init(&customers, 0, 0);
    pthread_mutex_init(&seatMutex, NULL);

    pthread_create(&barber, NULL, barber_func, NULL);

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        customer_ids[i] = i + 1;
        pthread_create(&customer_threads[i], NULL, customer_func, &customer_ids[i]);
        sleep(1);
    }

    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    // Since the barber runs infinitely, we just let the main thread exit here.
    return 0;
}
