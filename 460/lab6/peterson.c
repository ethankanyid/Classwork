#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

#define NUM_ITERATIONS 1000000

int counter = 0;               // Shared counter
bool flag[2] = {false, false}; // Flags for each thread
int turn = 0;                  // Whose turn is it?

// Thread function
void *run(void *arg)
{
    int id = *(int *)arg; // 0 or 1
    int j = 1 - id;

    for (int i = 0; i < NUM_ITERATIONS; ++i)
    {
        flag[id] = true;
        turn = j; // Lock
        while (flag[j] && turn == j)
            ;
        printf("%d entering critical section; counter: %d\n", id, counter);
        counter++;        // Critical section
        flag[id] = false; // Unlock
    }

    return NULL;
}

int main()
{
    pthread_t thread0, thread1;
    int id0 = 0, id1 = 1;

    // Create threads
    pthread_create(&thread0, NULL, run, &id0);
    pthread_create(&thread1, NULL, run, &id1);

    // Wait for both threads
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);

    // Check result
    printf("Final counter value: %d\n", counter); // Should be 2,000,000

    return 0;
}
