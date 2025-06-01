#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 500000

int max = MAX;

void staticStack()
{
    // Measure time
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    static int arr[MAX];  // Static Allocation data segment
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Static Stack:\n \tAllocation Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    for (int j = 0; j < max; j++) {
    for (int i = 0; i < max; i++) {
        arr[i] = i;  // Writing data
    }}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tWrite Time: %f seconds\n", cpu_time_used / max);

    start = clock();
        arr[max/2] = max;  // update data
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tUpdate Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    int i = arr[max/2];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tAccess Time: %f seconds\n\n", cpu_time_used / max);
}

/*void fixStackDynam()
{
    // Measure time
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int arr[max];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Fix Stack Dynamic:\n \tAllocation Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    for (int j = 0; j < max; j++) {
    for (int i = 0; i < max; i++) {
        arr[i] = i;  // Writing data
    }}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tWrite Time: %f seconds\n", cpu_time_used / max);

    start = clock();
        arr[max/2] = max;  // update data
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tUpdate Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    int i = arr[max/2];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tAccess Time: %f seconds\n\n", cpu_time_used / max);
}*/

void fixStackDynamDecl()
{
    // Measure time
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int arr[MAX];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Fix Stack Dynamic Declaration:\n \tAllocation Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    for (int j = 0; j < max; j++) {
    for (int i = 0; i < max; i++) {
        arr[i] = i;  // Writing data
    }}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tWrite Time: %f seconds\n", cpu_time_used / max);

    start = clock();
        arr[max/2] = max;  // update data
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tUpdate Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    int i = arr[max/2];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tAccess Time: %f seconds\n\n", cpu_time_used / max);
}

void stackDynam(int n)
{
    // Measure time
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int arr[n];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Stack Dynamic:\n \tAllocation Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    for (int j = 0; j < max; j++) {
    for (int i = 0; i < max; i++) {
        arr[i] = i;  // Writing data
    }}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tWrite Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    start = clock();
        arr[max/2] = max;  // update data
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tUpdate Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    int i = arr[max/2];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tAccess Time: %f seconds\n\n", cpu_time_used / max);
}

void fixHeapDynam()
{
    // Measure time
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int *arr = (int*)malloc(MAX * sizeof(int));
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Fixed Heap Dynamic:\n \tAllocation Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    for (int j = 0; j < max; j++) {
    for (int i = 0; i < max; i++) {
        arr[i] = i;  // Writing data
    }}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tWrite Time: %f seconds\n", cpu_time_used / max);

    start = clock();
        arr[max/2] = max;  // update data
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tUpdate Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    int i = arr[max/2];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tAccess Time: %f seconds\n\n", cpu_time_used / max);

    free(arr);
}

void heapDynam(int n)
{
    // Measure time
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int *arr = (int*)malloc(n * sizeof(int));
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Heap Dynamic:\n \tAllocation Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    for (int j = 0; j < max; j++) {
    for (int i = 0; i < max; i++) {
        arr[i] = i;  // Writing data
    }}
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tWrite Time: %f seconds\n", cpu_time_used / max);

    start = clock();
        arr[max/2] = max;  // update data
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tUpdate Time: %f seconds\n", cpu_time_used / max);

    start = clock();
    int i = arr[max/2];
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\tAccess Time: %f seconds\n\n", cpu_time_used / max);

    free(arr);
}

int main()
{
    staticStack();
    //fixStackDynam();
    fixStackDynamDecl();
    stackDynam(MAX);
    fixHeapDynam();
    heapDynam(MAX);
    printf("\n\nstack times vs stack times: no difference at large n\n");
    printf("heap times vs heap times: no difference n\n");
    printf("stack times vs heap times: heap took moderately longer at large n\n");
}
