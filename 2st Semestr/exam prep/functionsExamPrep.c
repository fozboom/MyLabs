#include "headerExamPrep.h"

void pushFILO (struct FILO ** head, int info, int * n)
{
    struct FILO * tmp = (struct FILO *)malloc(sizeof(struct FILO));
    tmp->data = info;
    tmp->next = NULL;
    if(*head == NULL)
    {
        *head = tmp;
    }
    else
    {
        tmp->next = *head;
        *head = tmp;
    }
    (*n)++;
}

void popFILO (struct FILO ** head, int * n)
{
    struct FILO * tmp;
    if(*head == NULL)
    {
        return;
    }
    tmp = *head;
    (*head) = (*head)->next;
    free(tmp);
    (*n)--;
}

int checkStack (struct FILO * head, int info)
{
    struct FILO * tmp = head;
    if (head != NULL)
    {
        while (tmp != NULL)
        {
            if (tmp->data == info)
                return 1;
            tmp = tmp->next;
        }
    }
    return 0;
}


void input2FILO (struct FILO ** head1, struct FILO ** head2, int * n1, int * n2, int max1, int max2)
{
    int x;
    while (*n1 < max1 && *n2 < max2)
    {
        scanf("%d", &x);
        if(checkStack(*head1, x))
        {
            pushFILO(head2, x, n2);
        }
        else
        {
            pushFILO(head1, x, n1);
        }
    }
}



































void pushFIFO (struct FIFO ** head, struct FIFO ** tail, int * n, int info)
{
   struct FIFO * tmp = (struct FIFO *)malloc(sizeof(struct FIFO));
   tmp->data = info;
   tmp->next = NULL;
   if (*tail == NULL)
   {
       *head = tmp;
       *tail = tmp;
   }
   else
   {
       (*tail)->next = tmp;
       *tail = tmp;
   }
   (*n)++;
}

void popFIFO (struct FIFO ** head, struct FIFO ** tail, int * n, int * info)
{
    if(*head == NULL)
    {
        return;
    }
    else
    {
        *info = (*head)->data;
        struct FIFO * tmp = *head;
        *head = (*head)->next;
        free(tmp);
        if (*head == NULL)
        {
            *tail = NULL;
        }
    }
    (*n)--;
}

//ввожу элементы, потому перехожу в режим:
//ввожу и удаляю, если удаленный равен введенному, добавляю его
void taskFIFO (struct FIFO ** head, struct FIFO ** tail, int * n, int max)
{
    int x, info;
    while (*n < max - 3)
    {
        scanf("%d", &x);
        pushFIFO(head, tail, n, x);
    }
    for (int i = *n; *n < max; i++)
    {
        scanf("%d", &x);
        pushFIFO(head, tail, n, x);
        popFIFO(head, tail, n, &info);
        if (x == info)
        {
            pushFIFO(head, tail, n, x);
        }
    }
}










































void pushFIFO2 (struct FIFO2 ** head, struct FIFO2 ** tail, int info)
{
    struct FIFO2 * tmp = (struct FIFO2 *)malloc(sizeof(struct FIFO2));
    tmp->data = info;
    tmp->next = NULL;
    tmp->prev = NULL;
    if (*head == NULL)
    {
        *head = tmp;
        *tail = tmp;
    }
    else
    {
        (*tail)->next = tmp;
        tmp->prev = *tail;
        *tail = tmp;
    }
}


void popFIFO2 (struct FIFO2 ** head, struct FIFO ** tail, int * info)
{
   if (*head == NULL)
       return;
   else
   {
       *info = (*head)->data;
       struct FIFO2 * tmp = *head;
       *head = (*head)->next;
       free(tmp);
       if (*head == NULL)
       {
           *tail = NULL;
           return;
       }
       (*head)->prev = NULL;
   }
}


int countFIFO2 (struct FIFO2 * head, struct FIFO2 * tail)
{
    if (head == NULL)
        return 0;
    int count = 1;
    while (head != tail)
    {
        count++;
       head = head->next;
    }
    return count;
}

void sortFIFO2 (struct FIFO2 ** head, struct FIFO2 ** tail)
{
    if (*head == NULL || *head == *tail)
        return;
    int n = countFIFO2(*head, *tail);
    struct FIFO2 * tmp1, * tmp2;
    int flag = 1;
    while (flag)
    {
        tmp1 = *head, tmp2 = (*head)->next;
        flag = 0;
        for(int i = 0; i < n - 1; i++)
        {
            if (tmp1->data > tmp2->data)
            {
                if (tmp1->prev != NULL)
                {
                    tmp1->prev->next = tmp2;
                }
                else
                {
                    *head = tmp2;
                }
                if (tmp2->next != NULL)
                    tmp2->next->prev = tmp1;
                else
                {
                    *tail = tmp1;
                }
                flag = 1;
                tmp1->next = tmp2->next;
                tmp1->prev = tmp2;
                tmp2->prev = tmp1->prev;
                tmp2->next = tmp1;
                tmp2 = tmp1->next;
            }
            else
            {
                tmp1 = tmp2;
                tmp2=tmp2->next;
            }
        }
    }
}



void pushFrontDeq (struct Deq ** head, struct Deq ** tail, int info)
{
    struct Deq * tmp = (struct Deq *)malloc(sizeof(struct Deq));
    tmp->data = info;
    tmp->next = NULL;
    tmp->prev = NULL;
    if (*head == NULL)
    {
        *head = tmp;
        *tail = tmp;
    }
    else
    {
        tmp->next = *head;
        (*head)->prev = tmp;
        *head = tmp;
    }
}

void pushBackDeq (struct Deq ** head, struct Deq ** tail, int info)
{
    struct Deq * tmp = (struct Deq *)malloc(sizeof(struct Deq));
    tmp->data = info;
    tmp->next = NULL;
    tmp->prev = NULL;
    if (*tail == NULL)
    {
        *head = tmp;
        *tail = tmp;
    }
    else
    {
        (*tail)->next = tmp;
        tmp->prev = *tail;
        *tail = (*tail)->next;
    }
}

void popFrontDeq (struct Deq ** head, struct Deq ** tail, int * info)
{
    if (*head == NULL)
        return;
    *info = (*head)->data;
    struct Deq * tmp = *head;
    *head = (*head)->next;
    free(tmp);
    if (*head == NULL)
    {
        *tail = NULL;
        return;
    }
    (*head)->prev = NULL;
}

void popBackDeq (struct Deq ** head, struct Deq ** tail, int * info)
{
    if (*tail == NULL)
        return;
    *info = (*tail)->data;
    struct Deq * tmp = *tail;
    *tail = (*tail)->prev;
    free(tmp);
    if (*tail == NULL)
    {
        *head = NULL;
        return;
    }
    (*tail)->next = NULL;
}




