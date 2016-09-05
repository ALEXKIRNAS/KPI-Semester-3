#include <cs50.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    int n;

	do{
		printf("Height: ");
		n = GetInt();
	} while (n < 0 || n > 23);


	int max = n+1;
	for(int i=0; i<n; i++) {

		for(int z = 0; z < max - (i+2); z++) printf(" ");
		for(int z = 0; z < (i+2); z++) printf("#");
		printf("\n");
	}
}