// CSCI 2530
// Assignment: 7
// Author:     Robert Guy
// File:       dijkstra.cpp
// Tab stops:  4

// This application uses Dijkstra's shortest
// path algorithm and reads information about
// a weighted graph from the standard input.
// And furthermore, has three components:
//
//  1. An input graph description that is
//     derived from the standard input.
//
//  2. The shortest path from the starting
//     vertex to the ending vertex.
//
//  3. The distance (or time) from the starting
//     vertex to the ending vertex. This is
//     derived from the shortest path.
//
//  An example of the input that this application
//  requests could be as follows:
//
//  5
//  1 2 9.0
//  1 3 12.0
//  2 4 18.0
//  2 3 6.0
//  2 5 20.0
//  3 5 15.0
//  0
//  1 5
//
//  The first line is a number that describes
//  the total number of vertices (or graph nodes).
//
//  Each subsequent line describes an edge. For example,
//  the second lines describes an edge between vertex 1
//  and vertex 2 with a weight of 9.0. This graph
//  representation remains consistent until a single
//  zero is encountered. A zero indicates the end
//  of edge sequencing, and informs the application
//  to search for two more values. The next two values
//  describe the starting and ending vertex. These values
//  are essential to computing the shortest path.
//
// An example of the output for this application (using the
// the above input) could be as follows:
//
// There are 5 vertices and 6 edges.
// The edges are as follows.
//
//( 1,3) weight 12.000
// (1,2) weight 9.000
// (2,5) weight 20.000
// (2,3) weight 6.000
// (2,4) weight 18.000
// (3,5) weight 15.000

// The shortest path from 1 to 5 has length 27.000 and is
// 1 -> 3 -> 5
//
// It is important to note that Dijkstra's algorithm can
// be expressed as a discrete event simulation and that
// is a key part of the implementation found within this
// application. This application processes singular events
// from an event queue data structure. This is thoroughly
// detailed through a concept known as switchable tracing.
//
// Events send signals from vertex u to vertex v, with
// a weight of w, at a specific time t. Switchable tracing
// describes the processing of these events and their
// fields.
//
// Switchable tracing is controllable and this field detail
// is only printed to the standard output upon request.
// This is accomplished through a command line argument.
// An example of proper command line syntax is as follows:
//
//  ./dijkstra -t
//
// "-t" enables switchable tracing. By default, switching
// tracing is disabled.
//
// Another example of a redirected graph input could be:
//
//  ./dijkstra <dijkstra_sample.txt -t

#include "pqueue.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

// Edge: An object of this type
// represents an edge in a weighted
// graph.
//
// Field(s):
//
//  from: An integer value
//  indicating the vertex that
//  this edge is directed from.
//
//  to: An integer value indicating
//  the vertex that this edge is
//  directed to.
//
//  weight: A real number indicating
//  the weight w of a edge.
//
//  next: A pointer to the next
//  edge object in an adjacency
//  list.

struct Edge
{

    int from;
    int to;
    double weight;
    Edge* next;

    Edge(int fv, int tv, double w, Edge* nxt)
    {

        from = fv;
        to = tv;
        weight = w;
        next = nxt;

    }
};

// Vertex: An object of this type
// represents a single vertex v
// within a graph.
//
//  Field(s):
//
//   edges:
//   A pointer to an adjacency
//   list of all edges, edges
//   from v to another vertex.

//   time:
//   A real number indicating
//   v's shortest distance (or time)
//   from the start vertex.
//
//   sender: A vertex number sender.

struct Vertex
{

    Edge* edges;
    double time;
    int sender;

    Vertex()
    {

        edges = NULL;
        time = -1;
        sender = -1;

    }
};

// Graph: An object of this
// type represents a weighted
// graph g.
//
//  Field(s):
//
//    numVertices: The total
//    number of vertices.
//
//    numEdges: The total number
//    of edges.
//
//    vertices: An array that
//    represents the collection
//    of vertex structures inside
//    graph g.

struct Graph
{

    int numVertices;
    int numEdges;
    Vertex* vertices;

    Graph(int nv)
    {

        numVertices = nv;
        numEdges = 0;
        vertices = new Vertex[nv + 1];

    }
};

