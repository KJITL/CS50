#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

void ciphertext(string plaintext, int key);

int main(int argc, string argv[])
{

    if (argc != 2) // if number of argumnets not 2  
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!isdigit(argv[1][i])) // check if the number is digit only
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }


    }
    int key = atoi(argv[1]);

    // (2) ask the user for plain

    string plaintext = get_string("plaintext:  ");

    // (3) Cypher & print it.
    ciphertext(plaintext, key);
    return 0;

}


// cipher text function

void ciphertext(string plaintext, int key)
{
    printf("ciphertext: ");

    // for each elment in plaintext, if its aplha , print its corrspended key " check case sensetive "
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {

        if (isalpha(plaintext[i])) // check if alphabitical
        {

            // if it lower case  char
            if (islower(plaintext[i]))
            {
                if ((int)(plaintext[i] + key) > 122)
                {
                    int num = (((plaintext[i] - 96) + key)) % 26 ;
                    printf("%c", (96 + num));
                }
                else
                {
                    printf("%c", (plaintext[i] + key));
                }

            }
            else if (isupper(plaintext[i])) // if it upper case char
            {

                if ((int)(plaintext[i] + key) > 90)
                {
                    int num = (((plaintext[i] - 64) + key)) % 26 ;
                    printf("%c", (64 + num));
                }
                else
                {
                    printf("%c", (plaintext[i] + key));
                }

            }

        }
        else // if its any other char
        {
            printf("%c", (plaintext[i]));
        }

    }
    printf("\n");


}
