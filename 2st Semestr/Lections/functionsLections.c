#include "headerLections.h"
#include "../myLibrary.h"

void push_after (struct Ring **p, char* str)
{
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));
    tmp->name = str;
    tmp->next = NULL;
    if(*p != NULL)
    {
        tmp->next = (*p)->next;
        (*p)->next = tmp;
    }
    else
    {
        tmp->next = tmp;
        *p = tmp;
    }
}

void pop (struct Ring **p)
{
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));
    if ((*p) == NULL) return;
    if((*p) == (*p)->next)
    {
        free(*p);
        *p = NULL;
    }
    else
    {
        tmp = (*p)->next;
        (*p)->next = (*p)->next->next;
        free(tmp);
    }
}

void print(struct Ring* p)
{
    struct Ring* temp = p;
    if (p == NULL) printf("EMPTY\n");
    else
    {
        do
        {
            printf("%s   ", temp->name);
            temp = temp->next;
        } while (temp != p);
    }
    printf("\n");
}