#pragma once
#include "ArrayUtils.h"

void selectionSort(int* array, int arrayCount)
{
    for(int i = 0; i < arrayCount-1; i++) // O(N^2)
    {
        int minIndex = i;
        for(int j = i + 1; j < arrayCount; j++)
        {
            if(array[minIndex] > array[j])
                minIndex = j;
        }

        if(minIndex == i)
            continue;

        // Post condition minIndex is the index of the smallest element in the array
        array[minIndex] = array[minIndex] + array[i];
        array[i] = array[minIndex] - array[i];
        array[minIndex] = array[minIndex] - array[i];
    }
}

void insertionSort(int* array, int arrayCount)
{
    for (int i = 1; i < arrayCount; i++) // O(N^2)
    {

        for (int j = i; j > 0 && array[j] < array[j - 1]; j--)
        {
            int temp = array[j];
            array[j] = array[j - 1];
            array[j - 1] = temp;
        }
    }
}

void bubbleSort(int* array, int arrayCount)
{
    bool swapped;
    do
    {
        swapped = false;
        for (int i = 0; i < (arrayCount - 1); i++)
        {
            if (array[i] > array[i + 1])
            {
                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
                swapped = true;
            }
        }
    } while (swapped);
}


void mergeSort(int* array, int arrayCount)
{
    if (arrayCount == 1)
        return;

    int leftCount = arrayCount / 2;
    int rightCount = arrayCount - leftCount;

    // Create 2 subarrays
    // Copy the elements from array into subarrays
    int* leftArray = generateIntArrayCopy(leftCount, array);
    int* rightArray = generateIntArrayCopy(rightCount, array + leftCount);

    // Call mergeSort on the subarrays
    mergeSort(leftArray, leftCount);
    mergeSort(rightArray, rightCount);
    
    int leftIndex = 0, rightIndex = 0;
    
    for (int mainIndex = 0 ; mainIndex < arrayCount; mainIndex ++)
    {
        
        if(rightIndex == rightCount || (leftIndex < leftCount && leftArray[leftIndex] <= rightArray[rightIndex]))
        {
            array[mainIndex] = leftArray[leftIndex];
            leftIndex++;
        }
        
        else if(leftIndex == leftCount || ( rightIndex < rightCount && rightArray[rightIndex] < leftArray[leftIndex]))
        {
            array[mainIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        
    }
    
    // Now that we have returned from the mergeSort calls, the subarrays should be sorted
    // Perform the merge process
    // Left as an exercise for the student

    free(leftArray);
    free(rightArray);
    
    return;
}
