
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void dfs(Graph g, int src, int nV, int *visited, int *count) {
  visited[src] = 1;
  for (int i = 0; i < nV; i++) {
    if (GraphIsAdjacent(g, src, i) && visited[i] != 1) {
      *count += 1;
      dfs(g, i, nV, visited, count);
    }
  }
}

int numReachable(Graph g, int src) {
	// TODO
  int nV = GraphNumVertices(g);
  int *visited = calloc(nV, sizeof(*visited));
  int count = 1;
  visited[src] = 1;
  dfs(g, src, nV, visited, &count);

  free(visited);

  return count;
}

