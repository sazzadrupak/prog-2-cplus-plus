#include "swap.hh"
#include <iostream>

// TODO: Implement swap function here
void swap(int & i, int & j){
    i = i + j;
    j = i - j;
    i = i - j;
}
