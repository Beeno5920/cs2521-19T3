// Lance-Williams Algorithm for Hierarchical Agglomerative Clustering
// COMP2521 Assignment 2

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <float.h>

#include "Graph.h"
#include "LanceWilliamsHAC.h"

#define INF DBL_MAX
#define max(x, y) (x > y ? x : y)
#define min(x, y) (x < y ? x : y)
#define swap(x, y) {int tmp = x; x = y; y = tmp;}

//Creats and return a new node of dendeogram and initialize its values 
static Dendrogram newDendeogram(int v) {
    Dendrogram dg = malloc(sizeof(*dg));
    dg->vertex = v;
    dg->left = NULL;
    dg->right = NULL;

    return dg;
}

/**
 * Creates and return a new distance matrix base on the given graph 
 * and update the two values in closestClusters array
*/
static double** newDistMatrix(Graph g, int* closestClusters) {
    int len = GraphNumVertices(g);
    double** distMatrix = malloc(sizeof(*distMatrix) * len);
    double minDist = INF;

    for (int i = 0; i < len; i++) {
        distMatrix[i] = malloc(sizeof(distMatrix) * len);
        for (int j = 0; j < len; j++) {
            distMatrix[i][j] = INF;
        }
    }

    for (int i = 0; i < len; i++) {
        AdjList outLink = GraphOutIncident(g, i);
        AdjList inLink = GraphInIncident(g, i);
        for (; outLink != NULL; outLink = outLink->next) {
            double dist = 1 / (double)(outLink->weight);

            if (dist < distMatrix[i][outLink->v] || dist < distMatrix[outLink->v][i])
                distMatrix[i][outLink->v] = distMatrix[outLink->v][i] = dist;
            
            if (dist < minDist) {
                minDist = dist;
                closestClusters[0] = i;
                closestClusters[1] = outLink->v;
            }
        }

        for (; inLink != NULL; inLink = inLink->next) {
            double dist = 1 / (double)(inLink->weight);

            if (dist < distMatrix[i][inLink->v] || dist < distMatrix[inLink->v][i])
                distMatrix[i][inLink->v] = distMatrix[inLink->v][i] = dist;

            if (dist < minDist) {
                minDist = dist;
                closestClusters[0] = i;
                closestClusters[1] = inLink->v;
            }
        }
    }

    if (closestClusters[0] > closestClusters[1]) {
        swap(closestClusters[0], closestClusters[1]);
    }

    return distMatrix;
}

//Free the given distance matrix
static void freeDistMatrix(double** distMatrix, int size) {
    for (int i = 0; i < size; i++) {
        free(distMatrix[i]);
    }
    free(distMatrix);
}

/**
 * Reconstruct the given distance matrix using Lance William's 
 * hierarchical agglomerative clustering method and return it. 
 * It also update the two values in the closestClusters array. 
*/
static double** updateDistMatrix(double** distMatrix, int* closestClusters, int size, int method) {
    double** updatedMatrix = malloc(sizeof(*updatedMatrix) * size);
    double minDist = INF;

    for (int i = 0; i < size; i++) {
        updatedMatrix[i] = malloc(sizeof(*updatedMatrix[i]) * size);
        for (int j = 0; j < size; j++) {
            updatedMatrix[i][j] = INF;
        }
    }
    
    int idx1 = closestClusters[0];
    int idx2 = closestClusters[1];
    
    for (int i = 0; i < size; i++) {
        int referenceRow = i;
        if (i >= idx1)
            referenceRow++;
        if (i >= idx2 - 1)
            referenceRow++;

        for (int j = i + 1; j < size; j++) {
            int referenceCol = j;
            if (j >= idx1)
                referenceCol++;
            if (j >= idx2 - 1)
                referenceCol++;

            if (j == size - 1) {
                if (method == 1)
                    updatedMatrix[i][j] = updatedMatrix[j][i] = min(distMatrix[referenceRow][idx1], distMatrix[referenceRow][idx2]);
                else if (method == 2)
                    updatedMatrix[i][j] = updatedMatrix[j][i] = max(distMatrix[referenceRow][idx1], distMatrix[referenceRow][idx2]);
            }else {
                updatedMatrix[i][j] = updatedMatrix[j][i] = distMatrix[referenceRow][referenceCol];
            }

            if (updatedMatrix[i][j] < minDist) {
                minDist = updatedMatrix[i][j];
                closestClusters[0] = i;
                closestClusters[1] = j;
            }
        }
    }

    if (closestClusters[0] > closestClusters[1]) {
        swap(closestClusters[0], closestClusters[1]);
    }
    freeDistMatrix(distMatrix, size + 1);
    
    return updatedMatrix;
}

/**
 * Generates  a Dendrogram using the Lance-Williams algorithm (discussed
 * in the spec) for the given graph  g  and  the  specified  method  for
 * agglomerative  clustering. The method can be either SINGLE_LINKAGE or
 * COMPLETE_LINKAGE (you only need to implement these two methods).
 * 
 * The function returns a 'Dendrogram' structure.
 */
Dendrogram LanceWilliamsHAC(Graph g, int method) {
    assert(g != NULL);

    int nVertex = GraphNumVertices(g);
    int clusterSize = nVertex;
    int* closestClusters = calloc(2, sizeof(*closestClusters));
    double** distMatrix = newDistMatrix(g, closestClusters);
    Dendrogram clusters[nVertex];
    for (int i = 0; i < nVertex; i++) {
        clusters[i] = newDendeogram(i);
    }

    while (clusterSize > 1) {
        Dendrogram newNode = newDendeogram(-1);
        newNode->left = clusters[closestClusters[0]];
        newNode->right = clusters[closestClusters[1]];
        clusterSize--;
        for (int i = 0; i < clusterSize; i++) {
            if (i == clusterSize - 1)
                clusters[i] = newNode;
            else {
                if (i >= closestClusters[0])
                    clusters[i] = clusters[i + 1];
                if (i >= closestClusters[1] - 1)
                    clusters[i] = clusters[i + 2];
            }
        }

        distMatrix = updateDistMatrix(distMatrix, closestClusters, clusterSize, method);
    }

    free(closestClusters);
    freeDistMatrix(distMatrix, clusterSize);

    for (int i = 1; i < clusterSize; i++)
        freeDendrogram(clusters[i]);

    return clusters[0];
}

/**
 * Frees all memory associated with the given Dendrogram structure.
 */
void freeDendrogram(Dendrogram dg) {
    if(!dg) {
        freeDendrogram(dg->left);
        freeDendrogram(dg->right);
        free(dg);
    }
}