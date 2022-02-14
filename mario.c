//Mario Problem Set - Feeling more comfortable Version
//Will make use of functions to print out the pyramids

#include <cs50.h>
#include <stdio.h>
void printing(int n, string x);

int main()
{
    // Code for getting user input
    int rows;
    do
    {
        rows = get_int("Height: ");
    }
    while (rows < 1 || rows > 8);

    // Code to print column by column. Note 2 spaces required.
    for (int i = 1 ; i <= rows ; i++)
    {
        printing(rows - i, " ");
        printing(i, "#");
        printing(2, " "); // 2 spaces
        printing(i, "#");
        printf("\n");
    }

    return 0;
}


// Function print to take in "n" number of repeats and what string to print "x"
void printing(int n, string x)
{
    for (int i = 0; i < n ; i++)
    {
        printf("%s", x);
    }
}