// Type definitions
typedef PriorityQueue EventQueue;

// Global variable(s)
int tracing = 0;

// StringIsEqual(dest, src) returns true if dest and
// src are identical strings. And otherwise, will return
// false.

bool stringIsEqual(const char* dest, const char* src)
{

    return strcmp(dest, src) == 0;

}

// UpdateTracing(argc, arv) iterates
// through the array of characters, argv
// and activates tracing if any member
// of argv is equal to the string: "-t".

void updateTracing(int argc, char* argv[])
{

   for(int i = 0; i < argc; i++)
   {

       bool tracingRequested = stringIsEqual(argv[i], "-t");

       if(tracingRequested)
       {

            tracing = 1;

       }
   }
}

// InsertBiedge(u, v, w, g) inserts an edge
// into two adjacency lists. First, an edge is inserted
// at vertex u, between u and v, of weight w.
// Conversely, another edge is inserted at vertex v,
// between v and u, of weight w.

void insertBiedge(int u, int v, double w, Graph*& g)
{

    Vertex* vertexList = g->vertices;
    vertexList[u].edges = new Edge(u, v, w, vertexList[u].edges);
    vertexList[v].edges = new Edge(v, u, w, vertexList[v].edges);
    g->numEdges++;

}

// PopulateEventWithPoints(s, r, e) sets
// the sender and receiver of event
// e to s and r, respectively.

void populateEventWithPoints(int s, int r, Event* e)
{

    e->sender = s;
    e->receiver = r;

}

// ReadGraph(e) reads information from the
// standard input and populates it into
// adjacency lists, forming vertex and
// edge objects. Lastly, it returns
// a populated event object e. E indicates
// the starting and ending vertex of this
// graph.

Graph* readGraph(Event* e)
{

    int cur, numVert;
    scanf("%i", &numVert);
    Graph* g = new Graph(numVert);

    while(scanf("%i", &cur) > 0)
    {

        int v;
        double w;

        if(cur != 0)
        {

            scanf("%i%lf", &v, &w);
            insertBiedge(cur, v, w, g);

        }
        else
        {

            scanf("%i%i", &cur, &v);
            populateEventWithPoints(cur, v, e);
            break;

        }
    }

    return g;

}

// TraceEdge(edge, i) follows each edge in the
// collection of edges, edge. Then, it prints
// the fields of each subsequent pointer
// of edges to the standard output. i is
// the current vertex.

void traceEdge(Edge* edge, int i)
{

    if(edge != NULL)
    {

        if(edge->to >= i)
        {


            int u = edge->from;
            int v = edge->to;
            double w = edge->weight;
            printf(" (%i, %i) weight %0.3lf\n", u, v, w);

        }

        traceEdge(edge->next, i);
    }
}

// WriteGraph(g) writes information from graph g
// to the standard output. It displays data
// from each edge in this graph and prints
// out the shortest path from the starting
// and ending vertex of this graph representation.

void writeGraph(Graph* g)
{

    int numVert = g->numVertices;
    int numEdge = g->numEdges;
    printf("\nThere are %i vertices and %i edges.\n", numVert, numEdge);
    printf("The edges are as follows.\n\n");

    for(int i = 1; i < g->numVertices + 1; i++)
    {

        Vertex vertex = g->vertices[i];
        Edge* edge = vertex.edges;
        traceEdge(edge, i + 1);

    }
}

// SendSignal(s, r, t, c, q) sends a signal from vertex
// s to vertex r, arriving at time t, by inserting
// an event into event queue q. C represents the
// current time.

void sendSignal(int s, int r, double t, double c, EventQueue& q)
{

    Event* evt = new Event(s, r, t);
    insert(q, evt, t);

    if(tracing > 0)
    {

        printf(" %0.1lf Sending signal: [sender: %i, receiver: %i, time: %0.1lf]\n", c, s, r, t);

    }
}

// PropagateSignal(g, v, q) sends a signal from vertex
// v to every vertex that is adjacent to v in g, excluding
// those that have already received a signal.

