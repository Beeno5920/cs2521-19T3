
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int shortestDistance(Graph g, int src, int dest) {
	// TODO
  int nV = GraphNumVertices(g);
  int* dist = calloc(nV, sizeof(*dist));
  Queue q = QueueNew();
  QueueEnqueue(q, src);

  while (!QueueIsEmpty(q)) {
    int next = QueueDequeue(q);

    for (int i = 0; i < nV; i++) {
      if ((dist[i] == 0 || dist[next] + 1 < dist[i]) && GraphIsAdjacent(g, next, i) && i != src) {
	dist[i] = dist[next] + 1;
	QueueEnqueue(q, i);
      }
    }
    
  }

  for (int i = 0; i < nV; i++) {
    if (dist[i] == 0 && i != src)
      dist[i] = -1;
  }

  int out = dist[dest];
  free(dist);
  QueueFree(q);
  return out;
}

