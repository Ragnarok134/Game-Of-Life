#include <stdio.h>
#include <stdlib.h>

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

void identifyAndExecuteTask(int T, int N, int M, int K, char **matrix, FILE *output) 
{
    //Identifying the current task
    switch (T) 
    {   
        case 1: task1(N, M, K, matrix, output); break;
        //case 2: task2(); break;
        //case 3: task3(); break;
        //case 4: task4(); break;
    }
}

int main(int argc, const char **argv) 
{
    //Checking for the right amount of arguments
    if (argc != 3) 
    {
        exit(1);
    }

    FILE *output = fopen(argv[2],"wt");
    if (output == NULL) 
    {
        exit(1);
    }

    int T, N, M, K;
    char **matrix;

    read(&T, &N, &M, &K, &matrix, argv[1]);

    identifyAndExecuteTask(T, N, M, K, matrix, output);

    fclose(output);

    return 0;
}
