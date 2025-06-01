#include <iostream>
#include "ArrayUtils.h"
#include "sorting_algorithms.h"
#include <chrono>

using namespace std;


int main(int argc, char* argv[])
{
    // Replace the body of the main function with the code to create arrays and time the sorts.

    
    
//    int arrayCount = 20;
//    int array[] = {4, 89, 1, 12, 6, 27, 9, 4, 77, 94, 69, 68, 7, 27, 21, 13, 2, 8, 16, 3};
    
    for (int i = 1000; i <= 100000; i*=10)
    {
        int* array = generateRandomIntArray(i);
        int arrayCount = i;
        
        //    printIntArray(arrayCount, array);
        
        //    selectionSort(array, arrayCount);
        //    insertionSort(array, arrayCount);
        
        // BUBBLE
        
        int* arraycpy = generateIntArrayCopy(arrayCount, array);
        
        auto start = std::chrono::high_resolution_clock::now();
        
        bubbleSort(arraycpy, arrayCount);
        
        auto stop = std::chrono::high_resolution_clock::now();
        
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        
        //  printIntArray(arrayCount, arraycpy);
        
        cout << endl << "Bubble execution time: " << duration.count() << " microseconds" << endl << endl;
        
        free(arraycpy);
        
        // MERGE
        
        int* arraycpy2 = generateIntArrayCopy(arrayCount, array);
        
        auto start2 = std::chrono::high_resolution_clock::now();
        
        mergeSort(arraycpy2, arrayCount);
        
        auto stop2 = std::chrono::high_resolution_clock::now();
        
        auto duration2 = duration_cast<std::chrono::microseconds>(stop2 - start2);
        
        //  printIntArray(arrayCount, array);
        //  printIntArray(arrayCount, arraycpy2);
        
        cout << endl << "Merge execution time: " << duration2.count() << " microseconds" << endl << endl;
        
        free(arraycpy2);
        
    }
    

    return 0;
}

