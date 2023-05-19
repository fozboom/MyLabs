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
    free(*p);
    *p = NULL;
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
    printf("\033[30;42m'counting'\033[0m - считалочка\n");
    printf("\033[30;42m'save'\033[0m - сохранить данные файл\n");
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
    free(task);
}

struct Ring* sortingRing(struct Ring *p)
{
    if (p == NULL || p->next == p) {
        return p;
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

void countingHumans (struct Ring **p)
{
    char* phrase = NULL, *win = NULL;
    int count = 1;
    if (*p == NULL)
    {
        printf("\nВы не ввели список людей");
        return;
    }
    if(*p == (*p)->next)
    {
        printf("\nВ списке один человек - %s", (*p)->name);
        return;
    }
    printf("\nВведите слова считалочки: ");
    inputStr(&phrase);
    for (int i = 0; phrase[i+1] != '\0'; i++)
    {
        if(!ifLetter(phrase[i]) && ifLetter(phrase[i+1]))
        {
            count++;
        }
    }
    while ((*p) != ((*p)->next))
    {
        for (int i = 0; i < count - 1; i++)
        {
            (*p) = (*p)->next;
        }
        deleteCurrent(p);
    }
}

int ifLetter (char s)
{
    if (s >= 'a' && s <= 'z')
        return 1;
    if (s >= 'A' && s <= 'Z')
        return 1;
    return 0;
}

void freeRing(struct Ring *p1, struct Ring *p2, struct Ring *newRing)
{
    if(p1 != NULL)
    {
        while (p1->next != NULL)
        {
            struct Ring *tmp = p1;
            p1->next->prev = p1->prev;  // Обновляем ссылку на предыдущий элемент
            p1->prev->next = p1->next;  // Обновляем ссылку на следующий элемент
            p1 = p1->next;              // Переходим к следующему элементу
            free(tmp);                  // Освобождаем память текущего элемента
        }
    }
    if (p2 != NULL)
    {
        while (p2->next != NULL)
        {
            struct Ring *tmp = p2;
            p2->next->prev = p2->prev;  // Обновляем ссылку на предыдущий элемент
            p2->prev->next = p2->next;  // Обновляем ссылку на следующий элемент
            p2 = p2->next;              // Переходим к следующему элементу
            free(tmp);                  // Освобождаем память текущего элемента
        }
    }
    if(newRing != NULL)
    {
        while (newRing->next != NULL)
        {
            struct Ring *tmp = newRing;
            newRing->next->prev = newRing->prev;  // Обновляем ссылку на предыдущий элемент
            newRing->prev->next = newRing->next;  // Обновляем ссылку на следующий элемент
            newRing = newRing->next;              // Переходим к следующему элементу
            free(tmp);
        }
    }

}

void saveToFile(struct Ring* p, char* filename, int format)
{
    FILE* file;
    if (format == 1)
        file = fopen(filename, "w"); // Открытие файла в текстовом формате для записи
    else
        file = fopen(filename, "wb"); // Открытие файла в бинарном формате для записи

    if (file == NULL)
    {
        printf("Ошибка открытия файла для записи.\n");
        return;
    }

    struct Ring* tmp = p;
    if (tmp != NULL)
    {
        do
        {
            if (format == 1)
                fprintf(file, "%s\n", tmp->name); // Запись в текстовом формате
            else
                fwrite(tmp->name, sizeof(char), SIZE, file); // Запись в бинарном формате
            tmp = tmp->next;
        } while (tmp != p);
    }

    fclose(file);
}

struct Ring* readFromFile(char* filename, int format)
{
    FILE* file;
    if (format == 1)
        file = fopen(filename, "r"); // Открытие файла в текстовом формате для чтения
    else
        file = fopen(filename, "rb"); // Открытие файла в бинарном формате для чтения


    if (file == NULL)
    {
        printf("Ошибка открытия файла для чтения.\n");
        return NULL;
    }

    struct Ring* p = NULL;
    char name[SIZE];

    if (format == 1)
    {
        while (fgets(name, SIZE, file) != NULL)
        {
            name[strcspn(name, "\n")] = '\0'; // Удаляем символ новой строки
            pushAfter(&p, name);
        }
    }
    else
    {
        while (fread(name, sizeof(char), SIZE, file) != 0)
        {
            pushAfter(&p, name);
        }
    }

    fclose(file);

    return p;
}


void howToInput (int* input, int* format, struct Ring **tmp)
{
    char* fileName;
    printf("\nКак вы хотите заполнить кольцо?");
    printf("\n0 - чтение кольца из файла");
    printf("\n1 - ввод кольца вручную\n");
    inputInt(input, 0, 1);
    if ((*input) == 1)
    {
        inputRing(tmp);
    }
    if ((*input) == 0)
    {
        printf("\nИз какого файла вы будете читать информацию?");
        printf("\n0 - чтение из бинарного файла");
        printf("\n1 - чтение из текстового файла\n");
        inputInt(format, 0, 1);
        printf("\nВведите имя файла - ");
        inputStr(&fileName);
        *tmp = readFromFile(fileName, *format);
        printRing(*tmp);
    }

}

void howToSave (int* input, int* format, struct Ring *tmp)
{
    char* fileName;
    printf("\nВ какой файл вы хотите сохранить информацию?");
    printf("\n0 - в бинарный файл");
    printf("\n1 - в текстовый файл\n");
    inputInt(format, 0, 1);
    printf("\nВведите имя файла - ");
    inputStr(&fileName);
    saveToFile(tmp, fileName, *format);
}

void deleteName (struct Ring **p)
{
    if((*p) == NULL)
    {
        printf("\nКольцо пустое");
        return;
    }
    char* name;
    int flag = 0;
    printf("\nВведите имя человека, которого хотите исключить из кольца - ");
    inputStr(&name);

    struct Ring *tmp = (*p);
    while (tmp->next != (*p))
    {
        if (strcmp(name, tmp->name) == 0)
        {
            flag = 1;
            break;
        }
        tmp = tmp->next;
    }
    if (flag)
    {
        (*p) = tmp;
        deleteCurrent(p);
    }
    else
    {
        printf("\nТакое имя не найдено");
    }
    free(name);
}

void doYouWantToDelete (struct Ring **p)
{
    int flag;
    printf("\nЕсли желаете удалить кого-то из кольца, введите 1");
    printf("\nЕсли не желаете, введите 0\n");
    inputInt(&flag, 0, 1);
    if(flag)
    {
        deleteName(p);
    }
}


void caseMergeRings (int* input, int* format, struct Ring **p1, struct Ring **p2, struct Ring **newRing)
{
    howToInput(input, format, p1);
    doYouWantToDelete (p1);
    howToInput(input, format, p2);
    doYouWantToDelete (p2);
    *p1 = sortingRing(*p1);
    *p2 = sortingRing(*p2);
    *newRing = mergeRingsInOne(*p1, *p2);
    system("clear"); printf("\nРезультат слияния двух колец:");
    printRing(*newRing);
}

void caseSortRing (int* input, int* format, struct Ring **p1, struct Ring **p2, struct Ring **newRing)
{
    howToInput(input, format, p1);
    printf("\nВы ввели следующее кольцо:"); system("clear");
    printRing(*p1);
    doYouWantToDelete (p1);
    printf("\nОтсортированное кольцо:");
    *newRing = sortingRing(*p1);
    printRing(*newRing);
}

void caseCounting (int* input, int* format, struct Ring **newRing)
{
    howToInput(input, format, newRing);
    doYouWantToDelete (newRing);
    countingHumans(newRing);
    printf("\nПобедитель - %s", (*newRing)->name);
}

