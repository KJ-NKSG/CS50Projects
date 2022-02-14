#include "math.h"
#include "stdio.h"
#include "stdlib.h"
#include "cs50.h"

int main(void)
{
    for (int i = 90 ; i < 100; i++)
    {
        printf("%.3i.jpg\n",i);
    }
    
     if (ptr[0] == 0xff && ptr[1] == 0xd8 && ptr[2] == 0xff && (ptr[3] & 0xf0) == 0xe0)
        {
             j += 1;
             if (j == 1)
             {
                 sprintf(filename,"%.3i.jpg", j);
                 outptr = fopen(filename, "w");
                 if (outptr == NULL)
                 {
                     fprintf(stdout,"Could not open %s", filename);
                     fclose(outptr);
                     return 1;
                 }
                else
                {
                 fwrite(ptr, block, 1, outptr);
                }
             }
             else
             {
                fclose(outptr);
                sprintf(filename,"%.3i.jpg", j);
                outptr = fopen(filename , "w");
                fwrite(ptr, block, 1, outptr);
             }
        }
        else
        {
            fwrite(ptr, block, 1, outptr);
        }
    }
    fprintf(stdout,"Total jpegs in file are: %i\n" , j);
    free(ptr);
    fclose(rawfile);
}