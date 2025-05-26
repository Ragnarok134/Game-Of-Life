#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int V, E;
    int **a;
} Graph;

typedef struct 
{
    int x, y;
    int id;
} AuxNode;

typedef struct
{
    int x, y;
}Coordinates;


int numberOfNodes(char** matrix, int N, int M);

int** generateAdjacencyMatrix(char** matrix, int N, int M, int numberOfNodes);

void DFS_scan(Graph *g, int visited[], int i, int* worthSearching, int id, int *terminalNodes);

void DFS(Graph *g, int *maxLength, Coordinates *Path);

int findHamiltonianPath(Graph* g, int numberOfNodes, Coordinates **path);