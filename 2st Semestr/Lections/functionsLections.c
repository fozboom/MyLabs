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




void fhkjdshg ()
{
    int n, s;
    char* str;
    struct Ring *p = NULL;
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));
    printf("Введите кол-во игроков\n");
    scanf("%d", &n);
    rewind(stdin);
    for(int i = 0; i < n; i++)
    {
        printf("Введите %d фамилию   ", i+1 );
        inputStr((&str));
        push_after(&p, str);
    }
    print(p);
    printf("Введите кол-во слов считалочки\n");
    scanf("%d", &s);
    rewind(stdin);
    while(p != p->next)
    {
        tmp = p;
        for(int i = 0; i < s - 2; i++)
        {
            tmp = tmp->next;
        }
        p = tmp;
        pop(&p);

    }
    print(p);
}