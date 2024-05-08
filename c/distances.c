/****************************************************************************
 *  Reads in a map from stdin and repeatedly reads in two integers s and d
 *  and computes the shortest path from s to d. Prints the distances to stdout.
 * 
 *  % gcc distances.c graph.c point.c pqindex.c -o distances
 *  % distances < usa.txt
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
    while(scanf("%d %d", &v, &w) != EOF)
       printf("%.6f\n", GRAPHsp(G, v, w));

    return 0;
  }

