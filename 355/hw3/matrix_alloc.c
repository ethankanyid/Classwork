#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <getopt.h>

int SIZE = 100;        // Default matrix size
int REPEAT = 50;       // Default number of multiplications

// Static matrices (global or static local in function)
static int *staticA;
static int *staticB;
static int *staticC;

// Helper to fill matrix with random numbers
void fill_random(int* matrix)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            matrix[i * SIZE + j] = rand() % 100 + 1;
}

// Helper to multiply matrices: C = A * B
void multiply_matrices(int* A, int* B, int* C)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            C[i * SIZE + j] = 0;
            for (int k = 0; k < SIZE; k++)
                C[i * SIZE + j] += A[i * SIZE + k] * B[k * SIZE + j];
        }
}

// Static matrix operations
void static_matrix_operations()
{
    printf("Running static matrix operations...\n");

    staticA = (int*)malloc(SIZE * SIZE * sizeof(int));
    staticB = (int*)malloc(SIZE * SIZE * sizeof(int));
    staticC = (int*)malloc(SIZE * SIZE * sizeof(int));

    fill_random(staticA);
    fill_random(staticB);

    clock_t start = clock();
    for (int i = 0; i < REPEAT; i++)
    {
        multiply_matrices(staticA, staticB, staticC);
    }
    clock_t end = clock();
    double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Static Matrices Time: %.3f seconds\n", elapsed);

    // Free dynamically allocated memory
    free(staticA);
    free(staticB);
    free(staticC);
}

// Stack-dynamic matrix operations
void stack_dynamic_matrix_operations()
{
    printf("Running stack-dynamic matrix operations...\n");

    int dynamicA[SIZE][SIZE];
    int dynamicB[SIZE][SIZE];
    int dynamicC[SIZE][SIZE]; // Result

    fill_random((int*)dynamicA);
    fill_random((int*)dynamicB);

    clock_t start = clock();
    for (int i = 0; i < REPEAT; i++)
    {
        multiply_matrices((int*)dynamicA, (int*)dynamicB, (int*)dynamicC);
    }
    clock_t end = clock();
    double elapsed = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Stack-Dynamic Matrices Time: %.3f seconds\n", elapsed);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    // Parsing command line arguments using getopt
    int opt;
    while ((opt = getopt(argc, argv, "s:r:h")) != -1) {
        switch (opt) {
            case 's':
                SIZE = atoi(optarg);  // Set matrix size
                break;
            case 'r':
                REPEAT = atoi(optarg);  // Set number of repetitions
                break;
            case 'h':
                printf("Usage: [-s matrix_size] [-r repetitions]\n");
                exit(0);
            default:
                fprintf(stderr, "Usage: %s [-s matrix_size] [-r repetitions]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Ensure SIZE is positive and REPEAT is at least 1
    if (SIZE <= 0 || REPEAT <= 0) {
        fprintf(stderr, "Matrix size and repetitions must be positive integers.\n");
        exit(EXIT_FAILURE);
    }

    static_matrix_operations();
    stack_dynamic_matrix_operations();

    return 0;
}
