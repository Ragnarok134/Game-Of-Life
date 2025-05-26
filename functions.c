#include "functions.h"

void copyMatrix(char **dst, char **src, int N, int M)
{
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            dst[i][j] = src[i][j];
}

void read(int *T, int *N, int *M, int *K, char ***matrix, const char *file) 
{
    FILE *input = fopen(file, "rt");

    if (input == NULL) 
    {
        exit(1);
    }

    fscanf(input, "%d", T);
    fscanf(input, "%d%d", N, M);
    fscanf(input, "%d", K);

    //Creating matrix to store the cells
    *matrix = (char **)malloc(sizeof(char *) * (*N));

    if (*matrix == NULL) 
    {
        exit(1);
    }

    for (int i = 0; i < (*N); i++) 
    {
        (*matrix)[i] = (char *)malloc(sizeof(char) * (*M));

        if ((*matrix)[i] == NULL) 
        {
            for (int j = 0; j < i; j++) 
            {
                free((*matrix)[j]);
            }

            free(*matrix);
            exit(1);
        }
    }

    //Reading the content of the matrix
    for (int i = 0; i < (*N); i++) 
    {
        for (int j = 0; j < (*M); j++) 
        {
            fscanf(input, " %c", &((*matrix)[i][j]));
        }
    }

    fclose(input);
}

void write(FILE *output, char **matrix, int N, int M) 
{
    if (output == NULL) 
    {
        exit(1);
    }

    for (int i = 0; i < N; i++, fprintf(output, "\n")) 
    {
        for (int j = 0; j < M; j++) 
        {
            fprintf(output, "%c", matrix[i][j]);
        }
    }

    fprintf(output, "\n");
}

int aliveNeighbours(char **matrix, int N, int M, int i, int j)
{
    int alive_neighbours = 0;
                
    if (i > 0 && j > 0) 
        if(matrix[i - 1][j - 1] == 'X') alive_neighbours++;
    if (i > 0)
        if(matrix[i - 1][j] == 'X') alive_neighbours++;
    if (i > 0 && j < M - 1)
        if(matrix[i - 1][j + 1] == 'X') alive_neighbours++;
    if (j > 0)
        if(matrix[i][j - 1] == 'X') alive_neighbours++;
    if (j < M - 1)
        if(matrix[i][j + 1] == 'X') alive_neighbours++;
    if (i < N - 1 && j > 0)
        if(matrix[i + 1][j - 1] == 'X') alive_neighbours++;
    if (i < N - 1)
        if(matrix[i + 1][j] == 'X') alive_neighbours++;
    if (i < N - 1 && j < M - 1) 
        if(matrix[i + 1][j + 1] == 'X') alive_neighbours++;

    return alive_neighbours;
}

void task1(int N, int M, int K, char **matrix, FILE *output) 
{
    //Creating the new auxiliary matrix
    char **new_matrix;

    new_matrix = (char **)malloc(sizeof(char*) * N);
    
    if (new_matrix == NULL)
    {
        exit(1);
    }

    for (int i = 0; i < N; i++) 
    {
        new_matrix[i] = (char *)malloc(sizeof(char) * M);
        
        if (new_matrix[i] == NULL) 
        {   
            for (int j = 0; j < i; j++)
                free(new_matrix[j]);
            
            free(new_matrix);
            exit(1);
        }
    }

    //Displaying the initial matrix
    write(output, matrix, N, M);

    //Representing each of the K generations
    for (int p = 1; p <= K; p++) 
    {
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < M; j++) 
            {   
                //Checking the number of alive neighbours for each of the cells

                int alive_neighbours = aliveNeighbours(matrix, N, M, i, j);

                //Checking the rules of the game to establish the following generation
                if ((matrix[i][j] == 'X' && (alive_neighbours == 2 || alive_neighbours == 3)))
                    new_matrix[i][j] = 'X';

                if (matrix[i][j] == '+' && alive_neighbours != 3)
                    new_matrix[i][j] = '+';

                if ((matrix[i][j] == 'X' && (alive_neighbours < 2 || alive_neighbours > 3)))
                    new_matrix[i][j] = '+';

                if (matrix[i][j] == '+' && alive_neighbours == 3)
                    new_matrix[i][j] = 'X';
            }
        }

        //Modifying the current matrix to store the new generation of cells 
        for (int i = 0; i < N; i++) 
        {
            for (int j = 0; j < M; j++) 
            {
                matrix[i][j] = new_matrix[i][j];
            }
        }

        write(output, matrix, N, M);
    }

    //Cleaning up
    for (int i = 0; i < N; i++) 
    {
        free(matrix[i]);
    }

    free(matrix);

    for (int i = 0; i < N; i++) 
    {
        free(new_matrix[i]);
    }

    free(new_matrix);
}

