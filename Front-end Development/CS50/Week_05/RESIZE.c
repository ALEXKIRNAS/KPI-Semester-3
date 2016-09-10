/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int k = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    FILE* inptr = fopen(infile, "r");
    FILE* outptr = fopen(outfile, "w");

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    int padding;
    bi.biWidth *= k;
    bi.biHeight*= k;
    padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage+54;
    
    int h = abs(bi.biHeight)/k;
    int w = abs(bi.biWidth)/k;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    RGBTRIPLE** matrix = malloc(sizeof(RGBTRIPLE*) * abs(bi.biHeight));
    for(int i=0; i<abs(bi.biHeight); i++) matrix[i] = malloc (sizeof( RGBTRIPLE) * abs(bi.biWidth));
    
    padding =  (4 - (w* sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0; i < h; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < w; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for(int z = 0; z < k; z++)
                for(int t = 0; t < k; t++){
                    matrix[i*k+z][j*k+t] = triple;
                }
        }
        
        fseek(inptr, padding, SEEK_CUR);
    }
    
    padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    for(int i=0; i<abs(bi.biHeight); i++){
        for(int z=0; z< abs(bi.biWidth); z++){
            RGBTRIPLE triple = matrix[i][z];
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }
     
      for (int y = 0; y < padding; y++)
        {
            fputc(0x00, outptr);
        }
        
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    for(int i=0; i<abs(bi.biHeight); i++) free(matrix[i]);
    free(matrix);

    // that's all folks
    return 0;
}
