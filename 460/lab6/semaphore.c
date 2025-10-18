#include <pthread.h>
#include <stdio.h>

#define NUM_ITERATIONS 1000000

int counter = 0; // Shared counter

pthread_mutex_t mutex; // Mutex acting as binary semaphore

// wait() - Acquire the semaphore (lock)
void wait()
{
    pthread_mutex_lock(&mutex);
}

// signal() - Release the semaphore (unlock)
void signal()
{
    pthread_mutex_unlock(&mutex);
}

// Thread function
void *run(void *arg)
{
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        wait(); // Enter critical section
        counter++;
        signal(); // Exit critical section
    }
    return NULL;
}

int main()
{
    pthread_t thread0, thread1;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_create(&thread0, NULL, run, NULL);
    pthread_create(&thread1, NULL, run, NULL);

    // Wait for threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    // Print final counter value
    printf("Final counter value: %d\n", counter);

    return 0;
}
