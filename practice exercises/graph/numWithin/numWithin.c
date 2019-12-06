
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int numWithin(Graph g, int src, int dist) {
	// TODO
  Queue q = QueueNew();
  QueueEnqueue(q, src);
  int out = 1;
  int nV = GraphNumVertices(g);
  int* distArr = malloc(nV * sizeof(*distArr));
  for (int i = 0; i < nV; i++)
    distArr[i] = -1;
  distArr[src] = 0;
  while (!QueueIsEmpty(q)) {
    int curr = QueueDequeue(q);
    if (distArr[curr] + 1 > dist)
      continue;
    for (int i = 0; i < nV; i++) {
      if (GraphIsAdjacent(g, curr, i) && distArr[i] == -1) {
	QueueEnqueue(q, i);
	distArr[i] = distArr[curr] + 1;
	out++;
      }
    }
  }
  free(distArr);
  QueueFree(q);
  return out;
}

