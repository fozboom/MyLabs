#include "headerUnion.h"
#include "../myLibrary.h"


//функция быстрой сортировки с компаратором
void quickSorting(struct child *info, int first, int last, int (*function)(struct child* , int , int ))
{
    if(first < last)                                                        //если есть что сортировать
    {
        int left = first, right = last, middle = (left + right) / 2;        //middle - центральный элемент, left и right - левый и правый индексы
        do
        {
            while ((*function)(info, left, middle) == 1)                         //ищу первый элемент, который нужно в другую половину
                left++;
            while ((*function)(info, middle, right) == 1)                       //ищу второй элемент, который нужно в другую половину
                right--;
            if (left <= right)                                              //обмениваю местами элементы
            {
                struct child tmp = info[left];
                info[left] = info[right];
                info[right] = tmp;
                left++;
                right--;
            }
        } while (left < right);                                             //пока индексы не поменялись местами
        quickSorting(info, first, right, function);                    //рекурсивный вызов сортировки на левую половину
        quickSorting(info, left, last, function);                      //рекурсивный вызов сортировки на правую половину
    }
}



//компаратор для сортировки в алфавитном порядке фамилий
int comparatorSurnames (struct child *info, int i, int j)
{
    int x = strcmp(info[i].sureName, info[j].sureName);
    if (x < 0)
        return 1;
    else
        return 0;
}



//функция заполнения массива структур с клавиатуры
void inputStruct(struct child** info, int* n)
{
    int i = 0;                                                          //параметр цикла по массиву структур
    *info = (struct child*)calloc(*n, sizeof(struct child)); //выделение памяти на один элемент
    while (1)
    {
        printf("Введите фамилию ");
        inputString((*info + i)->sureName);
        if ((*info + i)->sureName[0] == '\0')                           //если пользователь ввел Enter, закончить ввод
        {
            break;
        }
        printf("Введите имя ");
        inputString((*info + i)->firstName);
        printf("Введите возраст ребенка ");
        inputInt(&(*info + i)->age, 1, 9);
        printf("Ребенок находился в больнице?");
        printf("\n1 - Да");
        printf("\n0 - Нет\n");
        inputInt (&((*info + i)->flag), 0, 1);
        printf("Введите болезнь ребенка ");
        inputString((*info + i)->information[0].disease);
        printf("Введите фамилию участкового врача ");
        inputString((*info + i)->information[1].familyDoctor);
        if ((*info + i)->flag)
        {
            printf("Введите адрес больницы ");
            inputString((*info + i)->information[2].address);
            printf("Введите номер больницы ");
            inputInt(&((*info + i)->information[3]).campusNumber, 0, 9);
            printf("Введите фамилию лечащего врача ");
            inputString((*info + i)->information[4].hospitalDoctor);
        }
        i++;
        (*n)++;
        *info = (struct child*)realloc(*info, (*n) * sizeof(struct child));        //выделение памяти на след элемент
    }

    *info = (struct child*)realloc(*info, (--(*n)) * sizeof(struct child));         //после ввода перевыделить память
}



//функция для записи информации в файл (бинарный или текстовый)
void inputWithFile(struct child *info, int n, const char* fileName)
{
    int task;
    printf("\nЧтобы записать информацию в текстовый файл, введите 0\n");
    printf("\nЧтобы записать информацию в бинарный файл, введите 1\n");
    inputInt(&task, 0, 1);
    if (task == 0)
    {
        writeInTekstFile(info, n, fileName);
    }
    else if(task == 1)
    {
        writeInBinaryFile(info, n, fileName);
    }
}



//функция чтения информации из файла (бинарного или текстового)
void readWithFile(struct child **info, int *n, const char* fileName)
{
    int task;
    printf("\nЧтобы считать информацию из текстового файла, введите 0\n");
    printf("\nЧтобы считать информацию из бинарного файла, введите 1\n");
    inputInt(&task, 0, 1);
    if (task == 0)
    {
        readFromTekstFile(info, fileName, n);
    }
    else if(task == 1)
    {
        readFromBinaryFile(info, fileName, n);
    }
}



//функция добавления информации в массив структур
void addChild (struct child **info, int* n)
{
    *info = (struct child *)realloc(*info, (++(*n)) * sizeof(struct child));
    printf("Введите фамилию ");
    inputString((*info + *n - 1)->sureName);
    printf("Введите имя ");
    inputString((*info + *n - 1)->firstName);
    printf("Введите возраст ребенка ");
    inputInt(&(*info + *n - 1)->age, 0, 9);
    printf("Ребенок находился в больнице?");
    printf("\n1 - Да");
    printf("\n0 - Нет\n");
    inputInt(&((*info + *n - 1)->flag), 0, 1);
    printf("Введите болезнь ребенка ");
    inputString((*info + *n - 1)->information[0].disease);
    printf("Введите фамилию участкового врача ");
    inputString((*info + *n - 1)->information[1].familyDoctor);
    if ((*info + *n - 1)->flag)
    {
        printf("Введите адрес больницы ");
        inputString((*info + *n - 1)->information[2].address);
        printf("Введите номер больницы ");
        inputInt(&((*info + *n - 1)->information[3]).campusNumber, 1, 9);
        printf("Введите фамилию лечащего врача ");
        inputString((*info + *n - 1)->information[4].hospitalDoctor);
    }
}



