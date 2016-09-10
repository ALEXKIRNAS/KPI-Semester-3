/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int l=0, r=n;
    int m;
    while(l+1 < r){
        m = (l+r) >> 1;
        if(values[m] < value) l = m;
        else r = m;
    }
    
    if(values[l] == value) return true;
    else if(values[r] == value) return true;
    else return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
   for(int i = 0; i<n; i++){
       
       int min = i;
       for(int z = i+1; z < n; z++) if(values[z] < values[min]) min = z;
       
       if(i == min) continue;
       
       values[i]^=values[min];
       values[min]^=values[i];
       values[i]^=values[min];
   }
    return;
}
