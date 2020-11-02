// CSCI 2530
// Assignment: 6
// Author: Robert Guy
// File: pqueue.cpp
// Tab stops: 4

#include "pqueue.h"
#include <cstdlib>
using namespace std;

// PQCell: An object of this type
// contains an item, a priority,
// and a pointer to the next cell
// in the linked list.
//
//  Field(s):
//
//      nextCell: This is a pointer that
//      represents the cell that follows
//      this cell in the current priority
//      queue.
//
//      item: This represents
//      the item found within
//      this cell.
//
//      priorityLevel: This represents
//      the priority level of this cell.
//

struct PQCell
{

    PQCell* nextCell;
    ItemT item;
    PriorityT priorityLevel;

    PQCell(PQCell* nc, ItemT i, PriorityT p)
    {

        nextCell = nc;
        item = i;
        priorityLevel = p;

    }
};

// IsEmpty(q) returns true if q is empty
// and returns false if q is not empty.

bool isEmpty(const PriorityQueue& q)
{

    return q.cell == NULL;

}

// InsertCell(L, item, priority) inserts a cell
// with item i and priority p into linked list L.

void insertCell(PQCell*& L, ItemT item, PriorityT priority)
{

    if(L == NULL)
    {

        L = new PQCell(NULL, item, priority);

    }
    else if(L->priorityLevel > priority)
    {

        L = new PQCell(L, item, priority);

    }
    else
    {

        insertCell(L->nextCell, item, priority);

    }
}

// Insert(q, i, p) inserts item i, with priority p, into q.

void insert(PriorityQueue& q, ItemT i, PriorityT p)
{

    insertCell(q.cell, i, p);

}

// Remove(q, i, p) removes the item i from q that has
// the smallest priority, p.

void remove(PriorityQueue& q, ItemT& i, PriorityT& p)
{

    if(!isEmpty(q))
    {

        if(q.cell != NULL)
        {

            PQCell* lowestPriorityCell = q.cell;
            i = q.cell->item;
            p = q.cell->priorityLevel;
            q.cell = q.cell->nextCell;
            delete lowestPriorityCell;

        }
    }
    else
    {

        printf("Attempt to remove from an empty priority queue");
        exit(1);

    }
}

// ShowPriorityQueue(q, printItem, printPriority) prints the
// current contents of priority queue q. It calls parameter(s)
// printItem to print item i and printPriority to print
// priority p.

void ShowPriorityQueue(const PriorityQueue& q, ItemPrinterT printItem, PriorityPrinterT& printPriority)
{

    printf("Showing priority queue contents: \n");

    for(PQCell* p = q.cell; p != NULL; p = p->nextCell)
    {

        printf("Item: [ ");
        printItem(p->item);
        printf("]\n");
        printf("Priority: [ ");
        printPriority(p->priorityLevel);
        printf("]\n\n");

    }
}
