// CSCI 2530
// Assignment: 4
// Author:     Robert Guy
// File:       equiv.cpp
// Tab stops:  4

// This module is a tool that is designed
// to manage, combine, and test the
// equivalency of equivalence relation sets
// that range from {1, ..., n}.

#include "equiv.h"
#include <cstdio>
using namespace std;

// NewER(n) returns a new equivalence relation
// over {1, ..., n}.

ER newER(int n)
{

    ER data = new int[n + 1];

    for(int i = 1; i <= n; i++)
    {

        data[i] = i;

    }

    return data;

}

// DestroyER(e) recycles the
// memory occupied by e.

void destroyER(ER e)
{

    delete []e;

}

// Equivalent(e, x, y) returns true if x and y
// are currently in the same equivalence class
// in equivalence relation e (and returns false otherwise).

bool equivalent(ER e, int x, int y)
{

   return leader(e, x) == leader(e, y);

}

// Leader(e, x) returns the leader of
// x in equivalence relation e.

int leader(ER e, int x)
{

    if(e[x] == x)
    {

        return x;

    }
    else
    {

        return leader(e, e[x]);

    }
}

// Combine(e, x, y) merges the equivalence
// classes of x and y in equivalence relation e.

void combine(ER e, int x, int y)
{

    int xLeader = leader(e, x);
    int yLeader = leader(e, y);

    if(xLeader != yLeader)
    {

        e[yLeader] = xLeader;

    }
}

// ShowER(e, n) shows the boss array e of equivalence relation
// e, where e is over {1, ..., n}.

void showER(ER e, int n)
{

    printf("k\tk\'s boss\n");

    for(int i = 1; i <= n; i++)
    {

        printf("%i\t%i\n", i, e[i]);

    }
}