void updateMatrix(char** matrix, listNode* head)
{
    listNode* index = head;

    while(index != NULL)
    {
        int x = index -> x;
        int y = index -> y;

        if(matrix[x][y] == '+')
            matrix[x][y] = 'X';
        else 
            matrix[x][y] = '+';

        index = index -> next;
    }
}

void showGenerations(stackNode* top, int index, FILE* output)
{
    if(!top)
        return;

    if(index > 1)
        showGenerations(top -> next, index - 1, output);
    fprintf(output, "%d", index);
    printRec(top -> val, output);
    fprintf(output, "\n");
}

void task2(int N, int M, int K, char **matrix, FILE *output)
{
    stackNode* top = NULL;

    listNode* head = NULL;

    for(int p = 1; p <= K; p++)
    {
        if(p > 1)
        {
            updateMatrix(matrix, top -> val);
        }

        head = NULL;

        for(int i = 0; i < N; i++)
        {
           for(int j = 0; j < M; j++)
           {
            int alive_neighbours = aliveNeighbours(matrix, N, M, i, j);

            if ((matrix[i][j] == 'X' && (alive_neighbours < 2 || alive_neighbours > 3)))
                addAtEnd(&head, i, j);

            if (matrix[i][j] == '+' && alive_neighbours == 3)
                addAtEnd(&head, i, j);
            }
        }

        push(&top, head);

        //free(head);
    }

    showGenerations(top, K, output);



    //Cleaning up

    for (int i = 0; i < N; i++) 
    {
        free(matrix[i]);
    }

    free(matrix);

    deleteStack(&top);

}

treeNode* ruleA(treeNode* root, char **matrix, int N, int M)
{
    listNode *head = NULL;
    treeNode *child = (treeNode*)malloc(sizeof(treeNode));
    child -> left = NULL;
    child -> right = NULL;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            int alive_neighbours = aliveNeighbours(matrix, N, M, i, j);

            if ((matrix[i][j] == 'X' && (alive_neighbours < 2 || alive_neighbours > 3)))
                addAtEnd(&head, i, j);

            if (matrix[i][j] == '+' && alive_neighbours == 3)
                addAtEnd(&head, i, j);
        }
    }

    child -> head = head;

    return child;
}

treeNode* ruleB(treeNode* root, char **matrix, int N, int M)
{
    listNode *head = NULL;
    treeNode *child = (treeNode*)malloc(sizeof(treeNode));
    child -> left = NULL;
    child -> right = NULL;

    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            int alive_neighbours = aliveNeighbours(matrix, N, M, i, j);

            if(matrix[i][j] == '+' && alive_neighbours == 2)
                addAtEnd(&head, i, j);
        }
    }

    child -> head = head;

    return child;
}

