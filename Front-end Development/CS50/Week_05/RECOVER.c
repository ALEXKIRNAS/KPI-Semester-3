/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 
 typedef unsigned char uint8_t;
 
 const int Nmax = 512;
 uint8_t mas [Nmax];
 uint8_t header1[4] = {0xff, 0xd8, 0xff, 0xe0}; 
 uint8_t header2[4] = {0xff, 0xd8, 0xff, 0xe1}; 
 
 int min (int x, int y){
    if(x <  y) return x;
    else return y;
 }
 
 char* makeName (int k){
     char* name = malloc(sizeof(char) * 100);
     name[0] = '0';
     name[1] = k >= 10 ? '1' : '0';
     name+=2;
     name[0] = (k%10) + '0';
     name[1] = '.';
     name[2] = 'j';
     name[3] = 'p';
     name[4] = 'g';
     name[5] = '\0';
     name-=2;
     return name;
 }

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    FILE* picture;
    int number = 0;
    char opened = 0;
    
    while(!feof(file)){
        int k = fread(&mas, sizeof(uint8_t), Nmax, file);
       
        if(memcmp(mas, header1, 4) == 0 || memcmp(mas, header2, 4) == 0){
            char* name = makeName(number);
            if(opened) fclose(picture);
            picture = fopen(name, "w");
            free(name);
            number++;
            opened = 1;
        }
        
        if(opened) fwrite(&mas, 1, min(Nmax, k), picture);
    }
    
    int k = fread(&mas, sizeof(uint8_t), Nmax, file);
    fwrite(&mas, 1, min(Nmax, k), picture);
    if(opened) fclose(picture);
    fclose(file);
}