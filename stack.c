#include "stack.h"

void push(stackNode** top, listNode* head)
{
    stackNode* newStackNode = (stackNode*)malloc(sizeof(stackNode));
    newStackNode -> val = head;
    newStackNode -> next = *top;
    *top = newStackNode;
}

void deleteStack(stackNode** top)
{
    while((*top) != NULL)
    {
        stackNode* temp = (*top);
        *top = (*top) -> next;

        freeList(temp -> val);
        free(temp);
    }
}