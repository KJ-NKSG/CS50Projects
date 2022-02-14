#include "helpers.h"
#include "math.h"
#include "stdio.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // take average of Red/blue/green values and return an average for each pixel
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.00);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // initialize the temp pointer to hold the modified pixels
    RGBTRIPLE(*temp)[width] = calloc(height, sizeof(image[width]));
    int max = 255; // max pixel rgb value
    int a = 0, b = 0, c = 0;

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            a = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            b = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            c = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            // set value if over max
            if (a > max)
            {
                a = max;
            }
            if (b > max)
            {
                b = max;
            }
            if (c > max)
            {
                c = max;
            }
            image[i][j].rgbtRed = a;
            image[i][j].rgbtGreen = b;
            image[i][j].rgbtBlue = c;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // Initialize temp to allocate memory for pixel calculation
    RGBTRIPLE(*temp)[width] = calloc(height, sizeof(image[width]));
    // create temp file reflected image without overwriting original image
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            temp[i][j] = image[i][width - j - 1];
        }
    }

    // Copy over temp file RGB values into image address to get reflected image
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    // free the memory for temp after transfer
    free(temp);

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Initialize a temp pointer with allocated memory
    RGBTRIPLE(*temp)[width] = calloc(height, sizeof(image[width]));
    int k, m;

    //Cycle through and calculate the blur pixels for Temp
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int r = 0, b = 0, g = 0;

            if (i == 0 && j == 0) // Top left Corner
            {
                for (k = 0; k < 2; k++)
                {
                    for (m = 0; m < 2; m++)
                    {
                        r += image[i + k][j + m].rgbtRed;
                        b += image[i + k][j + m].rgbtBlue;
                        g += image[i + k][j + m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 4.00);
                temp[i][j].rgbtBlue = round(b / 4.00);
                temp[i][j].rgbtGreen = round(g / 4.00);
            }

            else if (i == 0 && j == width - 1) // Top right Corner
            {
                for (k = 0; k < 2; k++)
                {
                    for (m = 0; m < 2; m++)
                    {
                        r += image[i + k][j - m].rgbtRed;
                        b += image[i + k][j - m].rgbtBlue;
                        g += image[i + k][j - m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 4.00);
                temp[i][j].rgbtBlue = round(b / 4.00);
                temp[i][j].rgbtGreen = round(g / 4.00);

            }
            else if (i == height - 1 && j == 0) // bottom left Corner
            {
                for (k = 0; k < 2; k++)
                {
                    for (m = 0; m < 2; m++)
                    {
                        r += image[i - k][j + m].rgbtRed;
                        b += image[i - k][j + m].rgbtBlue;
                        g += image[i - k][j + m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 4.00);
                temp[i][j].rgbtBlue = round(b / 4.00);
                temp[i][j].rgbtGreen = round(g / 4.00);
            }
            else if (i == height - 1 && j == width - 1)// bottom right Corner
            {
                for (k = 0; k < 2; k++)
                {
                    for (m = 0; m < 2; m++)
                    {
                        r += image[i - k][j - m].rgbtRed;
                        b += image[i - k][j - m].rgbtBlue;
                        g += image[i - k][j - m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 4.00);
                temp[i][j].rgbtBlue = round(b / 4.00);
                temp[i][j].rgbtGreen = round(g / 4.00);
            }
            else if (i == 0 && j != 0 && j != width - 1) // first row
            {
                for (k = 0 ; k < 2; k++)
                {
                    for (m = -1 ; m < 2; m++)
                    {
                        r += image[i + k][j + m].rgbtRed;
                        b += image[i + k][j + m].rgbtBlue;
                        g += image[i + k][j + m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 6.00);
                temp[i][j].rgbtBlue = round(b / 6.00);
                temp[i][j].rgbtGreen = round(g / 6.00);
            }
            else if (i == height - 1 && j != 0 && j != width - 1) // last row
            {
                for (k = -1 ; k < 1; k++)
                {
                    for (m = -1 ; m < 2; m++)
                    {
                        r += image[i + k][j + m].rgbtRed;
                        b += image[i + k][j + m].rgbtBlue;
                        g += image[i + k][j + m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 6.00);
                temp[i][j].rgbtBlue = round(b / 6.00);
                temp[i][j].rgbtGreen = round(g / 6.00);
            }
            else if (i != 0 && i != height - 1 && j == 0) // First column
            {
                for (k = -1 ; k < 2; k++)
                {
                    for (m = 0 ; m < 2; m++)
                    {
                        r += image[i + k][j + m].rgbtRed;
                        b += image[i + k][j + m].rgbtBlue;
                        g += image[i + k][j + m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 6.00);
                temp[i][j].rgbtBlue = round(b / 6.00);
                temp[i][j].rgbtGreen = round(g / 6.00);
            }
            else if (i != 0 && i != height - 1 && j == width - 1) // last column
            {
                for (k = -1 ; k < 2; k++)
                {
                    for (m = -1 ; m < 1; m++)
                    {
                        r += image[i + k][j + m].rgbtRed;
                        b += image[i + k][j + m].rgbtBlue;
                        g += image[i + k][j + m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 6.00);
                temp[i][j].rgbtBlue = round(b / 6.00);
                temp[i][j].rgbtGreen = round(g / 6.00);
            }
            // All others ( divide by 9)
            else
            {
                for (k = -1 ; k < 2; k++)
                {
                    for (m = -1 ; m < 2; m++)
                    {
                        r += image[i + k][j + m].rgbtRed;
                        b += image[i + k][j + m].rgbtBlue;
                        g += image[i + k][j + m].rgbtGreen;
                    }
                }
                temp[i][j].rgbtRed = round(r / 9.00);
                temp[i][j].rgbtBlue = round(b / 9.00);
                temp[i][j].rgbtGreen = round(g / 9.00);
            }
        }
    }

    // Copy over temp file RGB values into image address to get blurred imaged
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    // release the allocated memory
    free(temp);
    return;
}
