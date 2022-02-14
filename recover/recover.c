#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    int block = 512; //FAT standard block size is 512 bytes


    //Error Handling 1: return usage method is no command line arguments specified
    //Only 1 argument allowed.
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //Error Handling 2: Not able to read/open the image file
    //Assign pointer to the open file
    FILE *rawfile = fopen(argv[1], "r");

    if (rawfile == NULL)
    {
        fprintf(stderr, "Image File was not able to be read / open. Check image file.\n");
        return 1;
    }

    //Review file and scan for JPEG signatures based on the first 4 bytes in each block
    BYTE *ptr = malloc(block);
    if (ptr == NULL)
    {
        fprintf(stderr, "Something went wrong with allocating Memory");
        return 2;
    }

    int j = 0;
    int counter = 0;
    char filename[10];
    FILE *outptr;

    while (fread(ptr, block, 1, rawfile) == 1)// recovloop through while fread returns else break out.
    {
        //fread(ptr, block, 1 , rawfile);JPEG sigs for first 3 bytes are 0xff (255) , 0xd8 (216), 0xff (255).
        //The 4th Byte is 0xe(y)  where by (y) will range from 0 to f. In which case the first 4 bits
        //of the 4th bytes will always start in 1110 xxxx.
        //need to use bitwise operator to mask last 4 bits of the 4th byte - 0xf0 = 1111 0000
        //& will return the value if both same else will return zero. so we want 111 then rest is zero.
        //0xe0 = 1110 0000. if reached end of file escape
        if (feof(rawfile))
        {
            break;
        }
        //fprintf(stdout,"1st Byte: %X, 6th Byte: %X\n", ptr[0],ptr[5]);

        if (ptr[0] == 0xff && ptr[1] == 0xd8 && ptr[2] == 0xff && (ptr[3] & 0xf0) == 0xe0)
        {
            j += 1;
            if (j == 1)
            {
                sprintf(filename, "%.3i.jpg", j - 1);
                outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    fprintf(stdout, "Could not open %s", filename);
                    return 1;
                }
                fwrite(ptr, block, 1, outptr);
            }
            else
            {
                fclose(outptr);
                sprintf(filename, "%.3i.jpg", j - 1);
                outptr = fopen(filename, "w");
                fwrite(ptr, block, 1, outptr);
            }
        }
        else if (j != 0)
        {
            fwrite(ptr, block, 1, outptr);
        }
    }
    // fprintf(stdout,"Total jpegs in file are: %i\n" , j);
    free(ptr);
    fclose(rawfile);
    return 0;

}