void propagateSignal(Graph* g, int v, EventQueue& q)
{

    Vertex* myVertex = &g->vertices[v];

    for(Edge* edge = myVertex->edges; edge != NULL; edge = edge->next)
    {

        Vertex* curVertex = &g->vertices[edge->to];

        if(curVertex->time < 0)
        {

            if(tracing > 0)
            {

                printf(" %0.1lf Vertex %i is adjacent to pair (%i, %i).\n", myVertex->time, v, edge->from, edge->to);

            }

            double summedTime = myVertex->time + edge->weight;
            sendSignal(v, edge->to, summedTime, myVertex->time, q);

        }
    }
}

// PopulateVertex(v, s, t) takes vertex v
// and populates its fields (sender and time)
// to s and t, respectively.

void populateVertex(Graph* g, int v, int s, double t)
{

    Vertex* myVertex = &g->vertices[v];
    myVertex->sender = s;
    myVertex->time = t;

    if(tracing > 0)
    {

        printf(" %0.1lf Vertex updated: [sender: %i, time: %0.1lf]\n", myVertex->time, s, t);

    }
}

// ProcessEvent(g, q, e) processes a single event
// e that has not received an event signal, and
// otherwise will ignore all subsequent signal
// calls.
//
// Event E represents the arrival of a signal
// at vertex r and is processed through two
// steps:
//
//  1. Installing information in vertex r.
//  2. Sending a signal from r to each
//     vertex that is adjacent to r and that
//     has not already received a signal
//     (e.g: Signal propagation).

void processEvent(Graph* g, EventQueue& q, Event* e)
{

    Vertex* v = &g->vertices[e->receiver];
    bool hasReceivedSignal = v->time >= 0;
    bool firstSignal = e->sender == 0;

    if(tracing > 0)
    {

        printf(" %0.1lf Signal request received from: ", e->time);
        printf("[sender: %i, receiver: %i, time: %0.1lf]\n", e->sender, e->receiver, e->time);

    }

    if(!hasReceivedSignal || firstSignal)
    {

        populateVertex(g, e->receiver, e->sender, e->time);
        propagateSignal(g, e->receiver, q);

        if(tracing > 0)
        {

            printf(" %0.1lf Signal arrival from %i to %i.\n", e->time, e->sender, e->receiver);

        }
    }
    else
    {

        if(tracing > 0)
        {

            printf(" %0.1lf Signal from %i to %i ignored.\n", e->time, e->sender, e->receiver);

        }
    }

    delete e;

}

// SimulateEventLoop(startV, endV, q) simulates
// the event loop. It processes events
// in chronological order until the ending vertex
// endV has a time that is greater than or equal
// to zero (endV >= 0).

void simulateEventLoop(Graph* g, int startV, int endV, EventQueue& q)
{

    Event* defaultEvent = new Event(1, 1, 0.0);
    Vertex* endVertex = &g->vertices[endV];
    populateVertex(g, defaultEvent->sender, defaultEvent->receiver, defaultEvent->time);
    sendSignal(0, startV, defaultEvent->time, 0.0, q);

    while(endVertex->time < 0)
    {

        remove(q, defaultEvent, defaultEvent->time);
        processEvent(g, q, defaultEvent);

    }

    if(tracing > 0)
    {

        printf("\nEnd of simulation.");

    }
}

// PrintPath(g, startV, endV) prints the shortest
// path between the starting vertex, startV and
// the ending vertex, endV (in graph g)
// to the standard output.

void printPath(const Graph* g, int startV, int endV)
{

    int i = g->vertices[endV].sender;
    printf("%i -> ", startV);

    while(i != startV)
    {

        printf("%i -> ", i);
        i = g->vertices[i].sender;

    }

    printf("%i", endV);

}

int main(int argc, char* argv[])
{

  updateTracing(argc, argv);
  EventQueue q;
  Event* e = new Event(0, 0, 0.0);
  Graph* g = readGraph(e);
  writeGraph(g);
  printf("\n");
  simulateEventLoop(g, e->sender, e->receiver, q);
  double pathLength = g->vertices[e->receiver].time;
  printf("\n");
  printf("The shortest path from %i to %i has length %0.3lf and is ", e->sender, e->receiver, pathLength);
  printPath(g, e->sender, e->receiver);
  printf("\n");
  return 0;

}
