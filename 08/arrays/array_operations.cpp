#include "array_operations.hh"
#include <algorithm>
#include<iostream>

int greatest_v1(int *itemptr, int size)
{
    int greatest = 0;
    for(int* i = itemptr; i < itemptr+size; i++){
        if(*i > greatest){
            greatest = *i;
        }
    }
    return greatest;
}

int greatest_v2(int *itemptr, int *endptr)
{
    int greatest = 0;
    for(int* i = itemptr; i < endptr; i++){
        if(*i > greatest){
            greatest = *i;
        }
    }
    return greatest;
}

void copy(int *itemptr, int *endptr, int *targetptr)
{
    int j = 0;
    for (int* i = itemptr; i < endptr; ++i){
        targetptr[j] = *i;
        j++;
    }
}

void reverse(int *leftptr, int *rightptr)
{
    std::reverse(leftptr, rightptr);
}
