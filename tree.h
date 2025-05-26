#pragma once
#include "list.h"

struct N
{
    listNode *head;
    struct N *left, *right;
};

typedef struct N treeNode;

void updateMatrix(char** matrix, listNode* head);
void copyMatrix(char **dst, char **src, int N, int M);
void preorder(treeNode *root, char **matrix, int N, int M, FILE* filename);
void freeTree(treeNode* root);
