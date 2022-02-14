#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

int main(int argc, string argv[])
{


    // Validate if Key provided is correct
    if (argc != 2)
    {
        printf("Check that only 1 Key argument inputted after ./substitution. \n");
        return 1;
    }

    // Assign length of Key
    int n = strlen(argv[1]);
    // Check length of key is 26
    if (n != 26)
    {
        printf("You must enter a key of length 26.\n");
        return 1;
    }

    // Next check if all the are letters

    for (int i = 0; i < n ; i++)
    {
        if (isalpha(argv[1][i]) == false)
        {
            printf("You must enter a key in alphabets only.\n");
            return 1;
        }
    }

    // check for duplicates
    for (int i = 0; i < n - 1 ; i++)
    {
        int m = i + 1;
        for (int j = m ; j < n ; j++)
        {
            if (tolower(argv[1][i]) == tolower(argv[1][j]))
            {
                printf("You must not have duplicated letters in the key.\n");
                return 1;
            }
        }
    }

    // Get user to input text to be cypher.
    string plaintext = get_string("plaintext: ");

    // Cypher the text using the key provide in the commandline
    // need to know the location of plaintext letter in relation to Key
    // based on letter order in base.

    char base[27] = {"abcdefghijklmnopqrstuvwxyz"};
    printf("ciphertext: ");

    for (int i = 0, p = strlen(plaintext) ; i < p ; i++)
    {
        if (isalpha(plaintext[i]) == false) //print out non letters
        {
            printf("%c", plaintext[i]);
        }
        else
        {
            for (int j = 0; j < 26; j++)// loop through base to get location
            {
                if (tolower(plaintext[i]) == base[j])
                {
                    if (islower(plaintext[i]) == 0)
                    {
                        printf("%c", toupper(argv[1][j]));
                    }
                    else
                    {
                        printf("%c", tolower(argv[1][j]));
                    }
                }
            }
        }
    }
    printf("\n");
    return 0;
}