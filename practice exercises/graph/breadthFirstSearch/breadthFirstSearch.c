
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void breadthFirstSearch(Graph g, int src) {
	// TODO
  Queue q = QueueNew();
  int len = GraphNumVertices(g);
  int* visited = calloc(len, sizeof(*visited));
  visited[src] = 1;
  QueueEnqueue(q, src);

  printf("%d ", src);
  while (QueueSize(q) != 0) {
    int next = QueueDequeue(q);
    for (int i = 0; i < len; i++) {
      if (GraphIsAdjacent(g, next, i) && !visited[i]) {
	visited[i] = 1;
	printf("%d ", i);
	QueueEnqueue(q, i);
      }
    }
  }

  QueueFree(q);
  free(visited);
}

