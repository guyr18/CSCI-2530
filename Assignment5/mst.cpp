// CSCI 2530
// Assignment: 5
// Author: Robert Guy
// File: mst.cpp
// Tab stops: 4
//
// ============================================
// This program reads a weighted graph g from
// the standard input and writes a minimal
// spanning tree of g to the standard output.
//
// The output format can further be simplified as:
//  1. The original graph G.
//  2. The computed minimal spanning tree T of G.
//  3. The total weight of T.
//
// Input format: The input starts with a line
// that tells how many vertices the graph has.
// If there are three vertices, then those
// vertices have numbers 1, 2, and 3. This
// application labels vertices from 1 to n. Such
// as 1, ..., n.
//
// Following the first line are the edges, one
// per line. Each edge line has three integers on it.
// Such as: 3 6 30.
//
// This would indicate that there is an edge of
// weight 30 between vertices 3 and 6.
//
// Weights are integers and the end of the input
// is signaled by a line that contains just a 0.
// Such as: 0.
//
// For example:
//  5
//  1   2   9
//  1   3   12
//  2   4   18
//  2   3   8
//  2   5   20
//  3   5   15
//  0
//
// The input is not required to be provided on different lines.
// An acceptable alternative could be as follows:
// 5 1 2 9 1 3 12 2 4 18 2 3 8 2 5 20 3 5 15 0
// ===========================================

#include "equiv.h"
#include <cstdio>
#include <cstdlib>
using namespace std;

// Edge: An object of this type
// represents one edge in a graph.
//
// Fields:
//  vertexOne: The first vertex
//  of an edge object.
//
//  vertexTwo: The second vertex
//  of an edge object.
//
//  vertexWeight: The summed weight
//  component of vertexOne and vertexTwo.


struct Edge
{

    int vertexOne;
    int vertexTwo;
    int vertexWeight;

    Edge()
    {

        vertexOne = 0;
        vertexTwo = 0;
        vertexWeight = 0;

    }
};

// Graph: An object of this type
// represents a weighted graph.
//
// Fields:
//  numVertices: The total number of vertices.
//  in this graph.
//
//  numEdges: The total number of edges
//  in this graph.
//
//  arrEdges: An array representing the
//  collection of edge objects found
//  in this graph.
//
//  physSizeEdges: The physical size of
//  the array, arrEdges.

struct Graph
{

    int numVertices;
    int numEdges;
    Edge* arrEdges;
    int physSizeEdges;

    Graph(int n, int e)
    {

        numVertices = n;
        numEdges = 0;
        arrEdges = new Edge[e];
        physSizeEdges = e;

    }
};

const int maxGraphEdges = 50;
typedef int (*QSORT_COMPARE_TYPE) (const void*, const void*);

// CompareEdges(A, B) compares two edge objects
// by returning the difference between their
// weight fields (vertexWeight).

int compareEdges(const Edge* A, const Edge* B)
{

    return A->vertexWeight - B->vertexWeight;

}

// InsertEdge(u, v, w, g) inserts an edge
// between vertices u and v, of weight w,
// into graph g.

void insertEdge(int u, int v, int w, Graph* g)
{

    int index = g->numEdges;
    g->arrEdges[index].vertexOne = u;
    g->arrEdges[index].vertexTwo = v;
    g->arrEdges[index].vertexWeight = w;
    g->numEdges++;

}

// ReadGraph(e) allocates a graph in the heap
// with enough room for e edges. It reads
// a graph from the standard input in the
// input format and returns a pointer to
// that graph.

Graph* readGraph(int e)
{

    int cur, numVert;
    scanf("%i", &numVert);
    Graph* g = new Graph(numVert, e);

    while(scanf("%i", &cur) > 0 && cur != 0)
    {

        int v, w;
        scanf("%i%i", &v, &w);
        insertEdge(cur, v, w, g);

    }

    return g;

}

// WriteGraph(g) writes graph g in the
// output format. WriteGraph shows the
// number of vertices and the number of
// edges, but otherwise does not write
// a heading.

void writeGraph(const Graph* g)
{

    int numVert = g->numVertices;
    int numEdge = g->numEdges;
    printf("\n\nThere are %i vertices and %i edges\n", numVert, numEdge);
    printf("\nvertices\tweight\n");

    for(int i = 0; i < numEdge; i++)
    {

        Edge edge = g->arrEdges[i];
        int u = edge.vertexOne;
        int v = edge.vertexTwo;
        int w = edge.vertexWeight;
        printf("%i\t%i\t%i\n", u, v, w);

    }
}

// SortEdges(g) sorts the edges of g
// into nondecreasing order by weight.

void sortEdges(Graph* g)
{

    qsort(g->arrEdges, g->numEdges, sizeof(Edge), (QSORT_COMPARE_TYPE) compareEdges);

}

// MinimalSpanningTree(g) returns a minimal
// spanning tree of g.

Graph* minimalSpanningTree(Graph* g)
{

    ER erm = newER(g->numVertices);
    Graph* t = new Graph(g->numVertices, g->numEdges);
    sortEdges(g);

    for(int i = 0; i < g->numEdges; i++)
    {

        Edge edge = g->arrEdges[i];
        int u = edge.vertexOne;
        int v = edge.vertexTwo;

        if(!equivalent(erm, u, v))
        {

            int w = edge.vertexWeight;
            insertEdge(u, v, w, t);
            combine(erm, u, v);

        }
    }

    destroyER(erm);
    return t;

}

// TotalWeight(g) returns the sum of the
// weights of the edges in g.

int totalWeight(const Graph* g)
{

    int sum = 0;

    for(int i = 0; i < g->numEdges; i++)
    {

        Edge edge = g->arrEdges[i];
        sum = sum + edge.vertexWeight;

    }

    return sum;

}

int main()
{

    Graph* g = readGraph(maxGraphEdges);
    printf("\nInput graph:");
    writeGraph(g);
    const Graph* t = minimalSpanningTree(g);
    int tw = totalWeight(t);
    printf("\nMinimal spanning tree:");
    writeGraph(t);
    printf("\nThe total weight of the spanning tree is %i",  tw);
    printf("\n");
    return 0;

}
