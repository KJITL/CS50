#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Max number of candidates
#define MAX 9 // maximum number of candidates we can have @@@@

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX]; // consider each pair , how many the i is higher over j @@@@

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner; // index inside candidate array of winner between two candidates
    int loser; // ^ the loser :(
}
pair;

// Array of candidates
string candidates[MAX]; //array storing candidates names @@@@@
pair pairs[MAX * (MAX - 1) / 2]; // from candidate , maximum pairs can get

int pair_count; // num of pairs in pair array i guess
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
bool is_cycle(int winner, int loser); // my special function
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

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}


// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // validate the name if exist insde candidate array or not , if so , add his vote , else return false

    // for each candidate inside candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0) // if equal to zero will be true
        {
            // store candidate index inside rank array with 'rank index'
            ranks[rank] = i;
            return true; // succuffuly ranking
        }
    }

    // candidate not found
    return false;
}



// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // go through ranks array,

    // for each element inside ranks[]
    for (int i = 0; i < candidate_count; i++)
    {
        // take from and to candidates from ranks array
        for (int j = i + 1; j < candidate_count; j++)
        {
            int from_candidate = ranks[i];
            int to_candidate = ranks[j];
            // increment an preferences as a voter prefer this candidate over that candidate
            preferences[from_candidate][to_candidate]++;
        }

    }

}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    // for each elemnt in  ' row or from candidate '
    for (int i = 0; i < candidate_count; i++)
    {
        // for each elemnt in column ' over candidate '
        for (int j = i + 1 ; j < candidate_count; j++)
        {

            // comparing , if i bigger than j , set i winner and j loser in pairs array ' pair_count index ' , increment pair_count
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i; // if i over j , is bigger than flip index around , its i winner and j loser
                pairs[pair_count].loser = j;
                pair_count++; // increment pair count as we just add a pair
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j; // if j over i , is bigger than flip index around , its j winner and i loser
                pairs[pair_count].loser = i;
                pair_count++; // increment pair count as we just add a pair
            }


        }

    }

    //test code

    //for (int x = 0; x < pair_count; x++)
    //{
    //    printf("index=%i, (winner= %i,loser= %i)\n", (x), (pairs[x].winner), (pairs[x].loser));
    //}
    //printf("\naaddd\n");
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // create array of winning diffrences with respect to each pair in pairs array
    int diffrences[pair_count];



    // store all winning pair defrences in prefrences array inside diffrences single array
    for (int i = 0; i < pair_count; i++)
    {
        diffrences[i] = preferences[pairs[i].winner][pairs[i].loser] -
                        preferences[pairs[i].loser][pairs[i].winner]; // winner prefrence - loser prefrence
    }



    // array of sorted pairs to store the final sorted pair of array
    pair sorted_pairs[pair_count];


    // for each index in new sorted pairs
    for (int j = 0; j < pair_count; j++)
    {
        int highest_diffrence = 0; // highest diffrences
        int highest_index = 0; // highest index

        for (int i = 0; i < pair_count; i++) // search for highest diffrences to be in the first sorted pairs , and so on.
        {
            if (diffrences[i] > highest_diffrence)
            {
                highest_index = i;
                highest_diffrence = diffrences[i];
            }
        }

        // store the highest diffrences index inside sorted pair
        sorted_pairs[j].winner = pairs[highest_index].winner;
        sorted_pairs[j].loser = pairs[highest_index].loser;

        // make the inserted elemnt to be zero, till we end with the array
        diffrences[highest_index] = 0;

    }


    // re arrange original pairs array

    for (int o = 0; o < pair_count; o++)
    {
        pairs[o].winner = sorted_pairs[o].winner;
        pairs[o].loser = sorted_pairs[o].loser;
    }



    //for (int x = 0; x < pair_count; x++)
    //{
    //    printf("index=%i, (winner= %i,loser= %i)\n", (x), (pairs[x].winner), (pairs[x].loser));
    //}
    //printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");

}







// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int count = 0;
    // from sorted pairs array , we check each pair and lock them
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        //test
        //printf("%i, %i\n", winner , loser);

        // we check if that winner is already winning and same time is not the loser now. ' cycle method test '
        if ((is_cycle(winner, loser) == false))
        {
            // test
            //printf("True!");

            locked[winner][loser] = true;
        }
        else if (count < 3) // impossible to be cycle with 2 or lower !
        {
            locked[winner][loser] = true;
        }
        count++;
    }

}


bool is_cycle(int winner, int loser)
{
    // for every column in losing candidate row
    if (loser != pairs[0].winner) // first winner exeption
    {
        for (int c = 0; c < candidate_count; c++)
        {
            if (locked[loser][c] == true)
            {
                return true;
            }
        }

    }
    return false;

}




// Print the winner of the election
void print_winner(void)
{
    // for each column in locked 2d array

    // if some one have full falses, then he is the winner becuase no one beat him

    //

    for (int i = 0; i < candidate_count; i++)
    {
        bool legit_column = true; // its always true , unlease there some one go into the candidate
        for (int j = 0; j < candidate_count; j++)
        {

            if (locked[j][i] == true) // there is someone go into candidate ! ?
            {
                legit_column = false;
            }


        }
        if (legit_column)
        {
            printf("%s\n", candidates[i]);
            break;
        }

    }

}