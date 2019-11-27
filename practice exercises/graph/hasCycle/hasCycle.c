
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

void dfs(Graph g, int src, int from, int *visited, bool *foundCycle) {
  for (int i = 0, n = GraphNumVertices(g); i < n; i++) {
    if (i != from && i != src && GraphIsAdjacent(g, src, i)) {
      if (visited[i] == 1) {
		*foundCycle = true;
		return;
    }else {
		visited[i] = 1;
		dfs(g, i, src, visited, foundCycle);
      }
    }
  }
}

bool hasCycle(Graph g) {
	// TODO
  bool foundCycle = false;
  for (int i = 0, n = GraphNumVertices(g); i < n; i++) {
    int *visited = calloc(n, sizeof(*visited));
    visited[i] = 1;
    
    dfs(g, i, i, visited, &foundCycle);
    free(visited);
    
    if(foundCycle)
      break;
  }

  return foundCycle;
}
