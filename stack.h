#pragma once
#include "list.h"

struct S
{
    listNode* val;
    struct S* next;
};

typedef struct S stackNode;

void push(stackNode** top, listNode* head);

void deleteStack(stackNode** top);
