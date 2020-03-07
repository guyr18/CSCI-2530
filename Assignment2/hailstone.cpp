// CSCI 2530
// Assignment: 2
// Author:     Robert Guy
// File:       hailstone.cpp
// Tab stops:  4

// This program generates a hailstone sequence for any nonnegative integer n.
// A value of n is read from the standard input. And information concerning
// n is written to the standard output. Information written to the standard
// output is shown below:
//
//  1. The entire hailstone sequence starting at n, all on one line, with the numbers separated by spaces.
//
//  2. The length of the hailstone sequence that starts with n.
//
//  3. The largest number in the hailstone sequence that starts with n.
//
//  4. A longest hailstone sequence that starts with a number from 1 to n. (There might be two or more equally long sequences. Only one of those should be shown.)
//
//  5. The length of the hailstone sequence shown in part 4.
//
//  6. A hailstone sequence that starts with a number from 1 to n that contains the largest number.
//
//  7. The largest number in the hailstone sequence shown in part 6.
//
// This application only uses iteration.

#include <cstdio>
#include <algorithm>
using namespace std;

// Next(n) returns the next value
// that follows n in a hailstone sequence.

int next(int n)
{

    int i = (3 * n) + 1;

    if(n % 2 == 0)
    {

        i = n / 2;

    }

	return i;

}

// PrintSequence(n) prints the entire
// hailstone sequence that starts with n.

void PrintSequence(int n)
{

    int cur = n;
    printf("%i", n);

    while(cur != 1)
    {

        cur = next(cur);
        printf(" %i", cur);

    }
}

// Length(n) returns the length of the hailstone
// sequence that starts with n.

int length(int n)
{

    int c = 1;
    int i = n;

    while(i > 1)
    {

        i = next(i);
        c = c + 1;

    }

    return c;

}

// Largest(n) returns the largest value
// found in the hailstone sequence
// that starts with n.

int largest(int n)
{

    int m = 1;
    int i = n;

    while(i > 1)
    {

        m = max(i, m);
        i = next(i);

    }

    return m;

}

// LongestStart(n) returns the starting
// value of the longest hailstone sequence
// that starts with an integer between 1 and n.

int longestStart(int n)
{

    int m = 1;
    int startVal = 1;

    for(int i = 2; i <= n; i++)
    {

        int len = length(i);

        if(len > m)
        {

            startVal = i;
            m = len;

        }
    }

    return startVal;

}

// LargestStart(n) returns the starting
// value of the largest hailstone sequence
// that starts with an integer between 1 and n.

int largestStart(int n)
{

    int m = 1;
    int startVal = 1;

    for(int i = 2; i <= n; i++)
    {

        int larg = largest(i);

        if(larg > m)
        {

            startVal = i;
            m = larg;

        }
    }

    return startVal;

}

// PrintInitial(val, length, largest, longestStart) prints
// data passed to val, length, largest, and longestStart
// to the standard output.

void printInitial(int val, int length, int largest, int longestStart)
{

    printf("sequence: ");
    PrintSequence(val);
    printf("\n");
    printf("length: %i\n", length);
    printf("largest: %i\n", largest);
    printf("\nFor start values from 1 to %i:\n", val);
    printf("\nlongest: ");
    PrintSequence(longestStart);

}

// PrintEnd(longStartLength, largestStart, largestVal) prints
// data passed to longStartLength, largestStart, and largestVal
// to the standard output.

void printEnd(int longStartLength, int largestStart, int largestVal)
{

    printf("\nlength: %i\n", longStartLength);
    printf("\ncontaining largest: ");
    PrintSequence(largestStart);
    printf("\nlargest: %i\n", largestVal);

}

int main()
{

    int hsVal;
    int hsLength, hsLargest, hsLongestStart;
    int hsLSLength, hsLargStart, hsLargVal;
    printf("What number shall I start with? ");
    scanf("%i", &hsVal);
    hsLength = length(hsVal);
    hsLargest = largest(hsVal);
    hsLongestStart = longestStart(hsVal);
    hsLSLength = length(hsLongestStart);
    hsLargStart = largestStart(hsVal);
    hsLargVal = largest(hsLargStart);
    printInitial(hsVal, hsLength, hsLargest, hsLongestStart);
    printEnd(hsLSLength, hsLargStart, hsLargVal);
    return 0;

}
