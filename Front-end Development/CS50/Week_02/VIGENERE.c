#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>


int main (int argc, char* argv[]){
    
    if(argc != 2) {
        printf("Usage: ./vigenere <key>\n");
        return 1;
    }
    
    char* str = GetString();
    int k = strlen(argv[1]);
    int t = 0;
    
    for(int i=0; str[i]; i++){
        
        if(t >= k) t-=k;
        
        int ch = str[i];
        int plus = tolower (argv[1][t]) - 'a';
        
        if(isalpha(str[i])){
            if(isupper(str[i])) {
                 ch += plus;
                if(ch > 'Z') ch-=26;
            }
            else{
                 ch += plus;
                if(ch > 'z') ch-=26;
            }
            t++;
        }
        
        printf("%c", (char) ch);
    }
    printf("\n");
}