#include "headerRing.h"
#include "../myLibrary.h"

void pushAfter (struct Ring **p, char* newName)
{
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));
    tmp->next = NULL;
    tmp->prev = NULL;
    strcpy(tmp->name, newName);
    if(*p == NULL)
    {
        tmp->next = tmp;
        tmp->prev = tmp;
        *p = tmp;
    }
    else
    {
        tmp->next = (*p)->next;
        (*p)->next->prev = tmp;
        tmp->prev = (*p);
        (*p)->next = tmp;
        (*p) = tmp;
    }
}

void deleteCurrent (struct Ring **p)
{
    if ((*p) == NULL)
    {
        printf("\nКольцо пустое");
        return;
    }
    if ((*p) == (*p)->next)
    {
        free(*p);
        (*p) = NULL;
        return;
    }
    struct Ring *tmp = (*p);
    (*p)->next->prev = (*p)->prev;
    (*p)->prev->next = (*p)->next;
    (*p) = (*p)->next;
    free(tmp);
}


struct Ring* mergeRingsInOne(struct Ring* p1, struct Ring* p2)
{
    if (p1 == NULL)
    {
        return p2;
    }
    if (p2 == NULL)
    {
        return p1;
    }

    int flag1 = 1, flag2 = 1;
    struct Ring* tmp1 = p1;
    struct Ring* tmp2 = p2;
    struct Ring* p3 = NULL;

    if (strcmp(p1->name, p2->name) < 0)
    {
        p3 = tmp1;
        tmp1 = tmp1->next;
    }
    else
    {
        p3 = tmp2;
        tmp2 = tmp2->next;
    }

    struct Ring* newRing = p3;

    while (flag1 && flag2)
    {
        if (strcmp(tmp1->name, tmp2->name) < 0)
        {
            newRing->next = tmp1;
            tmp1->prev = newRing;
            tmp1 = tmp1->next;
            if (tmp1 == p1)
            {
                flag1 = 0;
            }
        }
        else
        {
            newRing->next = tmp2;
            tmp2->prev = newRing;
            tmp2 = tmp2->next;
            if (tmp2 == p2)
            {
                flag2 = 0;
            }
        }
        newRing = newRing->next; // Обновляем newRing
    }

    while (tmp1 != p1)
    {
        newRing->next = tmp1;
        tmp1->prev = newRing;
        tmp1 = tmp1->next;
        newRing = newRing->next; // Обновляем newRing
    }
    while (tmp2 != p2)
    {
        newRing->next = tmp2;
        tmp2->prev = newRing;
        tmp2 = tmp2->next;
        newRing = newRing->next; // Обновляем newRing
    }

    newRing->next = p3; // Устанавливаем связь с начальным элементом, чтобы завершить кольцо
    p3->prev = newRing;

    return p3;
}

void inputRing (struct Ring **p)
{
    char* name = NULL;
    printf("\nВведите имена. Чтобы завершить ввод, введите Enter");
    do
    {
        printf("\nВведите имя - ");
        inputStr(&name);
        if(name[0] == '\0') break;
        pushAfter(p, name);
    }while(1);
    if((*p) != NULL){(*p) = (*p)->next;}
}





void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound)
{
    char* task = NULL;
    printf("\nВыберите действие:\n");
    printf("\033[30;42m'mergeRings'\033[0m - ввод данных с клавиатуры\n");
    printf("\033[30;42m'sortRing'\033[0m - использовать готовые данные из файла\n");
    printf("\033[30;42m'couting'\033[0m - добавить данные в структуру\n");
    printf("\033[30;42m'finish'\033[0m - завершить программу\n");
    rewind(stdin);
    inputStr(&task);
    for(*doTask = mergeRings; *doTask < finish; (*doTask)++)
    {
        if(strcmp(task, tasks[*doTask]) == 0)
        {
            *taskIsFound = true;
            break;
        }
    }
}

struct Ring* sortingRing(struct Ring *p)
{
    if (p == NULL || p->next == p) {
        return p; // Возвращаем список, если он пустой или содержит только один элемент
    }

    struct Ring *start = p; // Запоминаем начальный элемент списка

    int sorted = 0;
    while (!sorted) {
        sorted = 1;
        struct Ring *tmp = p->next;
        while (tmp != p) {
            if (strcmp(tmp->name, tmp->prev->name) < 0) {
                sorted = 0;
                char tmpName[SIZE];
                strcpy(tmpName, tmp->name);
                strcpy(tmp->name, tmp->prev->name);
                strcpy(tmp->prev->name, tmpName);
            }
            tmp = tmp->next;
        }
    }

    return start;
}

void printRing (struct Ring *p)
{
    printf("\n\033[3;34mСодержимое кольца:\033[0m");
    system("clear");
    if (p == NULL)
    {
        printf("\n\033[1;41m\033[1mКольцо пустое\033[0m");
        return;
    }
    struct Ring *tmp = p;
    printf("\n");
    do
    {
        printf("\033[32m%s\033[0m\033[1;31m <-> \033[0m", tmp->name);
        tmp = tmp->next;
    }while(tmp != p);
    printf("\n");
    printf("\033[1;31m↑\033[0m");
    do
    {
        for(int i = 0; i < strlen(tmp->name) + 4; i++)
            printf("\033[1;31m_\033[0m");

        tmp = tmp->next;
    }while(tmp != p);
    printf("\033[1;31m|\033[0m");
}
