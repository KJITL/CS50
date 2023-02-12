#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100 // max number of people who can vote
#define MAX_CANDIDATES 9 // max people who to vote for

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES]; // array that stores voters and candidates

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n"); // exit if there's no name with the user input to vote for
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining  candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates ' why ? becuase in previous if statment , we could not get the winner , therefore , elimnation will be.
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // validate the name , like do if and only if the name is exsist
    // for each name inside candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidate in the list
        if (strcmp(candidates[i].name, name) == 0)
        {
            // update preference array due to these factors
            preferences[voter][rank] = i; //go to voter raw, rank column , put i'candidate' number inside the cell
            return true;
        }

    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // go for each voter in preference list
    for (int voter_index = 0; voter_index < voter_count; voter_index++)
    {
        // for each rank
        for (int rank = 0; rank < candidate_count; rank++)
        {
            int selected_cand = preferences[voter_index][rank]; // store the voted candidate index
            if (!candidates[selected_cand].eliminated)// if this candidate in this cell is true and not elemenated, update voted value and go next voter
            {
                candidates[selected_cand].votes++;
                break;
            }
        }
    }

}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // store the required winning number " greater than half "
    int win_num = floor(voter_count / 2) + 1;

    // for each votes inside candidate array , dedicte who have win num to print his name and return true
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes >= win_num) // if we find some one has equal or more than half, print it and return true
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min_vote = MAX_VOTERS; // initialize min votes with max possible votes could be , to be reduced correctly and closer to answer

    // for each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if ((candidates[i].votes < min_vote)
            && (!candidates[i].eliminated)) // if there is candidate that is not eliminated and have less than min vote
        {
            min_vote = candidates[i].votes; // update the value with new min vote
        }
    }

    return min_vote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // for each candidate inside candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes != min && !candidates[i].eliminated) // if there element not have minimum , ' not tie '
        {
            return false; // becuase clearly not tie or ' not all minimum '
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // for each candidate inside candidate array
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min) // if there element not have minimum , ' not tie '
        {
            candidates[i].eliminated = true; // becuase clearly not tie or ' not all minimum '
        }
    }

}
