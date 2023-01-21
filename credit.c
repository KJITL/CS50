#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    //(1) ask the user to prompt credit card number

    long credit = get_long("Number: ");

    //create a copied version of credit card ' to use it in knowing credit card type down '
    long copyCredit = credit;

    //(2) applying checksum method ' if invalid , print invalid then exit '

    // loop till we finish with the whole 'credit number' values itereratly

    int evenNums = 0; // sum of the starting with the number’s second-to-last digit
    int oddNums = 0; // sum of others digits
    bool valid = true; // if valid check sum

    while (credit != 0) // while we dont end with all digits.
    {
        // take the last right most digit ' that just sum it '
        oddNums = oddNums + (credit % 10);
        credit = credit / 10; // cut right most after sum it.



        // take the even from write numbers ' with mulitplying it by 2 '

        // but before , lets sure that if numebr more than 9 , there will be 2 digits
        // therefore we should seperate them and add them digitly

        if ((2 * (credit % 10)) > 9)  // for example if the digit is 6 , then 6*2 = 12 , then 1+2 = 3 , we sum only 3 .
        {
            // take the number that content of 2 digits ' the mulitple of digit '
            int n = 2 * (credit % 10);

            // sum its digits
            int s = (n % 10) + (n / 10);

            // sum the summation 's' in evenNums
            evenNums = evenNums + s;
        }
        else
        {
            evenNums = evenNums + (2 * (credit % 10));

        }
        credit = credit / 10; // cut right most after sum it.

    }
    // sum the as luhm law says
    int sum = evenNums + oddNums;
    //printf("%i\n",sum);
    // check last digit of summation , if = 0 , then its valid, otherwise change it to invalid.
    if (sum % 10 != 0)
    {
        valid = false;
    }


    //(3) ' if valid ' count number of digits & know the first digit ,,, then print the card name with respect to these information

    if (valid)
    {
        //count the length
        int length = 0;
        long lcopyCredit = copyCredit;
        while (lcopyCredit != 0)
        {
            lcopyCredit = lcopyCredit / 10;
            length++;
        }
        //printf("%i\n",length);

        //check what this length belong to

        // chech if its length 15 , and if wee take first two dijits is equal to 34 or 37
        if ((length == 15) && ((int)(copyCredit / pow(10, 13)) == 34 || (int)(copyCredit / pow(10, 13)) == 37)) //if american express
        {
            printf("AMEX\n");
        }
        // chech if its length 16 , and if wee take first two dijits is between  50 or 56 exclusive
        else if ((length == 16) && ((int)(copyCredit / pow(10, 14)) > 50 && (int)(copyCredit / pow(10, (length - 2)) < 56))) //mastercard
        {
            printf("MASTERCARD\n");
        }
        // chech if its length 13 or 16 , and if wee take first dijit is equal to 4
        else if ((length == 13 || length == 16) && (int)(copyCredit / pow(10, (length - 1))) == 4) //VISA
        {
            printf("VISA\n");
        }
        else
        {
            // other type
            printf("INVALID\n");
        }



    }
    else
    {
        printf("INVALID\n");
    }
}