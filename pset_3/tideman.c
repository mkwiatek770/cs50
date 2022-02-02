#include <cs50.h>
#include <stdio.h>
#include <string.h>

/*
Put more formally, the Tideman voting method consists of three parts:

1. Tally: Once all of the voters have indicated all of their preferences, determine,
       for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
2. Sort: Sort the pairs of candidates in decreasing order of strength of victory,
      where strength of victory is defined to be the number of voters who prefer the preferred candidate.
3. Lock: Starting with the strongest pair, go through the pairs of candidates
      in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.

Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner!
*/


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j. this is adjacent matrix
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

    // print matrix (temporary)
    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }

    add_pairs();
    // pairs (unsorted)
    for(int i = 0; i < pair_count; i++){
        printf("%i. winner=%i loser=%i\n", i, pairs[i].winner, pairs[i].loser); 
    }
    sort_pairs();
    // pairs (sorted)
    for(int i = 0; i < pair_count; i++){
        printf("%i. winner=%i loser=%i\n", i, pairs[i].winner, pairs[i].loser); 
    }
    lock_pairs();
    // print locked matrix (temporary)
    for(int i = 0; i < candidate_count; i++){
        for(int j = 0; j < candidate_count; j++){
            printf("%i ", locked[i][j]);
        }
        printf("\n");
    }
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for(int i = 0; i < candidate_count; i++){
        if (strcmp(candidates[i], name) == 0){
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    int winner, loser;
    for (int i = 0; i < candidate_count - 1; i++){
        winner = ranks[i];
        for (int j = i + 1; j < candidate_count; j++){
            loser = ranks[j];
            preferences[winner][loser]++; // maybe += 1 would be better ..
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++){
        for (int j = 0; j < candidate_count; j++){
            if (preferences[i][j] > preferences[j][i]){
                pair new;
                new.winner = i;
                new.loser = j;
                pairs[pair_count] = new;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// TODO merge sort
void sort_pairs(void)
{
    int swap_counter = 0;
    int iteration = 0;
    do {
        swap_counter = 0;
        for (int i = 0; i < pair_count - 1 - iteration; i++){
            pair p1 = pairs[i];
            pair p2 = pairs[i + 1];
            int difference = preferences[p1.winner][p1.loser] - preferences[p2.winner][p2.loser];
            if (difference < 0){
                // swap
                pair temp;
                temp.winner = p1.winner;
                temp.loser = p1.loser;
                pairs[i] = p2;
                pairs[i + 1] = temp;
                swap_counter++;
            }
        }
        iteration++;
    } while (swap_counter >  0);
    return;
}


// "skips middle pair cycle": https://i.imgur.com/mdsDidq.png
// "skips final pair cycle" https://i.imgur.com/OJosjRe.png
bool cycle_checker(int target, int other_node){
    // out-of recurrence check
    if (locked[other_node][target] == true){
        return true;
    }
    // loser's lock-ins
    for (int i = 0; i < candidate_count; i++){
        if (locked[other_node][i] == true){
            if (cycle_checker(target, i) == true){
                return true;
            }
        }
    }
    return false;
}


// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++){
        pair p = pairs[i];
        // for first two it's always safe
        if (i == 0 || i == 1){
            locked[p.winner][p.loser] = true;
        }
        else {
            if (!cycle_checker(p.winner, p.loser)){
                locked[p.winner][p.loser] = true;
            }
        }
    }
}


// Print the winner of the election
void print_winner(void)
{
    // inny pomysl
    // petla to posortowanych parach
        // wez wygreanego
        // petla po 

    int locks_counter;
    for (int i = 0; i < pair_count; i++){
        locks_counter = 0;
        for (int j = 0; j < pair_count; j++){
            if (locked[j][i] == true){
                locks_counter++;
            }
        }
        if (locks_counter == 0){
            printf("%s\n", candidates[i]);
        }
    }
    return;
}