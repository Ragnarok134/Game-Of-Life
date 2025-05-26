#include "functions.h"

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