//функция удаления ребенка из списка
void deleteChild (struct child **info, int *n, int i)
{
    for(int j = i; j < ((*n) - 1); j++)
    {
        *(info + j) = *(info + j + 1);
    }
    *info = (struct child*)realloc(*info, (--(*n)) * sizeof(struct child));

}



//функция поиска людей с определенной болезнью и запись их в новую структуру
void findDisease (struct child *info, struct child **sortInfo, int n, int* size, char* disease)
{
    int i = 0;
    *sortInfo = (struct child*)calloc(1,sizeof(struct child));
    for(int j = 0; j < n; j++)
    {
        if (strcmp(disease, (info + j)->information[0].disease) == 0)
        {
            *((*sortInfo) + i) = *(info + j);
            *sortInfo = (struct child*)realloc(*sortInfo, (++(*size)) * sizeof(struct child));
            i++;
        }
    }
    *sortInfo = (struct child*)realloc(*sortInfo, (--(*size)) * sizeof(struct child));
}



//функция записи массива структур в бинарный файл
void writeInBinaryFile (struct child *info, int n, const char* name)
{
    FILE *file;
    file = fopen (name, "wb");
    if(file == NULL)
    {
        printf("\nОшибка открытия бинарного файла");
    }
    for(int i = 0; i < n; i++)
    {
        fwrite(&(*(info + i)), sizeof(struct child), 1, file);
    }
    fclose(file);

}



//функция записи массива структур в текстовый файл
void writeInTekstFile (struct child *info, int n, const char* name)
{
    FILE* file;
    file = fopen (name, "wt");
    if(file == NULL)
    {
        printf("\nОшибка открытия текстового файла");
    }
    fprintf(file, "%d\n", n);
    for(int i = 0; i < n; i++)
    {
        fprintf(file, "%s %s %d %d ", (info + i)->sureName, (info + i)->firstName, (info + i)->age, (info + i)->flag);
        fprintf(file, "%s %s ", (info + i)->information[0].disease, (info + i)->information[1].familyDoctor);
        if((info + i)->flag)
        {
            fprintf(file, "%s %d %s\n", (info + i)->information[2].address, (info + i)->information[3].campusNumber, (info + i)->information[4].hospitalDoctor);
        }
        else
            fprintf(file, "\n");
    }
    fclose(file);
}



