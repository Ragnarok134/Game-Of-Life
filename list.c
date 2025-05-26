#include "list.h"

void addAtBeginning(listNode** head, int x, int y)
{
    listNode *newNode = (listNode*)malloc(sizeof(listNode));
	newNode -> x = x;
    newNode -> y = y;
	newNode -> next = *head;
	*head = newNode;
}

void addAtEnd(listNode** head, int x, int y)
{
    if (*head == NULL) 
    {
        addAtBeginning(head, x, y);
        return ;
    }
        
    listNode *aux = *head;
    listNode *newNode = (listNode*)malloc(sizeof(listNode));
    newNode -> x = x;
    newNode -> y = y;

    while (aux->next != NULL) 
        aux = aux->next;
        
    aux->next = newNode;
    newNode->next = NULL;
}

void printRec(listNode *head, FILE* output)
{
    if (head != NULL) {
        fprintf(output, " %d %d", head -> x, head -> y);
        printRec(head->next, output);
    }
}

void freeList(listNode *head)
{
    if(head != NULL)
    {
        freeList(head -> next);
        free(head);
    }
}