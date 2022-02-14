// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table1[N];


//Set Counters
int counter;
int loading;

//Allocate file
FILE *fp;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    unsigned int hashindex = 0;
    int k = strlen(word);
    char loword[k + 1];

    for (int i = 0 ; i < k + 1; i++)
    {
        loword[i] = tolower(word[i]);
    }
    // hash the word
    hashindex = hash(loword);

    // loop dictionary to check if misspelled / not in side.
    if (strcmp(table[hashindex]->word, loword) == 0)
    {
        //fprintf(stdout,"Size allcoated %lu\n", sizeof(table[hashindex]->word));
        return true;
    }
    else
    {
        // Word not in table header. check linked nodes if
        // the header has any.
        for (node *tmp =  table[hashindex]; tmp != NULL; tmp = tmp->next)
        {
            if (strcmp(tmp->word, loword) == 0)
            {
                return true;
            }
        }
    }
    return false;
}

// Hashes word to a number. Masking code taken from https://en.wikipedia.org/wiki/Mask_(computing)
unsigned int hash(const char *word)
{
    //Variables used in Hash Function



    return result;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize variables used
    int k = LENGTH + 2;
    char buffer[k];
    unsigned int hashindex = 0;
    counter = 0;

    //Initialize hashtable of pointers
    for (int i = 0 ; i < N ; i++)
    {
        table[i] = malloc(sizeof(node));
        if (table[i] == NULL)
        {
            fprintf(stdout, "table Memory not allocated");
            return 1;
        }
        strcpy(table[i]->word, "0");
        table[i]->next = NULL;
    }
    //open dictionary
    fp = fopen(dictionary, "r");
    if (fp != NULL)
    {
        loading = 1;
        while (fgets(buffer, k, fp) != NULL)
        {
            buffer[strcspn(buffer, "\n")] = '\0';
            hashindex = hash(buffer);
            //if (strncmp(table[hashindex]->word, "0", k) == 0)
            //fprintf(stdout,"%s", table[hashindex]->word);
            if(strcmp(table[hashindex]->word,"0") ==  0)
            {
                strcpy(table[hashindex]->word, buffer);
            }
            else
            {
                // Prevent collision
                // create new node and assign the new word
                node *ne = malloc(sizeof(node));
                if (ne == NULL) // check memory leak
                {
                    fprintf(stdout, "memory leak");
                    return 1;
                }
                node *tmp = table[hashindex]; // get the address of the table and assign to tmp
                strcpy(ne->word, buffer);
                ne->next = NULL;

                while (tmp->next != NULL)
                {
                    tmp = tmp->next; // loops through to find the last node
                }
                tmp->next = ne; //point last node to the new node n
            }
            counter++;
        }

        int p = 0;
        int nodes = 0;
        for (node *t = table[p]); t->next = NULL; t = t->next);
        {
            nodes++;
        }
        fprintf(stdount,"table[%i] nodes: %i", p, nodes);


        fclose(fp);
        return true;
    }
    else
    {
        loading = 0;
        return false;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Reference from loading.
    if (loading == 0)
    {
        return 0;
    }
    else
    {
        return counter;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    if (loading == 1)
    {
        //Then free memory
        for (int i = 0; i < N; i++)
        {
            while (table[i]->next != NULL)
            {
                node *tmp = table[i]->next;
                free(table[i]);
                table[i] = tmp;
            }
            free(table[i]);
        }
        return true;
    }
    else
    {
        return false;
    }
}
