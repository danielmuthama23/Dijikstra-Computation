/*********************************************************************
 *  Undirected graph.
 *
 *  This code is from "Algorithms in C, Third Edition,
 *  by Robert Sedgewick, Addison-Wesley, 2002.
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "pqindex.h"

static int N;
static int *pq;
static int *qp;
static double *priority;

int greater(int i, int j) { return priority[i] > priority[j]; }

void exch(int i, int j) {
   int t;
   t = qp[i]; qp[i] = qp[j]; qp[j] = t;
   pq[qp[i]] = i; pq[qp[j]] = j;
}

void PQinit(int NMAX, double p[]) {
   pq = malloc((NMAX + 1) * sizeof *pq);
   qp = malloc((NMAX + 1) * sizeof *qp);
   if (pq == NULL || qp == NULL) {
      fprintf(stderr, "Out of memory in PQinit()\n");
      exit(EXIT_FAILURE);
   }
   priority = p;
}

int PQisempty(void) { return N == 0; }

void fixUp(int a[], int k)  {
   while (k > 1 && greater(a[k/2], a[k])) {
      exch(a[k], a[k/2]);
      k = k/2;
   }
}

void fixDown(int a[], int k, int N) {
   int j;
   while (2*k <= N) {
      j = 2*k;
      if (j < N && greater(a[j], a[j+1])) j++;
      if (!greater(a[k], a[j])) break;
      exch(a[k], a[j]);
      k = j;
   }
}


void PQinsert(int k) {
   qp[k] = ++N;
   pq[N] = k;
   fixUp(pq, N);
}

int PQdelmin(void) { 
   exch(pq[1], pq[N]); 
   fixDown(pq, 1, --N); 
   return pq[N+1]; 
}

void PQchange(int k) {
   fixUp(pq, qp[k]);
   fixDown(pq, qp[k], N);
}
