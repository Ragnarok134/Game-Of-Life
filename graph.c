#include "graph.h"

int numberOfNodes(char** matrix, int N, int M)
{
    int cnt = 0;

    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            if(matrix[i][j] == 'X')
                cnt ++;
    
    return cnt;
}

int** generateAdjacencyMatrix(char** matrix, int N, int M, int numberOfNodes)
{
    int **adjacencyMatrix;

    adjacencyMatrix = (int **)malloc(sizeof(int*) * numberOfNodes);
    for(int i=0; i<numberOfNodes; i++)
        adjacencyMatrix[i] = (int*)malloc(sizeof(int) * numberOfNodes);

    for(int i=0; i<numberOfNodes; i++)
        for(int j=0; j<numberOfNodes; j++)
            adjacencyMatrix[i][j] = 0;

    int cnt = -1;
    AuxNode* nodes = NULL;

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
        {
            if(matrix[i][j] == 'X')
            {
                cnt ++;
                nodes = (AuxNode*)realloc(nodes, (cnt + 1) * sizeof(AuxNode));

                nodes[cnt].x = i;
                nodes[cnt].y = j;
                nodes[cnt].id = cnt;
                
                if (i > 0 && j > 0) 
                    if(matrix[i - 1][j - 1] == 'X') 
                    {
                        for(int k = 0; k<cnt; k++)
                        {
                            if(nodes[k].x == i-1 && nodes[k].y == j-1)
                            {
                                adjacencyMatrix[cnt][nodes[k].id] = 1;
                                adjacencyMatrix[nodes[k].id][cnt] = 1;
                            }
                        }
                    }

                if (i > 0)
                    if(matrix[i - 1][j] == 'X')
                    {
                        for(int k = 0; k<cnt; k++)
                        {
                            if(nodes[k].x == i-1 && nodes[k].y == j)
                            {
                                adjacencyMatrix[cnt][nodes[k].id] = 1;
                                adjacencyMatrix[nodes[k].id][cnt] = 1;
                            }
                        }
                    }
                
                if (i > 0 && j < M - 1)
                    if(matrix[i - 1][j + 1] == 'X')
                    {
                        for(int k = 0; k<cnt; k++)
                        {
                            if(nodes[k].x == i-1 && nodes[k].y == j+1)
                            {
                                adjacencyMatrix[cnt][nodes[k].id] = 1;
                                adjacencyMatrix[nodes[k].id][cnt] = 1;
                            }
                        }
                    }

                if (j > 0)
                    if(matrix[i][j - 1] == 'X')
                    {
                        for(int k = 0; k<cnt; k++)
                        {
                            if(nodes[k].x == i && nodes[k].y == j-1)
                            {
                                adjacencyMatrix[cnt][nodes[k].id] = 1;
                                adjacencyMatrix[nodes[k].id][cnt] = 1;
                            }
                        }
                    }
            }
        }
    }

    return adjacencyMatrix;
}

void DFS_scan(Graph *g, int visited[], int i, int* worthSearching, int id, int *terminalNodes) {/*
    if(*worthSearching == 1)
    {
        int sum = 0;
        for(int j = 0; j < g->V; j++)
            sum += g->a[i][j];

        if(sum == 1) (*terminalNodes)++;

        if(*terminalNodes > 2)
        {
            (*worthSearching) = 0;
        }

        int j;
        visited[i] = id;
        for (j = 0; j < g->V; j++) 
            if (g->a[i][j] == 1 && visited[j] == 0)
                DFS_scan(g, visited, j, worthSearching, id, terminalNodes);
    }
    */
}

void DFS(Graph *g, int *maxLength, Coordinates *Path) {/*
    int i, comp_conexe = 0, visited[g->V], id = 0;
    for (i = 0; i < g->V; i++)
        visited[i] = 0;
    for (i = 0; i < g->V; i++) 
        if (visited[i] == 0) {
            id++;
            int worthSearching = 1;
            int terminalNodes = 0;
            DFS_scan(g, visited, i, &worthSearching, id, &terminalNodes);

            if(worthSearching)
            {
                int numberOfNodes = 0;
                for(int j=0; j<g->V; j++)
                    if(visited[j] == id)
                        numberOfNodes ++;
                
                Coordinates* path = NULL;
                int length = findHamiltonianPath(g, numberOfNodes, &path);
                if(length > (*maxLength))
                {
                    (*maxLength) = length;
                    *Path = path;
                }
                else free(path);
            }
        }
    */
}

int findHamiltonianPath(Graph* g, int numberOfNodes, Coordinates **path)
{
    return 0;
}