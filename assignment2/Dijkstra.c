#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Dijkstra.h"
#include "Graph.h"
#include "PQ.h"

#define INF 2147483647

//create and return a new predecessor node and initialize its values
static PredNode* newPredNode(int vertex) {
    PredNode* newNode = malloc(sizeof(*newNode));
    newNode->v = vertex;
    newNode->next = NULL;

    return newNode;
}

//append predecessor node to the end of the predecessor list
static void appendPredNode(PredNode* pred, int vertex) {
    PredNode* cur = pred;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = newPredNode(vertex);
}

//remove all nodes come after the input node
static void removePredNodesAfter(PredNode* pred) {
    assert(pred != NULL);
    while (pred->next != NULL) {
        PredNode* tmp = pred->next->next;
        free(pred->next);
        pred->next = tmp;
    }
}

//create and return a new ShortersPaths structure and initialize its values
static ShortestPaths newPaths(Graph g, int src) {
    ShortestPaths path;
    path.numNodes = GraphNumVertices(g);
    path.src = src;
    path.dist = NULL;
    path.pred = NULL;

    return path;
}

//create and return a new item and initialize its values
static ItemPQ newItem(int distance, int vertex) {
    ItemPQ item;
    item.value = distance;
    item.key = vertex;

    return item;
}

//using Dijkstra's algorithm to find the shortest paths and return the results as a ShortestPaths structure
ShortestPaths dijkstra(Graph g, Vertex src) {
    //assert(validVertex(g, src));

    ShortestPaths path = newPaths(g, src);

    //initialize the the arrays 
    for (int i = 0; i < path.numNodes; i++) {
        path.pred = realloc(path.pred, sizeof(*path.pred) * (i + 1));
        path.dist = realloc(path.dist, sizeof(*path.dist) * (i + 1));

        path.pred[i] = NULL;
        path.dist[i] = INF;
    }

    path.dist[src] = 0;

    PQ vertex_PQ = PQNew();
    PQAdd(vertex_PQ, newItem(0, src));

    while (!PQIsEmpty(vertex_PQ)) {
        ItemPQ temp = PQDequeue(vertex_PQ);
        int minDistIdx = temp.key;
    
        for (AdjList ptr = GraphOutIncident(g, minDistIdx); ptr != NULL; ptr = ptr->next) {
           if (path.dist[minDistIdx] + ptr->weight < path.dist[ptr->v]) {
                path.dist[ptr->v] = path.dist[minDistIdx] + ptr->weight;

                if (path.pred[ptr->v] == NULL)
                    path.pred[ptr->v] = newPredNode(minDistIdx);
                else {
                    path.pred[ptr->v]->v = minDistIdx;
                    removePredNodesAfter(path.pred[ptr->v]);
                }
            
                PQAdd(vertex_PQ, newItem(path.dist[ptr->v], ptr->v));
            } else if (path.pred[ptr->v] != NULL && path.dist[minDistIdx] + ptr->weight == path.dist[ptr->v]) {
                appendPredNode(path.pred[ptr->v], minDistIdx);
                
                PQAdd(vertex_PQ, newItem(path.dist[ptr->v], ptr->v));
            }
        }
    }

    //change all the INF values to 0 in the distance arrays
    for (int i = 0; i < path.numNodes; i++) {
        if (path.dist[i] == INF) 
            path.dist[i] = 0;
    }

    return path;
}

void showShortestPaths(ShortestPaths sp) {
    for (int i = 0; i < sp.numNodes; i++) {
        printf("Node %d\n", i);
        printf("\tDistance\n");
        for (int j = 0; j < sp.numNodes; j++) {
            printf("\t%d : ", j);
            if (j == i)
                printf("X\n");
            else
                printf("%d\n", sp.dist[j]);
        }
        printf("\tPreds\n");
        for (PredNode* curr = sp.pred[i]; curr != NULL; curr = curr->next) {
            printf("\t%d : ", curr->v);
            if (curr == NULL)
                printf("NULL\n");
            else
                printf("[%d]->", curr->v);
        }
    }
}

void freeShortestPaths(ShortestPaths sp) {
    for (int i = 0; i < sp.numNodes; i++) {
        PredNode* curr = sp.pred[i];
        while (curr != NULL) {
            sp.pred[i] = sp.pred[i]->next;
            free(curr);
            curr = sp.pred[i];
        }
    }
    free(sp.dist);
}