#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main (void){
    
    char* str = GetString();
    char* ptr = strtok(str, " ");
    
    while(ptr != NULL){
        
        printf("%c", toupper(*ptr));
        ptr = strtok(NULL, " ");
        
    }
    printf("\n");
    
}