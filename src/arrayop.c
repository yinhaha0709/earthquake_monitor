/*
    Pre allocates space for arrays when they are defined. 
    After the array is used up, free up space.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "arrayop.h"

//Pre allocate memory to 2D array
double** allocation_memory_double(int row, int cow)
{
    int i = 0;
    double** p;
    p = (double**)malloc(row*sizeof(double*));
    for(i = 0; i < row; i++)
    {
        p[i] = (double*)malloc(cow*sizeof(double));
    }
    return p;
}

//Freeing memory for two-dimensional arrays
void* free_memory_double(double** p, int row)
{
    if(NULL == p){
        return NULL;
    }
    int i = 0;
    for(i = 0; i < row; i++)
    {
        free(p[i]);
    }
    free(p[i]);
    return NULL;
} 