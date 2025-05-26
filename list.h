#pragma once
#include <stdio.h>
#include <stdlib.h>

struct Element
{
    int x, y;
    struct Element* next;
};

typedef struct Element listNode;

void addAtBeginning(listNode** head, int x, int y);

void addAtEnd(listNode** head, int x, int y);

void printRec(listNode *head, FILE* output);

void freeList(listNode *head);