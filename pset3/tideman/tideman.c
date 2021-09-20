// Implements a Tideman voting system

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
bool checkcycle(int W, int L);
void lock_pairs(void);
void print_winner(void);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // Places candidate indexes in order, according to preference
            ranks[rank] = i;

            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int first;
    int second;

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Record every time a candidate precedes another
            first = ranks[i];
            second = ranks[j];
            preferences[first][second]++;
        }
    }
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
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
// implemented a selection sort algorithm

void sort_pairs(void)
{


    for (int i = 0; i < pair_count; i++)
    {
        int largest = 0;
        int index;

        int first_in;
        int second_in;

        for (int j = i; j < pair_count; j++)
        {
            first_in = pairs[j].winner;
            second_in = pairs[j].loser;
            
            // Finds strongest win, and current index of that particular win
            if (preferences[first_in][second_in] - preferences[second_in][first_in] > largest)
            {
                largest = preferences[first_in][second_in] - preferences[second_in][first_in];
                index = j;
            }
        }
        
        // Only swaps largest win to the left if it's not already there
        if (index != i)
        {
            pair replace = pairs[i];
            pairs[i] = pairs[index];
            pairs[index] = replace;
        }

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
// Implemented a recursion algorithm here

void lock_pairs(void)
{
    int first;
    int second;

    for (int i = 0; i < pair_count; i++)
    {
        first = pairs[i].winner;
        second = pairs[i].loser;
        
        // Check if locking the pair will create a cycle, it not, then lock it
        
        if (!checkcycle(first, second))
        {
            locked[first][second] = true;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    // Searches for columns in locked graph that don't contain any locks (or trues)
    for (int i = 0; i < candidate_count; i++)
    {
        int false_count = 0;

        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == false)
            {
                false_count++;
            }
        }

        if (false_count == candidate_count)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}


// Recursion algorithm for checking for cycles
// I refer to a chain of winners/losers i.e. (d,a), (a,b), (b,c) as a path

bool checkcycle(int W, int L)
{
    // Exit case: if the winner is found again at the end of the "path"
    if (locked[L][W])
    {
        return true;
    }
    
    // Checks if the current loser was a winner in another pair
    for (int i = 0; i < candidate_count; i++)
    {
        // If found, then call the function again
        if (locked[L][i])
        {
            // Keep current winner "W" during every func call, so the algorithm "remembers" to look for it further down the path
            if (checkcycle(W, i))
            {
                return true;
            }

        }
    }

    return false;
}