void generateTree(treeNode** root, int N, int M, int K, char **matrix, int generation)
{
    if(generation > K)  return;

    //Updating the matrix to match the current generation
    updateMatrix(matrix, (*root) -> head);

    //Making a copy to undo changes made in the next calls of the function
    char **oldMatrix;

    oldMatrix = (char **)malloc(sizeof(char*) * N);
    for(int i=0; i<N; i++)
        oldMatrix[i] = (char*)malloc(sizeof(char) * M);

    copyMatrix(oldMatrix, matrix, N, M);

    //Left branch
    (*root) -> left = ruleB(*root, matrix, N, M);

    generateTree(&((*root) -> left), N, M, K, matrix, generation + 1);

    //Reset matrix to current generation
    copyMatrix(matrix, oldMatrix, N, M);

    //Right branch
    (*root) -> right = ruleA(*root, matrix, N, M);

    generateTree(&((*root) -> right), N, M, K, matrix, generation + 1);

    //Reset matrix to current generation
    copyMatrix(matrix, oldMatrix, N, M);

    //Cleanup
    for (int i = 0; i < N; i++)
        free(oldMatrix[i]);
    free(oldMatrix);

}

void task3(int N, int M, int K, char **matrix, FILE *output)
{
    //Create root
    treeNode *root = (treeNode*)malloc(sizeof(treeNode));

    root -> head = NULL;
    root -> left = NULL;
    root -> right = NULL;
    
    generateTree(&root, N, M, K, matrix, 1);

    preorder(root, matrix, N, M, output);

    //Cleanup
    freeTree(root);

    for (int i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);

}

/*
void generateTreeTask4(treeNode** root, int N, int M, int K, char **matrix, int generation, int *maxLength, Coordinates **Path)
{
    if(generation > K)  return;

    //Updating the matrix to match the current generation
    updateMatrix(matrix, (*root) -> head);

    Graph *g = (Graph*)malloc(sizeof(Graph));
    g -> V = numberOfNodes(matrix, N, M);
    int** adj = generateAdjacencyMatrix(matrix, N, M, g -> V);
    g -> a = adj;
    //Search hamiltonian chain in adj
    *maxLength = -1;
    *Path = NULL;

    //Making a copy to undo changes made in the next calls of the function
    char **oldMatrix;

    oldMatrix = (char **)malloc(sizeof(char*) * N);
    for(int i=0; i<N; i++)
        oldMatrix[i] = (char*)malloc(sizeof(char) * M);

    copyMatrix(oldMatrix, matrix, N, M);

    //Left branch
    (*root) -> left = ruleB(*root, matrix, N, M);

    generateTree(&((*root) -> left), N, M, K, matrix, generation + 1);

    //Reset matrix to current generation
    copyMatrix(matrix, oldMatrix, N, M);

    //Right branch
    (*root) -> right = ruleA(*root, matrix, N, M);

    generateTree(&((*root) -> right), N, M, K, matrix, generation + 1);

    //Reset matrix to current generation
    copyMatrix(matrix, oldMatrix, N, M);

    //Cleanup
    for (int i = 0; i < N; i++)
        free(oldMatrix[i]);
    free(oldMatrix);
}
*/
void task4(int N, int M, int K, char **matrix, FILE *output)
{
//Create root
    treeNode *root = (treeNode*)malloc(sizeof(treeNode));

    root -> head = NULL;
    root -> left = NULL;
    root -> right = NULL;
    
    generateTree(&root, N, M, K, matrix, 1);

    //Graph* g = (Graph*)malloc(sizeof(Graph));
    //g -> V = numberOfNodes(matrix, N, M);
    //g -> a = generateAdjacencyMatrix(matrix, N, M, g -> V);

    //preorder(root, matrix, N, M, output);

    //Cleanup
    freeTree(root);
    
    //for (int i = 0; i < g -> V; i++)
        //free(g -> a[i]);
    //free(g -> a);

    //free(g);

    for (int i = 0; i < N; i++)
        free(matrix[i]);
    free(matrix);

}

void identifyAndExecuteTask(int T, int N, int M, int K, char **matrix, FILE *output) 
{
    //Identifying the current task
    switch (T) 
    {   
        case 1: task1(N, M, K, matrix, output); break;
        case 2: task2(N, M, K, matrix, output); break;
        case 3: task3(N, M, K, matrix, output); break;
        case 4: task4(N, M, K, matrix, output); break;
    }
}

