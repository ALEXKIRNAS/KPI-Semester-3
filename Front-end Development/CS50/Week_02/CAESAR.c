#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>


int main (int argc, char* argv[]){
    
    if(argc != 2) {
        printf("Usage: ./caesar <key>\n");
        return 1;
    }
    
    int k = atoi (argv[1]) % 26;
    char* str = GetString();
    
    for(int i=0; str[i]; i++){
        int ch = str[i];
        
        if(isalpha(str[i])){
            if(isupper(str[i])) {
                 ch += k;
                if(ch > 'Z') ch-=26;
            }
            else{
                 ch += k;
                if(ch > 'z') ch-=26;
            }
        }
        
        printf("%c", (char) ch);
    }
    printf("\n");
}