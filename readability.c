#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// call functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
double CL_Index(double L, double S);

int main()
{
    string text = get_string("Text: ");

    // count the text
    int Letter_count = count_letters(text);
    int Word_count  = count_words(text);
    int Sent_count = count_sentences(text);

    //printf("%i , %i , %i \n", Letter_count, Word_count, Sent_count);

    // Calculate Coleman-Liau Index
    double L = (double)Letter_count / (double)Word_count * 100 ;
    double S = (double)Sent_count / (double)Word_count * 100;
    int index = round(CL_Index(L, S));

    //print out results as per specification
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
    return 0;
}

// Letter Counting Function
int count_letters(string text)
{
    int lettercount = 0;
    // for loop to cycle through text and count letters.
    for (int i = 0, n = strlen(text); i < n ; i++)
    {
        if (isalpha(text[i]))
        {
            lettercount += 1;
        }
    }
    return lettercount;
}

// Word counting function
int count_words(string text)
{
    int wordcount = 0;
    // Few assumptions as per specifications.No space at beginning of text.
    // Only 1 space between words.
    for (int i = 0, n = strlen(text); i < n ; i++)
    {
        if (isalpha(text[i]) && text[i + 1] == ' ')
        {
            wordcount += 1 ;
        }
        else if (isalpha(text[i]) == false && text[i + 1] == ' ')
        {
            wordcount += 1 ;
        }
        else if (isalpha(text[i]) && text[i + 1] == '\0')
        {
            wordcount += 1 ;
        }
        else if (isalpha(text[i]) == false && text[i + 1] == '\0')
        {
            wordcount += 1 ;
        }
    }
    return wordcount;
}

// Sentence Count function
int count_sentences(string text)
{
    int sentcount = 0;

    // for the purpose of this problem, the text ending with !,?,. will be
    // considered as a sentence.
    for (int i = 0, n = strlen(text); i < n ; i++)
    {
        if (text[i + 1] == '.' || text[i] == '?' || text[i] == '!')
        {
            sentcount += 1 ;
        }
    }
    return sentcount;
}


// calculate index using the CL formula
double CL_Index(double L, double S)
{
    return (0.0588 * L) - (0.296 * S) - 15.8 ;
}