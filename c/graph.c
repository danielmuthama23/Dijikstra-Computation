/*********************************************************************
 *  Undirected graph.
 *
 *  This code is from "Algorithms in C, Third Edition,
 *  by Robert Sedgewick, Addison-Wesley, 2002.
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"
#include "point.h"
#include "pqindex.h"

/*********************************************************
 *  Adjacency list data type.
 *********************************************************/
 typedef struct node *link;
 struct node {
    int w;               // destination node of edge
    link next;           // next element in adjacency list
    double wt;           // cost of edge
 };

/*********************************************************
 *  Graph data type.
 *********************************************************/
 struct graph {
    int V;               // number of vertices
    int E;               // number of edges
    int s;               // source
    int d;               // destination
    link *adj;           // adjacency list
    Point *points;       // Euclidean points of nodes
    int *pred;           // predecssor node for shortest path
    double *dist;        // shortest path distance
 };


/*********************************************************
 *  Initialize and return a new Edge.
 *********************************************************/
 Edge EDGE(int v, int w) {
    Edge e;
    e.v = v;
    e.w = w;
    return e;
 }

/*********************************************************
 *  Initialize and return a new adjacency list element.
 *********************************************************/
 link NEW(int w, link next, double wt) {
    link x = malloc(sizeof *x);
    x->w = w;
    x->next = next;
    x->wt = wt;
    return x;                         
 }

/*********************************************************
 *  Initialize and return a new graph with V vertices
 *  and no edges.
 *********************************************************/
 Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    G->V = V; G->E = 0;
    G->adj     = malloc(V * sizeof(*G->adj));
    G->points  = malloc(V * sizeof(*G->points));
    G->pred    = malloc(V * sizeof(*G->pred));
    G->dist    = malloc(V * sizeof(*G->dist));
    if (G->adj == NULL || G->points  == NULL ||
                          G->pred == NULL    || G->dist == NULL) {
       fprintf(stderr, "Out of memory in GRAPHinit()\n");
       exit(EXIT_FAILURE);
    }

    for (v = 0; v < V; v++) G->adj[v]  = NULL;
    for (v = 0; v < V; v++) G->dist[v] = INFINITY;
    for (v = 0; v < V; v++) G->pred[v] = -1;

    PQinit(V, G->dist);

    return G;
 }

/*********************************************************
 *  Insert Edge e into Graph g.
 *********************************************************/
void GRAPHinsertE(Graph G, Edge e) {
    int v = e.v;
    int w = e.w;
    double d = POINTdist(G->points[v], G->points[w]);
    G->adj[v] = NEW(w, G->adj[v], d);
    G->adj[w] = NEW(v, G->adj[w], d); 
    G->E++;
 }


/*********************************************************
 *  Print graph for debugging.
 *********************************************************/
 void GRAPHshow(Graph G) {
    link t; 
    int v, w;
    printf("%d vertices, %d edges\n", G->V, G->E);
    for (v = 0; v < G->V; v++) {
       printf("%6d ", v);
       POINTshow(G->points[v]);
       printf(" :  ");
       for (t = G->adj[v]; t != NULL; t = t->next) {
          w = t->w;
          printf("%d ", w);
       }
       printf("\n");
    }
 }

/*********************************************************
 *  Print shortest path.
 *********************************************************/
 void GRAPHshowsp(Graph G) {
    int v;

    // check if they're connected
    if (G->pred[G->d] == -1) {
       printf("%d and %d not connected.\n\n", G->s, G->d);
       return;
    }

    // otherwise print path - ok its actually in reverse order
    for (v = G->d; v != G->s; v = G->pred[v])
       printf("%d-", v);
    printf("%d\n\n", v);
 }

/*********************************************************
 *  Display graph in turtle graphics.
 *********************************************************/
 void GRAPHplot(Graph G) {
    link t; 
    int v, w;
    for (v = 0; v < G->V; v++) {
       POINTplot(G->points[v]);
       for (t = G->adj[v]; t != NULL; t = t->next) {
          w = t->w;
          LINEplot(G->points[v], G->points[w]);
       }
    }

    // draw the shortest path in red
    if (G->pred[G->d] != -1) {
       printf("C 1 0 0\n");
       for (v = G->d; v != G->s; v = G->pred[v])
          LINEplot(G->points[G->pred[v]], G->points[v]);
    }

    // highlight the nodes examined in blue
    printf("C 0 0 1\n");
    for (v = 0; v < G->V; v++)
       if (G->dist[v] < INFINITY)
          POINTplot(G->points[v]);

    // highlight the source and destination in green
    printf("C 0 1 0\n");
    POINTplot(G->points[G->s]);
    POINTplot(G->points[G->d]);

 }

/*********************************************************
 *  Read in a graph from a file, bare bones error checking.
 *  V E
 *  node: id x y
 *  edge: from to
 *********************************************************/
 Graph GRAPHscan(void) {
    int i, v, w;
    int V, E;
    Point p;
    Graph G;

    scanf("%d %d", &V, &E);
    G = GRAPHinit(V);

    // read in and insert vertices
    for (i = 0; i < V; i++) {
         scanf("%d %d %d", &v, &p.x, &p.y);
         assert(0 <= v && v < V);
         G->points[i] = p;
    }

    // read in and insert edges
    for (i = 0; i < E; i++) {
       scanf("%d %d", &v, &w);
       assert(0 <= v && v < V);
       assert(0 <= w && w < V);
       GRAPHinsertE(G, EDGE(v, w));
    }
    return G;
}



/*********************************************************
 *  Compute the shortest path from s to d in Graph G.
 *  Return the length of the path.
 *********************************************************/
 double GRAPHsp(Graph G, int s, int d) {
    int v, w;
    link t;

    // initialize source and destination
    assert(0 <= s && s < G->V);
    assert(0 <= d && d < G->V);
    G->s = s;
    G->d = d;

    // initialize
    for (v = 0; v < G->V; v++) G->dist[v] = INFINITY;
    for (v = 0; v < G->V; v++) G->pred[v] = -1;
    for (v = 0; v < G->V; v++) PQinsert(v);

    // set distance of source
    G->dist[s] = 0.0;
    G->pred[s] = s;
    PQchange(s);

    // run Dijkstra's algorithm
    while (!PQisempty()) {
       v = PQdelmin();

       //// printf("process %d (%.1f)\n", v, G->dist[v]);

       // v not reachable from s so stop
       if (G->pred[v] == -1) break;

       // scan through all nodes w adjacent to v
       for (t = G->adj[v]; t != NULL; t = t->next) {
          w = t->w;
          if (G->dist[v] + t->wt < G->dist[w] - EPSILON) {
             G->dist[w] = G->dist[v] + t->wt;
             PQchange(w);
             G->pred[w] = v;
             //// printf("    lower %d to %.1f\n", w, G->dist[w]);
          }
       }
    }

    // clean up queue so that you can reuse it again
    while(!PQisempty())
       v = PQdelmin();

    return G->dist[d];
 }
