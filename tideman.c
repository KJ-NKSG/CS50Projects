#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool cyclecheck(int n, int m, int p);

int main(int argc, string argv[])
{

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;

    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //rank input = j (starting from 0)
    //name input = the voter selected candidate name in order
    //ranks[] = array that stores rank order (1,2,3) for the candidate index no.
    // rank 1 = david example.
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j], name) == 0)
        {
            ranks[rank] = j;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i <= candidate_count - 2; i++)
    {
        for (int j = i + 1; j <= candidate_count - 1; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                //printf("Winner:%s, Loser:%s\n",candidates[pairs[pair_count].winner],candidates[pairs[pair_count].loser]);
                pair_count += 1;
            }
        }
    }
    //printf("%i\n",pair_count);
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Use Bubble Sort with breakout for improved efficiency for best case scenario

    for (int i = 0; i < pair_count; i++)
    {
        bool check = false;
        for (int j = 0; j < pair_count - i - 1; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] < preferences[pairs[j + 1].winner][pairs[j + 1].loser])
            {
                int temp1 = pairs[i].winner;
                int temp2 = pairs[i].loser;

                pairs[i].winner = pairs[i + 1].winner;
                pairs[i].loser = pairs[i + 1].loser;

                pairs[i + 1].winner = temp1;
                pairs[i + 1].loser = temp2;

                check = true;
            }
        }
        if (check == false)
        {
            break;
        }
    }
    //for (int i = 0; i < pair_count; i++)
    //{
    //     printf("%i : %i , strength: %i\n" ,pairs[i].winner, pairs[i].loser,preferences[pairs[i].winner][pairs[i].loser]);
    //}

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // set first edge
    locked[pairs[0].winner][pairs[0].loser] = true;

    for (int i = 1 ; i < pair_count ; i++)
    {
        if (cyclecheck(i, pairs[i].winner, pairs[i].loser) == true)
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
            //printf("i: %i, %d\n", i, locked[pairs[i].winner][pairs[i].loser]);
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int count = 0;
    string name;

    // Find the source which basically means a column in the
    // locked matrix that has all falses ( meaning no losses at all)

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                count += 1;
            }
        }
        if (count == candidate_count)
        {
            name = candidates[i];
        }
        else
        {
            count = 0;
        }
    }

    printf("%s\n", name);
    return;
}

//establish new recursive function for lockedpairs
// m = winner candidate index in the checking pairs before it is about to be locked
// p = loser candidate index in the checking pairs before it is about to be locked

bool cyclecheck(int n, int m, int p)
{
    // base to exit recursive function. check if there is a cycle, if not cont.
    // printf("paircount = %i\n", n);
    int route = 0;
    int state = 0;

    if (n == 0)
    {
        return true;
    }

    if (locked[pairs[n - 1].winner][pairs[n - 1].loser] == true)
    {
        route = 1;
    }

    if (m == pairs[n - 1].loser && p == pairs[n - 1].winner)
    {
        state = 1;
    }
    else if (m == pairs[n - 1].loser)
    {
        state = 2;
    }

    if (route == 1 && state == 2)
    {
        m = pairs[n - 1].winner;
    }

    if (route == 1 && state == 1)
    {
        //printf("false\n");
        return false;
    }

    return cyclecheck(n - 1, m, p);
}
