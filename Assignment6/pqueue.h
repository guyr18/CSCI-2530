// CSCI 2530
// Assignment: 6
// Author: Robert Guy
// File: pqueue.h
// Tab stops: 4

// These #ifndef and #define lines make it so that, if this file is
// read more than once by the compiler, its body is skipped on all
// but the first time it is read.

#ifndef PQUEUE_H
#define PQUEUE_H

#include <cstdio>

// PQCell forward declaration.

struct PQCell;

// PriorityQueue: An object of
// this type is represented by a
// linked list that is in
// nondescending order by priority.
//
//  Field(s):
//      cell: This represents a
//      pointer to the PQCell object
//      that this PriorityQueue is
//      represented by.

struct PriorityQueue
{

    PQCell* cell;

    PriorityQueue()
    {

        cell = NULL;

    }
};

// Type definitions

// An item type is an immutable array of characters.
// Therefore, it is defined as const char*.

typedef const char* ItemT;

// A priority type is a numeric value that measures
// the priority level. Therefore, it is defined as double.

typedef double PriorityT;

// The following type definitions serve as parameterized
// functions:

typedef void (ItemPrinterT) (ItemT item);
typedef void (PriorityPrinterT) (PriorityT priority);

// Public functions

bool isEmpty(const PriorityQueue& q);
void insert(PriorityQueue& q, ItemT i, PriorityT p);
void remove(PriorityQueue& q, ItemT& i, PriorityT& p);

// The following function is a debugging tool:

void ShowPriorityQueue(const PriorityQueue& q, ItemPrinterT printItem, PriorityPrinterT& printPriority);

#endif
