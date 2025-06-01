#pragma once

/**
* This will not work with the Linked based list.
*/
template<class TYPE>
void bubbleSort(TYPE array[], int count, int(*compare)(const TYPE& item1, const TYPE& item2)){
    bool swapped = true;
    while(swapped){
        swapped = false;
        for (int i = 0; i < count-1; ++i)
        {
            if(compare(array[i], array[i+1]) > 0)
            {
                TYPE temp = array[i];
                array[i] = array[i+1];
                array[i+1] = temp;
                swapped = true;
            }
        }
        count--;
    }
}
