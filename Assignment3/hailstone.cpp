// CSCI 2530
// Assignment: 3
// Author:     Robert Guy
// File:       hailstone.cpp
// Tab stops:  4

// This program generates a hailstone sequence for any nonnegative integer n.
// A value of n is read from the standard input. And information concerning
// n is written to the standard output. Information written to the standard
// output is shown below:
//
//  1. The entire hailstone sequence starting at n, all on one
//     line, with the numbers separated by spaces.
//
//  2. The length of the hailstone sequence that starts with n.
//
//  3. The largest number in the hailstone sequence that starts with n.
//
//  4. A longest hailstone sequence that starts with a number from 1 to n.
//
//  5. The length of the hailstone sequence shown in part 4.
//
//  6. A hailstone sequence that starts with a number from 1 to n
//     that contains the largest number.
//
//  7. The largest number in the hailstone sequence shown in part 6.
//
// This application only uses recursion.

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

// PrintSequence(n) prints the entire hailstone
// sequence that starts with n.

void PrintSequence(int n)
{

    if(n == 1)
    {

        printf("1");

    }
    else
    {

        printf("%i ", n);
        PrintSequence(next(n));

    }
}

// Length(n) returns the length of the hailstone
// sequence that starts with n.

int length(int n)
{

    if(n == 1)
    {

        return 1;

    }
    else
    {

        return length(next(n)) + 1;

    }
}

// Largest(n) returns the largest value
// found in the hailstone sequence
// that starts with n.

int largest(int n)
{

    if(n == 1)
    {

        return 1;

    }
    else
    {

        int m = largest(next(n));
        return max(n, m);

    }
}

// LongestStart(n) returns the starting
// value of the longest hailstone sequence
// that starts with an integer between 1 and n.

int longestStart(int n)
{

    if(n == 1)
    {

        return 1;

    }
    else
    {

        int m = longestStart(n - 1);
        int lengthM = length(m);
        int lengthN = length(n);

        if(lengthN < lengthM)
        {

            return m;

        }
    }

    return n;

}

// LargestStart(n) returns the starting
// value of the largest hailstone sequence
// that starts with an integer between 1 and n.

int largestStart(int n)
{

   if(n == 1)
    {

        return 1;

    }
    else
    {

        int m = largestStart(n - 1);
        int largestM = largest(m);
        int largestN = largest(n);

        if(largestN < largestM)
        {

            return m;

        }
    }

    return n;
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
