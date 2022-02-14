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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // initialize the temp pointer to hold the modified pixels
    RGBTRIPLE(*temp)[width] = calloc(height, sizeof(image[width]));

    int max = 255; // max pixel rgb value
    int a = 0, b = 0, c = 0;

    // initialize the kernals Gx and Gy
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Loop through each pixel and calculate the modified pixles based on sobel function
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int Rx = 0, Bx = 0, GRx = 0;
            int Ry = 0, By = 0, GRy = 0;

            if (i == 0 && j == 0) // Top left Corner
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 1 ; k < 3; k++)
                {
                    for (int m = 1; m < 3; m++)
                    {
                        Rx += (image[k - 1][m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[k - 1][m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[k - 1][m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[k - 1][m - 1].rgbtRed * Gy[k][m]);
                        By += (image[k - 1][m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[k - 1][m - 1].rgbtGreen * Gy[k][m]);
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }

            else if (i == 0 && j == width - 1) // Top right Corner
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 1; k < 3 ; k++)
                {
                    for (int m = 0; m < 2; m++)
                    {

                        Rx += (image[i + k - 1][j + m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[i + k - 1][j + m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[i + k - 1][j + m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[i + k - 1][j + m - 1].rgbtRed * Gy[k][m]);
                        By += (image[i + k - 1][j + m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[i + k - 1][j + m - 1].rgbtGreen * Gy[k][m]);
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }
            else if (i == height - 1 && j == 0) // bottom left Corner
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 0 ; k < 2 ; k++) // actual k = 1 to 2
                {
                    for (int m = 1; m < 3; m++)
                    {
                        Rx += (image[i + k - 1][m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[i + k - 1][m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[i + k - 1][m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[i + k - 1][m - 1].rgbtRed * Gy[k][m]);
                        By += (image[i + k - 1][m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[i + k - 1][m - 1].rgbtGreen * Gy[k][m]);
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }
            else if (i == height - 1 && j == width - 1)// bottom right Corner
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 0; k < 2; k++)
                {
                    for (int m = 0; m < 2; m++)
                    {
                        Rx += (image[i + k - 1][j + m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[i + k - 1][j + m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[i + k - 1][j + m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[i + k - 1][j + m - 1].rgbtRed * Gy[k][m]);
                        By += (image[i + k - 1][j + m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[i + k - 1][j + m - 1].rgbtGreen * Gy[k][m]);
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }

            else if (i == 0 && j != 0 && j != width - 1) // first row
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 1; k < 3; k++)
                {
                    for (int m = 0; m < 3; m++)
                    {
                        Rx += (image[i + k - 1][j + m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[i + k - 1][j + m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[i + k - 1][j + m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[i + k - 1][j + m - 1].rgbtRed * Gy[k][m]);
                        By += (image[i + k - 1][j + m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[i + k - 1][j + m - 1].rgbtGreen * Gy[k][m]);
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }
            else if (i == height - 1 && j != 0 && j != width - 1) // last row
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 0; k < 2; k++)
                {
                    for (int m = 0; m < 3; m++)
                    {
                        Rx += (image[i + k - 1][j + m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[i + k - 1][j + m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[i + k - 1][j + m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[i + k - 1][j + m - 1].rgbtRed * Gy[k][m]);
                        By += (image[i + k - 1][j + m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[i + k - 1][j + m - 1].rgbtGreen * Gy[k][m]);
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }
            else if (i != 0 && i != height - 1 && j == 0) // First column
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 0; k < 3; k++)
                {
                    for (int m = 1; m < 3; m++)
                    {
                        Rx += (image[i + k - 1][j + m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[i + k - 1][j + m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[i + k - 1][j + m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[i + k - 1][j + m - 1].rgbtRed * Gy[k][m]);
                        By += (image[i + k - 1][j + m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[i + k - 1][j + m - 1].rgbtGreen * Gy[k][m]);
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }
            else if (i != 0 && i != height - 1 && j == width - 1) // last column
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 0; k < 3; k++)
                {
                    for (int m = 0; m < 2; m++)
                    {
                        Rx += (image[i + k - 1][j + m - 1].rgbtRed * Gx[k][m]);
                        Bx += (image[i + k - 1][j + m - 1].rgbtBlue * Gx[k][m]);
                        GRx += (image[i + k - 1][j + m - 1].rgbtGreen * Gx[k][m]);

                        Ry += (image[i + k - 1][j + m - 1].rgbtRed * Gy[k][m]);
                        By += (image[i + k - 1][j + m - 1].rgbtBlue * Gy[k][m]);
                        GRy += (image[i + k - 1][j + m - 1].rgbtGreen * Gy[k][m]);

                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }
            // All others
            else
            {
                // Cycle through kernal Matrix and sum it up
                for (int k = 0; k < 3; k++)
                {
                    for (int m = 0; m < 3; m++)
                    {
                        Rx += image[i + k - 1][j + m - 1].rgbtRed * Gx[k][m];
                        Bx += image[i + k - 1][j + m - 1].rgbtBlue * Gx[k][m];
                        GRx += image[i + k - 1][j + m - 1].rgbtGreen * Gx[k][m];

                        Ry += image[i + k - 1][j + m - 1].rgbtRed * Gy[k][m];
                        By += image[i + k - 1][j + m - 1].rgbtBlue * Gy[k][m];
                        GRy += image[i + k - 1][j + m - 1].rgbtGreen * Gy[k][m];
                    }
                }
                a = round(sqrt(pow(Rx, 2.0) + pow(Ry, 2.0)));
                b = round(sqrt(pow(Bx, 2.0) + pow(By, 2.0)));
                c = round(sqrt(pow(GRx, 2.0) + pow(GRy, 2.0)));
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
                temp[i][j].rgbtRed = a;
                temp[i][j].rgbtBlue = b;
                temp[i][j].rgbtGreen = c;
            }
        }
    }

    // Copy over temp file RGB values into image address to get blurRed image
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    // free memory
    free(temp);
    return;
}

