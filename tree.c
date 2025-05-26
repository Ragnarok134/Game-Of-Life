#include "tree.h"

void preorder(treeNode *root, char **matrix, int N, int M, FILE* filename)
{
    if(root)
    {
        //Updating the matrix to match the current generation
        updateMatrix(matrix, root -> head);

        //Making a copy to undo changes made in the next calls of the function
        char **oldMatrix;
        oldMatrix = (char **)malloc(sizeof(char*) * N);
        for(int i=0; i<N; i++)
            oldMatrix[i] = (char*)malloc(sizeof(char) * M);
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<M; j++)
            {
                oldMatrix[i][j] = matrix[i][j];
                fprintf(filename, "%c", matrix[i][j]);
            }
            fprintf(filename,"\n");
        }
        fprintf(filename,"\n");

        preorder(root -> left, matrix, N, M, filename);

        copyMatrix(matrix, oldMatrix, N, M);
        
        preorder(root -> right, matrix, N, M, filename);

        copyMatrix(matrix, oldMatrix, N, M);

        for (int i = 0; i < N; i++)
            free(oldMatrix[i]);
        free(oldMatrix);
    }
}

void freeTree(treeNode* root)
{
    if(!root) return;
    freeList(root->head);
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}
