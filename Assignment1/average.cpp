// CSCI 2530
// Assignment: 1
// Author:     Robert Guy
// File:       average.cpp
// Tab stops:  4

//=======================================================
// This program does two main steps.
//
// 1. It reads 3 integers and writes their median.
//
// 2. After that, it reads integers until it reads -1.
//    Then it writes the mean of those integers, excluding
//    -1.
//
// For example, if the input is
//   3 8 2 10 11 15 -1
// then the output is:
//
// The median of (3, 8, 2) is 3.
// The mean of (10, 11, 15) is 12.00
//=======================================================

#include <cstdio>
#include <algorithm>
using namespace std;

// ComputeMedian() reads, prints, and computes
// the median of the inputted data.
void computeMedian()
{

    int tempOne, tempTwo, tempThree;
    int valOne, valTwo;
    int median;
    scanf("%i%i%i", &tempOne, &tempTwo, &tempThree);
    int lowestTwoThree = min(tempTwo, tempThree);
    int maxTwoThree = max(tempTwo, tempThree);
    valOne = min(tempOne, lowestTwoThree);

    if(valOne == tempOne)
    {

        valTwo = lowestTwoThree;

    }
    else
    {

        valTwo = min(tempOne, maxTwoThree);

    }

    median = valTwo;
    printf("\nThe median of (%i, %i, %i)", tempOne, tempTwo, tempThree);
    printf(" is %i", median);

}

// ComputeMean() reads, prints, and computes
// the mean of the inputted data.
void computeMean()
{

    double sum = 0.0;
    double mean = 0.0;
    int a = 0;
    int count = 0;
    printf("\nThe mean of (");

    while(scanf("%i", &a) > 0 && a != -1)
    {

        if(count > 0)
        {

            printf(", ");

        }

        printf("%i", a);
        sum = sum + a;
        count = count + 1;

    }

    mean = sum / count;
    printf(") is %0.2lf\n", mean);

}

int main()
{

    computeMedian();
    computeMean();
    return 0;

}
