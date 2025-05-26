#pragma once
#include "stack.h"
#include "tree.h"
#include "graph.h"

void copyMatrix(char **dst, char **src, int N, int M);

void read(int *T, int *N, int *M, int *K, char ***matrix, const char *file);

void write(FILE *output, char **matrix, int N, int M);

int aliveNeighbours(char **matrix, int N, int M, int i, int j);

void task1(int N, int M, int K, char **matrix, FILE *output);

void updateMatrix(char** matrix, listNode* head);

void showGenerations(stackNode* top, int index, FILE* output);

void task2(int N, int M, int K, char **matrix, FILE *output);

treeNode* ruleA(treeNode* root, char **matrix, int N, int M);

treeNode* ruleB(treeNode* root, char **matrix, int N, int M);

void generateTree(treeNode** root, int N, int M, int K, char **matrix, int generation);

void task3(int N, int M, int K, char **matrix, FILE *output);

void generateTreeTask4(treeNode** root, int N, int M, int K, char **matrix, int generation, int *maxLength, Coordinates **Path);

void task4(int N, int M, int K, char **matrix, FILE *output);

void identifyAndExecuteTask(int T, int N, int M, int K, char **matrix, FILE *output);
