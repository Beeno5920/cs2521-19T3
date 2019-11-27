// Centrality Measures ADT implementation
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "CentralityMeasures.h"
#include "Dijkstra.h"
#include "PQ.h"

//Create a Nodevalues, allocate enought memeroy and initialise its values
static NodeValues newNodeValues(int size) {
	NodeValues nvs;
	nvs.numNodes = size;
	nvs.values = calloc((size + 1), sizeof(nvs.values));

	return nvs;
}

//Check if the given vertex in the shortest paths
static int vertexInSp(ShortestPaths sp, int v) {
	int inSp = 0;
	for (int i = 0, n = sp.numNodes; i < n; i++)
		inSp += sp.dist[i];
		
	return inSp;
}

NodeValues closenessCentrality(Graph g) {
	assert(g != NULL);

	int N = GraphNumVertices(g);
	NodeValues nvs = newNodeValues(N);
	
	for (int i = 0; i < N; i++) {
		ShortestPaths sp = dijkstra(g, i);

		if (!vertexInSp(sp, i)) {
			nvs.values[i] = (double)0;
			freeShortestPaths(sp);
			continue;
		}

		int sumOfSpDist = 0;
		int nReachableNode = 0;
		for (int j = 0, m = sp.numNodes; j < m; j++) {
			sumOfSpDist += sp.dist[j];
			if(j != i && sp.dist[j] != 0)
				nReachableNode++;
		}
		double closeness = ((double)(nReachableNode) / (N - 1)) * ((double)(nReachableNode) / sumOfSpDist);
		nvs.values[i] = closeness;
		freeShortestPaths(sp);
	}
	return nvs;
}

//Use DFS to find out the number of shortest paths from src to dest
static double numOfPaths(int src, int dest, PredNode** pred) {
	if (!pred)
		return 0;

	double nPath = 0;

	for (PredNode* curr = pred[dest]; curr != NULL; curr = curr->next) {
		if (curr->v == src)
			nPath++;
		nPath += numOfPaths(src, curr->v, pred);
	}

	return nPath;
}

NodeValues betweennessCentrality(Graph g) {
	assert(g != NULL);

	int len = GraphNumVertices(g);
	NodeValues nvs = newNodeValues(len);

	for (int v = 0; v < len; v++) {
		for (int s = 0; s < len; s++) {
			if (v == s)
				continue;
			ShortestPaths sp = dijkstra(g, s);
			for (int t = 0; t < len; t++) {
				if (v == t || s == t)
					continue;
				double sigma_st = numOfPaths(s, t, sp.pred);
				double sigma_st_v = numOfPaths(s, v, sp.pred) * numOfPaths(v, t, sp.pred);
				nvs.values[v] += (sigma_st == 0) ? 0 : sigma_st_v / sigma_st;
			}
			freeShortestPaths(sp);
		}
	}

	return nvs;
}

NodeValues betweennessCentralityNormalised(Graph g) {
	assert(g != NULL);

	int len = GraphNumVertices(g);
	NodeValues nvs = newNodeValues(len);
	NodeValues betweennessNode = betweennessCentrality(g);

	for (int v = 0; v < len; v++) {
		double n = betweennessNode.numNodes;
		double betweenness = betweennessNode.values[v];

		if (n - 2 > 0) 
			nvs.values[v] = (1 / ((n - 1)*(n - 2))) * betweenness;
	}
	freeNodeValues(betweennessNode);

	return nvs;
}

void showNodeValues(NodeValues nvs) {
	for (int i = 0, n = nvs.numNodes; i < n; i++) {
		printf("%d: %f\n", i, nvs.values[i]);
	}
}

void freeNodeValues(NodeValues nvs) {
	free(nvs.values);
}
