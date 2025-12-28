// Example 1: Thread Creation and Joining
#define PTHREADS4W_IMPLEMENTATION
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;
    printf("Thread %d: Hello from the thread!\n", thread_id);
    return NULL;
}

int main() {
    const int NUM_THREADS = 5;
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i + 1;
        if (pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]) != 0) {
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

    printf("All threads have finished.\n");
    return 0;
}
