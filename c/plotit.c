/****************************************************************************
 *  Reads in a map from stdin and two integers s and d and computes the
 *  shortest path from s to d. Plots the results in turtle graphics.
 * 
 *  % gcc plotit.c graph.c point.c pqindex.c -o plotit
 *  % plotit < usa.txt | turtle > usa.eps
 *  % gs usa.eps
 *
 ****************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(void) {
    int s, d;
    Graph G;
	s=d=0;
    G = GRAPHscan();              // read in the graph from stdin
    scanf("%d %d", &s, &d);       // read in the source and destination
    GRAPHsp(G, s, d);             // compute the shortest path from s to d
    GRAPHplot(G);                 // plot it in turtle graphics
    return 0; 
}

// 5000 California
