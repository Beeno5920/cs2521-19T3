
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void dfs(Graph g, int src, int* arr) {
  for (int i = 0, n = GraphNumVertices(g); i < n; i++) {
    if (GraphIsAdjacent(g, src, i) && !arr[i]) {
      arr[i] = 1;
      printf("%d ", i);
      dfs(g, i, arr);
    }
  }
}

void depthFirstSearch(Graph g, int src) {
	// TODO
  int* arr = calloc(GraphNumVertices(g), sizeof(*arr));
  arr[src] = 1;
  printf("%d ", src);
  dfs(g, src, arr);
  free(arr);
}

