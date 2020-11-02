// CSCI 2530
// Assignment: 7
// Author:     Robert Guy
// File:       event.h
// Tab stops:  4

// **Say what this program does here.  (replace this comment)**

#ifndef EVENT_H
#define EVENT_H

struct Event
{

    int sender;
    int receiver;
    double time;

    Event(int s, int r, double t)
    {

        sender = s;
        receiver = r;
        time = t;

    }
};

#endif
