# CS50 Problem sets

## Caesar
Problem:
Implement a program called "caesar" that encrypts messages using Caesar's cipher, which shifts each letter in the plaintext by a given key. The program should take the key as a command-line argument and encrypt the user-provided plaintext, preserving the case of the original message

Example:
$ ./caesar 13
plaintext:  HELLO
ciphertext: URYYB


## Credit
Problem:
The problem set involves writing a program in C called "credit.c" that validates credit card numbers using Luhn's algorithm. The program prompts the user for a credit card number and then determines if it is a valid American Express, MasterCard, or Visa card number based on their respective formats. The program's output should be either "AMEX\n", "MASTERCARD\n", "VISA\n", or "INVALID\n" for valid and invalid credit card numbers. The input is assumed to be entirely numeric and devoid of hyphens or leading zeroes, but it is not assumed to fit in an int data type.

Example:
$ ./credit
Number: 4003-6000-0000-0014
Number: foo
Number: 4003600000000014
VISA


## filter
Problem:
An image filtering program, often implemented in C, is a software program that modifies image pixels to achieve visual effects. Examples of filters include grayscale, which converts an image to grayscale by averaging the red, green, and blue values of each pixel. Image filtering is commonly used in image processing applications for artistic effects, image correction, or feature extraction in computer vision tasks.


## Plurity
Problem:
The problem is to implement a program in C called "plurality" that simulates a plurality vote election. The program takes command-line arguments as candidate names, allows users to input the number of voters, and then lets each voter input their vote by entering the name of the candidate they are voting for. The program should then update the vote count for each candidate and print the winner(s) of the election.

Example:
$ ./plurality Alice Bob Charlie
Number of voters: 4
Vote: Alice
Vote: Bob
Vote: Charlie
Vote: Alice
Alice


## Runoff
Problem:
The program implements a ranked-choice voting system, specifically the instant runoff method. It takes input from users representing voter preferences and determines the winner based on ranked preferences. It handles ties, elimination of candidates, and requires all voters to rank all candidates. The program is implemented in C and can be downloaded as a ZIP file from a provided link.

Example:
./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Bob
Rank 3: Charlie

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Alice
Rank 3: Charlie

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice


## Tideman
Problem:
The Tideman voting method is a ranked-choice voting system that determines the Condorcet winner of an election, if one exists. It works by constructing a graph of candidates, where arrows indicate head-to-head matchup victories. The method locks in the strongest edges first based on the margin of victory, avoiding cycles in the graph. The winner is the candidate with no arrows pointing at them, or the source of the graph.

Example:
$ ./tideman Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Charlie