//функция чтения информации из текстового файла
void readFromTekstFile (struct child **info, const char* name, int* n)
{
    FILE *file;
    file = fopen(name, "rt");
    if (file == NULL)
    {
        printf("\nОшибка чтения данных из текстового файла");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", n);
    *info = (struct child*)calloc(*n, sizeof(struct child));
    for(int i = 0; i < *n; i++)
    {
        fscanf(file, "%s %s %d %d ", (*info + i)->sureName, (*info + i)->firstName, &(*info + i)->age, &(*info + i)->flag);
        fscanf(file, "%s %s ", (*info + i)->information[0].disease, (*info + i)->information[1].familyDoctor);
        if((*info + i)->flag)
        {
            fscanf(file, "%s %d %s\n", (*info + i)->information[2].address, &(*info + i)->information[3].campusNumber, (*info + i)->information[4].hospitalDoctor);
        }
    }
    fclose(file);
}



//функция чтения информации из бинарного файла
void readFromBinaryFile (struct child **info, const char* name, int* n)
{
    int i = 0;
    FILE *file;
    file = fopen(name, "rb");
    if (file == NULL)
    {
        printf("\nОшибка чтения данных из бинарного файла");
        exit(EXIT_FAILURE);
    }
    *info = (struct child *)malloc(sizeof(struct child));
    while(fread((*info + i++), sizeof(struct child), 1, file) == 1)
    {
        *info = (struct child *)realloc(*info, ((++(*n))) * sizeof(struct child));
    }
    *info = (struct child *)realloc(*info, ((--(*n))) * sizeof(struct child));
    fclose(file);
}



//функция вывода массива структур в виде динамической таблицы
void outputStruct(struct child* info, int n) {
    system("clear");
    int maxSureName = 8, maxFirstName = 4, maxDisease = 7, maxFamilyDoctor = 12, maxAddress = 7, maxDoctor = 14;
    for (int i = 0; i < n; i++) {
        if (strlen((info + i)->sureName) > maxSureName)
            maxSureName = strlen((info + i)->sureName);
        if (strlen((info + i)->firstName) > maxFirstName)
            maxFirstName = strlen((info + i)->firstName);
        if (strlen((info + i)->information[0].disease) > maxDisease)
            maxDisease = strlen((info + i)->information[0].disease);
        if (strlen((info + i)->information[1].familyDoctor) > maxFamilyDoctor)
            maxFamilyDoctor = strlen((info + i)->information[1].familyDoctor);

        if ((info + i)->flag) {
            if (strlen((info + i)->information[2].address) > maxAddress)
                maxAddress = strlen((info + i)->information[2].address);
            if (strlen((info + i)->information[4].hospitalDoctor) > maxDoctor)
                maxDoctor = strlen((info + i)->information[4].hospitalDoctor);
        }
        ;
    }               //определение максимальных слов в каждом столбце
    printf("\n");
    for(int i = 0; i < (maxSureName + maxFirstName + maxDisease + maxFamilyDoctor + maxAddress + maxDoctor + 71); i++)
        printf("_");
    printf("\n|   ");
    printf("\033[1;32m\033[1mSureName\033[0m");
    for (int i = 8; i < maxSureName; i++)
        printf(" ");
    printf("   |   ");
    printf("\033[1;32m\033[1mName\033[0m");
    for (int i = 4; i < maxFirstName; i++)
        printf(" ");
    printf("   |   ");
    printf("\033[1;32m\033[1mAge\033[0m");
    printf("   |   ");
    printf("\033[1;32m\033[1mDisease\033[0m");
    for (int i = 7; i < maxDisease ; i++)
        printf(" ");
    printf("   |   ");
    printf("\033[1;32m\033[1mSchoolDoctor\033[0m");
    for (int i = 12; i < maxFamilyDoctor; i++)
        printf(" ");
    printf("   |   ");
    printf("\033[1;32m\033[1mAddress\033[0m");
    for (int i = 7; i < maxAddress; i++)
        printf(" ");
    printf("   |   ");
    printf("\033[1;32m\033[1mHospitalNum\033[0m");
    printf("   |   ");
    printf("\033[1;32m\033[1mHospitalDoctor\033[0m");
    for (int i = 14; i < maxDoctor; i++)
        printf(" ");
    printf("   |");
    for (int j = 0; j < n; j++) {
        printf("\n");
        for(int i = 0; i < (maxSureName + maxFirstName + maxDisease + maxFamilyDoctor + maxAddress + maxDoctor + 71); i++)
            printf("_");
        printf("\n");
        printf("|   %s   ", (info + j)->sureName);
        for (int i = strlen((info + j)->sureName); i < maxSureName; i++)
            printf(" ");
        printf("|   %s   ", (info + j)->firstName);
        for (int i = strlen((info + j)->firstName); i < maxFirstName; i++)
            printf(" ");
        printf("|    %d    ", (info + j)->age);
        printf("|   %s   ", (info + j)->information[0].disease);
        for (int i = strlen((info + j)->information[0].disease); i < maxDisease; i++)
            printf(" ");
        printf("|   %s   ", (info + j)->information[1].familyDoctor);
        for (int i = strlen((info + j)->information[1].familyDoctor); i < maxFamilyDoctor; i++)
            printf(" ");
        if((info+j)->flag)
        {
            printf("|   %s   ", (info + j)->information[2].address);
            for (int i = strlen((info + j)->information[2].address); i < maxAddress; i++)
                printf(" ");
            printf("|        %d        ", (info + j)->information[3].campusNumber);
            printf("|   %s   ", (info + j)->information[4].hospitalDoctor);
            for (int i = strlen((info + j)->information[4].hospitalDoctor); i < maxDoctor; i++)
                printf(" ");
            printf("|");
        }
        else
        {
            printf("|   %s   ", (info + j)->information[2].address);
            for (int i = strlen((info + j)->information[2].address); i < maxAddress; i++)
                printf(" ");
            printf("|                 ");
            printf("|   %s   ", (info + j)->information[4].hospitalDoctor);
            for (int i = strlen((info + j)->information[4].hospitalDoctor); i < maxDoctor; i++)
                printf(" ");
            printf("|");
        }
    }                  //вывод основной информации в каждую ячейку

    printf("\n");
    for(int i = 0; i < (maxSureName + maxFirstName + maxDisease + maxFamilyDoctor + maxAddress + maxDoctor + 71); i++)
        printf("_");
}



//функция ввода строки
void inputString(char* str)
{
    int i = 0;
    fgets(str, 30, stdin);
    while (str[i] != '\n')
        i++;
    str[i] = '\0';
}



//функция для выбора задачи
void choiseTask (char **task,  enum choice *doTask, const char* tasks[], bool *taskIsFound)
{
    printf("\nВыберите действие:\n");
    printf("'input' - ввод данных с клавиатуры\n");
    printf("'read' - использовать готовые данные из файла\n");
    printf("'add' - добавить данные в структуру\n");
    printf("'delete' - удалить данные из структуры\n");
    printf("'look' - найти людей с определенной болезнью\n");
    printf("'write' - сохранить данные в  файл\n");
    printf("'finish' - завершить программу\n");
    inputStr(task);
    for(*doTask = input ; *doTask < finish; (*doTask)++)
    {
        if(strcmp(*task, tasks[*doTask]) == 0)
        {
            *taskIsFound = true;
            break;
        }
    }
}



//функция очистки памяти
void freeMemory (struct child *x, struct child *y, char* a, char* b, char* c)
{
    free(x);
    free(y);
    free(a);
    free(b);
    free(c);
}


