#include "headerLections.h"

void push_after (struct Ring **p, int a)
{
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));
    tmp->data = a;
    tmp->next = NULL;
    if(*p != NULL)
    {
        struct Ring *pz = (*p)->next;
        (*p)->next = tmp;
        tmp->next = pz;
    }
    else
    {
        tmp->next = tmp;
        *p=tmp;
    }
}

void push_before (struct Ring **p, int a)
{
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));
    tmp->data = a;
    tmp->next = NULL;
    if(*p != NULL)
    {
        struct Ring *pz = *p;
        while(pz->next != *p)
            pz = pz->next;
        pz->next = tmp;
        tmp->next = *p;
    }
    else
    {
        tmp->next = tmp;
        *p = tmp;
    }
}

void pop(struct Ring** p)
{
    if (*p==NULL) return;
    if (*p== (*p)->next)
    {
        free(*p);
        *p = NULL;
    }
    else
    {
        struct Ring* temp;
        temp = (*p)->next;
        (*p)->next = (*p)->next->next;
        free( temp);
    }
}

void pushDoubleRing(struct DoubleRing** p, int x)
{
    struct DoubleRing* temp;
    temp = (struct DoubleRing *) calloc (1,sizeof(struct DoubleRing));
    temp->next = NULL;
    temp->prev = NULL;
    temp->data = x;
    if (*p == NULL)
    {
        temp->next = temp;
        temp->prev = temp;
        *p = temp;
    }
    else
    {
        temp->next = (*p)->next;
        (*p)->next->prev = temp;
        (*p)->next = temp;
        temp->prev = *p;
        *p = temp;
    }
}


void popDoubleRing(struct DoubleRing** p)
{
    if (*p == NULL)
    {
        return ;
    }
    if (*p == (*p)->next)
    {
        free(*p);
        *p = NULL;
    }
    else
    {
        struct DoubleRing* temp;
        temp = (*p)->next;
        (*p)->next = temp->next;
        temp->next->prev = *p;
        free(temp);
    }
}

