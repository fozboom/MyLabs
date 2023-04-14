#include "headerUnion2.h"

void inputStr(char* str)
{
    int i = 0;
    fgets(str, 30, stdin);
    while (str[i] != '\n')
        i++;
    str[i] = '\0';

}


void inputStruct(struct child** info, int* n)
{
    int i = 0;
    *info = (struct child*)calloc(*n, sizeof(struct child));
    while (1)
    {
        if ((*info + i) == NULL)
        {
            printf("Ошибка памяти");
            exit(EXIT_FAILURE);
        }
        printf("Введите фамилию ");
        inputStr((*info + i)->sureName);
        if ((*info + i)->sureName[0] == '\0')
        {
            (*n)--;
            break;
        }
        printf("Введите имя ");
        inputStr((*info + i)->firstName);
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
        inputStr((*info + i)->information[0].disease);
        printf("Введите фамилию участкового врача ");
        inputStr((*info + i)->information[1].familyDoctor);
        if ((*info + i)->flag)
        {
            printf("Введите адрес больницы ");
            inputStr((*info + i)->information[2].address);
            printf("Введите номер больницы ");
            scanf("%d", &((*info + i)->information[3]).campusNumber);
            rewind(stdin);
            printf("Введите фамилию лечащего врача ");
            inputStr((*info + i)->information[4].hospitalDoctor);
        }
        i++;
        (*n)++;
        *info = (struct child*)realloc(*info, (*n) * sizeof(struct child));
    }
}

void outputStr(struct child* info, int n) {
    int maxSureName = 0, maxFirstName = 0, maxDisease = 0, maxFamilyDoctor = 0, maxAddress = 0, maxDoctor = 0;
    for (int i = 0; i < n; i++) {
        if (strlen((info + i)->sureName) > maxSureName)
            maxSureName = strlen((info + i)->sureName);
        if (strlen((info + i)->firstName) > maxFirstName)
            maxFirstName = strlen((info + i)->firstName);
        if (strlen((info + i)->information[0].disease) > maxDisease)
            maxDisease = strlen((info + i)->information[1].disease);
        if (strlen((info + i)->information[1].familyDoctor) > maxFamilyDoctor)
            maxFamilyDoctor = strlen((info + i)->information[1].familyDoctor);

        if ((info + i)->flag) {
            if (strlen((info + i)->information[2].address) > maxAddress)
                maxAddress = strlen((info + i)->information[2].address);
            if (strlen((info + i)->information[4].hospitalDoctor) > maxDoctor)
                maxDoctor = strlen((info + i)->information[4].hospitalDoctor);
        }
    }

    printf("Фамилия");
    for (int i = 6; i < maxSureName + 7; i++)
        printf(" ");
    printf("Имя");
    for (int i = 2; i < maxFirstName + 7; i++)
        printf(" ");
    printf("Болезнь");
    for (int i = 6; i < maxDisease + 7; i++)
        printf(" ");
    printf("Уч. врач");
    for (int i = 7; i < maxFamilyDoctor + 7; i++)
        printf(" ");
    printf("Адрес");
    for (int i = 4; i < maxAddress + 7; i++)
        printf(" ");
    printf("Леч. врач");
    for (int i = 8; i < maxDoctor + 9; i++)
        printf(" ");
    for (int j = 0; j < n; j++) {
        printf("\n");
        for(int i = 0; i < (maxSureName + maxFirstName + maxDisease + maxFamilyDoctor + maxAddress + maxDoctor + 43); i++)
            printf("-");
        printf("\n");
        printf("|   %s   ", (info + j)->sureName);
        for (int i = strlen((info + j)->sureName); i < maxSureName; i++)
            printf(" ");
        printf("|   %s   ", (info + j)->firstName);
        for (int i = strlen((info + j)->firstName); i < maxFirstName; i++)
            printf(" ");
        printf("|   %s   ", (info + j)->information[0].disease);
        for (int i = strlen((info + j)->information[0].disease); i < maxDisease; i++)
            printf(" ");
        printf("|   %s   ", (info + j)->information[1].familyDoctor);
        for (int i = strlen((info + j)->information[1].familyDoctor); i < maxFamilyDoctor; i++)
            printf(" ");
        if ((info + j)->flag)
        {
            printf("|   %s   ", (info + j)->information[2].address);
            for (int i = strlen((info + j)->information[2].address); i < maxAddress; i++)
                printf(" ");
            printf("|   %s   ", (info + j)->information[4].hospitalDoctor);
            for (int i = strlen((info + j)->information[4].hospitalDoctor); i < maxDoctor; i++)
                printf(" ");
            printf("|");
        }
        else {
            printf("|   %s   ", (info + j)->information[2].address);
            for (int i = strlen((info + j)->information[2].address); i < maxAddress; i++)
                printf(" ");
            printf("|   %s   ", (info + j)->information[4].hospitalDoctor);
            for (int i = strlen((info + j)->information[4].hospitalDoctor); i < maxDoctor; i++)
                printf(" ");
            printf("|");
            for(int i = 0; i < (maxAddress + 6); i++)
                printf(" ");
            printf("|");
            for(int i = 0; i < (maxDoctor + 6); i++)
                printf(" ");
            printf("|");
        }
    }

    printf("\n");
    for(int i = 0; i < (maxSureName + maxFirstName + maxDisease + maxFamilyDoctor + maxAddress + maxDoctor + 43); i++)
        printf("-");
}


void quickSorting(struct child *info, int first, int last, int (*function)(struct child* info, int i, int j))
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




