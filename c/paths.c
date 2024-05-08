/****************************************************************************
 *  Reads in a map from stdin and repeatedly reads in two integers s and
 *  d and computes the shortest path from s to d. Prints the paths to stdout.
 * 
 *  % gcc path.c graph.c point.c pqindex.c -o path
 *  % path < usa.txt
 *
 ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "graph.h"

int main(void) {
    int v, w;
    Graph G;

    // read in graph
    G = GRAPHscan();

    // read in shortest path queries and process
    while(scanf("%d %d", &v, &w) != EOF) {
       GRAPHsp(G, v, w);
       GRAPHshowsp(G);
    }

    return 0;
  }

