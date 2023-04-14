#include "headerUnion2.h"
#include "../myLibrary.h"

void inputString(char* str)
{
    int i = 0;
    fgets(str, 30, stdin);
    while (str[i] != '\n')
        i++;
    str[i] = '\0';
}

void inputStr (char** mas)
{
    int n = 1, i = 0;                                                //n - длина строки, i - параметр цикла
    char s;
    *mas = (char*)calloc(n, sizeof(char));          //выделение памяти на один элемент
    while ((s = getchar()) != '\n')
    {
        *(*mas + i) = s;                                                 //запись символа в строку
        *mas = (char*)realloc(*mas,(++n) * sizeof(char));    //перевыделение памяти
        i++;
    }
    *(*mas + i) = '\0';                                                  //запись нуль-терминатора
}


void inputStruct(struct child** info, int* n)
{
    int i = 0;
    *info = (struct child*)calloc(*n, sizeof(struct child));
    while (1)
    {
        printf("Введите фамилию ");
        inputString((*info + i)->sureName);
        if ((*info + i)->sureName[0] == '\0')
        {
            (*n)--;
            break;
        }
        printf("Введите имя ");
        inputString((*info + i)->firstName);
        printf("Введите возраст ребенка ");
        scanf("%d", &(*info + i)->age);  rewind(stdin);
        printf("Ребенок находился в больнице?");
        printf("\n1 - Да");
        printf("\n0 - Нет\n");
        while (!scanf("%d", &((*info + i)->flag)) || (((*info + i)->flag) != 0 && ((*info + i)->flag) != 1))
        {
            rewind(stdin);
            printf("Ошибка ввода");
        }
        rewind(stdin);
        printf("Введите болезнь ребенка ");
        inputString((*info + i)->information[0].disease);
        printf("Введите фамилию участкового врача ");
        inputString((*info + i)->information[1].familyDoctor);
        if ((*info + i)->flag)
        {
            printf("Введите адрес больницы ");
            inputString((*info + i)->information[2].address);
            printf("Введите номер больницы ");
            scanf("%d", &((*info + i)->information[3]).campusNumber);
            rewind(stdin);
            printf("Введите фамилию лечащего врача ");
            inputString((*info + i)->information[4].hospitalDoctor);
        }
        i++;
        (*n)++;
        *info = (struct child*)realloc(*info, (*n) * sizeof(struct child));
    }
}

void outputStruct(struct child* info, int n) {
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


void quickSorting(struct child *info, int first, int last, int (*function)(struct child* , int , int ))
{
    if(first < last) {
        int left = first, right = last, middle = (left + right) / 2;
        do {
            while ((*function)(info, left, middle))
                left++;
            while (!(*function)(info, right, middle))
                right--;
            if (left <= right) {
                struct child tmp = *(info + left);
                *(info + left) = *(info + right);
                *(info + right) = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quickSorting(info, first, right, function);
        quickSorting(info, left, last, function);
    }
}


int comparatorSurnames (struct child *info, int i, int j)
{
    if(strcmp((info + i)->sureName, (info + j)->sureName) < 0)
    {
        return 1;
    }
    else
        return 0;
}


void writeInBinaryFile (struct child *info, int n, const char* name)
{
    FILE *file;
    file = fopen (name, "wb");
    if(file == NULL)
    {
        printf("\nОшибка открытия бинарного файла");
    }
    for(int i = 0; i < n; i++)
        fwrite((info + i), sizeof(struct child), 1, file);

}



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
}






