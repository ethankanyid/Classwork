#include <stdio.h>

int level;
enum {
    //nElems = 3,
    NOT_DONE = -1
};
//int val[nElems]; 

void recur(int k, int nElems, int *ptr, void (*handlePerm)(int elems[], int nElems, void *userArg), void *userArg)
{
    int i;

    ptr[k] = level;
    level++;
    
    if (level == nElems) 
    {
        handlePerm(ptr,nElems,userArg);
    }

    for (i = 0; i < nElems; i++)
        if (ptr[i] == NOT_DONE)
            recur(i, nElems, ptr, handlePerm, userArg);
    
    level--;
    
    ptr[k] = NOT_DONE;
}

void genPerms(int nElems, void (*handlePerm)(int elems[], int nElems, void *userArg), void *userArg)
{
    int i;

    int val[nElems];
    int *ptr = val;

    level = 0;
    for (i = 0; i < nElems; i++)
        val[i] = NOT_DONE;
    
    for (i = 0; i < nElems; i++)
        recur(i, nElems, ptr, handlePerm, userArg);
}
