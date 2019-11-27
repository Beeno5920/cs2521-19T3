// graph.h ... Interface to Graph of strings
// Written by John Shepherd, September 2015

#include <stdbool.h>
#include <stdlib.h>

#ifndef GRAPH_H
#define GRAPH_H

typedef unsigned char Num;

typedef struct GraphRep {
	size_t nV;
	size_t maxV;
	char **vertex;
	Num **edges;
} GraphRep;

typedef struct GraphRep *Graph;

// Function signatures

Graph newGraph (size_t);
void dropGraph (Graph);
bool addEdge (Graph, char *, char *);
size_t nVertices (Graph);
bool isConnected (Graph, char *, char *);
void showGraph (Graph, int);

#endif
