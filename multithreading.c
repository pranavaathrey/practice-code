#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Shared data: Array of roll numbers
int roll_numbers[] = {101, 102, 103, 104, 105, 106, 107, 108};
int n = 8; // Size of array

pthread_mutex_t lock; // Mutex for synchronization

// Thread function for Odd Roll Numbers
void* process_odd(void* arg) {
    pthread_mutex_lock(&lock); // Enter Critical Section
    printf("\n[Thread Odd] Processing Odd Roll Numbers:\n");
    for (int i = 0; i < n; i++) {
        if (roll_numbers[i] % 2 != 0) {
            printf("Processing Roll No: %d\n", roll_numbers[i]);
        }
    }
    pthread_mutex_unlock(&lock); // Exit Critical Section
    return NULL;
}

// Thread function for Even Roll Numbers
void* process_even(void* arg) {
    pthread_mutex_lock(&lock); // Enter Critical Section
    printf("\n[Thread Even] Processing Even Roll Numbers:\n");
    for (int i = 0; i < n; i++) {
        if (roll_numbers[i] % 2 == 0) {
            printf("Processing Roll No: %d\n", roll_numbers[i]);
        }
    }
    pthread_mutex_unlock(&lock); // Exit Critical Section
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // initialize mutex
    pthread_mutex_init(&lock, NULL);

    // create threads
    pthread_create(&t1, NULL, process_odd, NULL);
    pthread_create(&t2, NULL, process_even, NULL);

    // join threads (wait for them to finish)
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}