# CSCI-2530
# Assignment 7
Assignment 7 represented a <b>discrete event simulation</b> by incorporating <b>Dijkstra's</b> shortest path algorithm.

# Background
  A <b>discrete event simulation</b> performs a simulation of a collection of events, where each event occurs at a specified time. 
 
  <b>Dijkstra's</b> algorithm finds shortest paths in weighted graphs, and it can be expressed as a discrete event simulation.
 
# More Information..
 This application uses <b>Dijkstra's</b> shortest
 path algorithm and reads information about
 a weighted graph from the standard input.
 And furthermore, has three components:
  1. An input graph description that is
     derived from the standard input.
  2. The shortest path from the starting
     vertex to the ending vertex.
  3. The distance (or time) from the starting
     vertex to the ending vertex. This is
     derived from the shortest path.
  
  Conclusively, this assignment presented the challenge of integrating arrays, structures, linked lists and switchable
  tracing within a single application. This assignment was considered a "final project" for <b>CSCI 2530</b>.
  
# Compiling This Application

To compile this application, we will make use of the provided **Makefile**. You should clone the repository, navigate to directory **Assignment7**.

```
cd Assignment7
```

Subsequently, run **make clean** to remove any unneeded object files.

```
make clean
```

Lastly, you will run ***make dijkstra*** to obtain the desired executables.

```
make dijkstra
```

# Running This Application
  
    An example of the input that this application
    requests could be as follows:

    5
    1 2 9.0
    1 3 12.0
    2 4 18.0
    2 3 6.0
    2 5 20.0
    3 5 15.0
    0
    1 5

    The first line is a number that describes
    the total number of vertices (or graph nodes).
 
    Each subsequent line describes an edge. For example,
    the second lines describes an edge between vertex 1
    and vertex 2 with a weight of 9.0. This graph
    representation remains consistent until a single
    zero is encountered. A zero indicates the end
    of edge sequencing, and informs the application
    to search for two more values. The next two values
    describe the starting and ending vertex. These values
    are essential to computing the shortest path.
    
    An example of the output for this application (using the
    the above input) could be as follows:

   There are 5 vertices and 6 edges.
   The edges are as follows.

   (1,3) weight 12.000  
   (1,2) weight 9.000  
   (2,5) weight 20.000  
   (2,3) weight 6.000  
   (2,4) weight 18.000  
   (3,5) weight 15.000  

   The shortest path from 1 to 5 has length 27.000 and is
   1 -> 3 -> 5

   It is important to note that Dijkstra's algorithm can
   be expressed as a discrete event simulation and that
   is a key part of the implementation found within this
   application. This application processes singular events
   from an event queue data structure. This is thoroughly
   detailed through a concept known as switchable tracing.

   Events send signals from vertex u to vertex v, with
   a weight of w, at a specific time t. Switchable tracing
   describes the processing of these events and their
   fields.

   Switchable tracing is controllable and this field detail
   is only printed to the standard output upon request.
   This is accomplished through a command line argument.
   An example of proper command line syntax is as follows:

    ```
    ./dijkstra -t
    ```
    
  "-t" enables switchable tracing. By default, switching
  tracing is disabled.

  Another example of a redirected graph input could be:

    ```
    ./dijkstra <dijkstra_sample.txt -t
    ```
