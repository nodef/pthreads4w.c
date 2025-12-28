// Example 2: Mutex Locking for Shared Resource
#define PTHREADS4W_IMPLEMENTATION
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10
#define NUM_INCREMENTS 1000

int shared_counter = 0;
pthread_mutex_t mutex;

void* increment_counter(void* arg) {
    for (int i = 0; i < NUM_INCREMENTS; i++) {
        pthread_mutex_lock(&mutex);
        shared_counter++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0) {
            perror("Failed to create thread");
            return 1;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
            return 1;
        }
    }

    pthread_mutex_destroy(&mutex);

    printf("Final value of shared_counter: %d\n", shared_counter);
    return 0;
}
