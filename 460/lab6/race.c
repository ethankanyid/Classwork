#include <pthread.h>
#include <stdio.h>

#define NUM_ITERATIONS 1000000

int counter = 0; // Shared counter

void *increment_counter(void *arg)
{
    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        counter++;
        // counter++ is not atomic:
        // It's translated roughly to:
        // 1. Read counter
        // 2. Increment the value
        // 3. Write it back
        // Multiple threads doing this at once can cause lost updates.
    }
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final counter value
    printf("Final counter value: %d\n", counter);
    return 0;
}
