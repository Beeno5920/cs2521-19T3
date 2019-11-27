
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

int bfs(Graph g, int src, int nV, int *dist, int *maxDist, int *maxIdx) {

  Queue q = QueueNew();
  QueueEnqueue(q, src);

  while (!QueueIsEmpty(q)) {
    int curr = QueueDequeue(q);
    for (int i = 0; i < nV; i++) {
      if ((dist[i] == -1) && GraphIsAdjacent(g, curr, i)) {
	dist[i] = dist[curr] + 1;
	if (dist[i] > *maxDist) {
	  *maxDist = dist[i];
	  *maxIdx = i;
	}else if (dist[i] == *maxDist) {
	  if (i > *maxIdx)
	    *maxIdx = i;
	}
	QueueEnqueue(q, i);
      }
    }
  }

  QueueFree(q);

  return *maxIdx;
}

int furthestReachable(Graph g, int src) {
	// TODO
  int nV = GraphNumVertices(g);
  int *dist = malloc(sizeof(*dist) * nV);
  int maxDist = 0;
  int maxIdx = -1;
  for (int i = 0; i < nV; i++)
    dist[i] = -1;
  dist[src] = 0;
  maxIdx = bfs(g, src, nV, dist, &maxDist, &maxIdx);
  if (maxIdx == -1)
    maxIdx = src;

  free(dist);
  return maxIdx;
}
