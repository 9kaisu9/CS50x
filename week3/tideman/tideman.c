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
void swap_pairs(pair *p1, pair *p2);
bool has_cycle(int winner, int loser);

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
    // Set all preferences to 0
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            preferences[i][j] = 0;
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

    for (int i = 0; i < pair_count; i++)
    {
        printf("%i   %i   %i\n", pairs[i].winner, pairs[i].loser, preferences[pairs[i].winner][pairs[i].loser]);
    }


    lock_pairs();

    for (int a = 0; a < candidate_count; a++)
    {
        for (int b = 0; b < candidate_count; b++)
        {
            printf("%i", locked[a][b]);
        }
        printf("\n");
    }


    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int a = 0; a < candidate_count; a++)
    {
        for (int b = a + 1; b < candidate_count; b++)
        {
            preferences[ranks[a]][ranks[b]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int a = 0; a < candidate_count; a++)
    {
        for (int b = a + 1; b < candidate_count; b++)
        {
            if (preferences[a][b] > preferences[b][a])
            {
                pairs[pair_count].winner = a;
                pairs[pair_count].loser = b;
                pair_count++;
            }
            if (preferences[b][a] > preferences[a][b])
            {
                pairs[pair_count].winner = b;
                pairs[pair_count].loser = a;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    for (int c = 0; c < pair_count; c++)
    {
        for (int a = 0; a < (pair_count - 1 - c); a++)
        {
            if (preferences[pairs[a].winner][pairs[a].loser] < preferences[pairs[a + 1].winner][pairs[a + 1].loser])
            {
                swap_pairs(&pairs[a], &pairs[a + 1]);
            }
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[i][j] == true)
            {
                break;
            }
            if (i == candidate_count - 1)
            {
                printf("%s\n", candidates[j]);
                return;
            }
        }
    }
}

void swap_pairs(pair *p1, pair *p2)
{
    pair tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;
        if(!has_cycle(winner, loser))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

bool has_cycle(int winner, int loser)
{
    if (locked[loser][winner] == true)
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i] == true && has_cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}



