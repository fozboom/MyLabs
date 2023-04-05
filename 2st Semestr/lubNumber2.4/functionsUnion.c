#include "headerUnion.h"

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
    int flag;
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
        if ((*info + i)->flag)
        {
            printf("Введите болезнь ребенка ");
            inputStr((*info + i)->information.hospital.child.disease);
            printf("Введите фамилию участкового врача ");
            inputStr((*info + i)->information.hospital.child.familyDoctor);
            printf("Введите адрес больницы ");
            inputStr((*info + i)->information.hospital.address);
            printf("Введите номер больницы ");
            scanf("%d", &((*info + i)->information.hospital.campusNumber));
            rewind(stdin);
            printf("Введите фамилию лечащего врача ");
            inputStr((*info + i)->information.hospital.hospitalDoctor);
        }
        else
        {
            printf("Введите болезнь ребенка ");
            inputStr((*info + i)->information.child.disease);
            printf("Введите фамилию участкового врача ");
            inputStr((*info + i)->information.child.familyDoctor);
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

        if ((info + i)->flag) {
            if (strlen((info + i)->information.hospital.child.disease) > maxDisease)
                maxDisease = strlen((info + i)->information.hospital.child.disease);
            if (strlen((info + i)->information.hospital.child.familyDoctor) > maxFamilyDoctor)
                maxFamilyDoctor = strlen((info + i)->information.hospital.child.familyDoctor);
            if (strlen((info + i)->information.hospital.address) > maxAddress)
                maxAddress = strlen((info + i)->information.hospital.address);
            if (strlen((info + i)->information.hospital.hospitalDoctor) > maxDoctor)
                maxDoctor = strlen((info + i)->information.hospital.hospitalDoctor);
        } else {
            if (strlen((info + i)->information.child.disease) > maxDisease)
                maxDisease = strlen((info + i)->information.child.disease);
            if (strlen((info + i)->information.child.familyDoctor) > maxFamilyDoctor)
                maxFamilyDoctor = strlen((info + i)->information.child.familyDoctor);
        }
    }


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

        if ((info + j)->flag)
        {
            printf("|   %s   ", (info + j)->information.hospital.child.disease);
            for (int i = strlen((info + j)->information.hospital.child.disease); i < maxDisease; i++)
                printf(" ");
            printf("|   %s   ", (info + j)->information.hospital.child.familyDoctor);
            for (int i = strlen((info + j)->information.hospital.child.familyDoctor); i < maxFamilyDoctor; i++)
                printf(" ");
            printf("|   %s   ", (info + j)->information.hospital.address);
            for (int i = strlen((info + j)->information.hospital.address); i < maxAddress; i++)
                printf(" ");
            printf("|   %s   ", (info + j)->information.hospital.hospitalDoctor);
            for (int i = strlen((info + j)->information.hospital.hospitalDoctor); i < maxDoctor; i++)
                printf(" ");
            printf("|");
        }
        else {
            printf("|   %s   ", (info + j)->information.child.disease);
            for (int i = strlen((info + j)->information.child.disease); i < maxDisease; i++)
                printf(" ");
            printf("|   %s   ", (info + j)->information.child.familyDoctor);
            for (int i = strlen((info + j)->information.child.familyDoctor); i < maxFamilyDoctor; i++)
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




void sortirovka (struct child *info, int n)
{
    for(int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++)
        {
            if (strcmp((info + j)->sureName, (info + j + 1)->sureName) > 0)
            {
                struct child tmp = *(info + j);
                *(info + j) = *(info + j + 1);
                *(info + j + 1) = tmp;
            }

        }
    }
}


void quickSort(struct child *info, int first, int last)
{
    if(first < last) {
        int left = first, right = last, middle = (left + right) / 2;
        do {
            while (strcmp((info + left)->sureName, (info + middle)->sureName) < 0)
                left++;
            while (strcmp((info + right)->sureName, (info + middle)->sureName) > 0)
                right--;
            if (left <= right) {
                struct child tmp = *(info + left);
                *(info + left) = *(info + right);
                *(info + right) = tmp;
                left++;
                right--;
            }
        } while (left <= right);
        quickSort(info, first, right);
        quickSort(info, left, last);
    }
}


void readInformation (struct child **info, int*n)
{
    FILE *file;
    file = fopen("information.txt", "r");
    if(file == NULL)
    {
        printf("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    fscanf(file, "%d", n);
    *info = (struct child *)calloc((*n), sizeof(struct child));
    for(int i = 0; i < *n; i++)
    {
        fscanf(file, "%d", &((*info + i)->flag));
        fscanf(file, "%s", &((*info + i)->sureName));
        fscanf(file, "%s", &((*info + i)->firstName));
        if((*info + i)->flag)
        {
            fscanf(file, "%s", &((*info + i)->information.hospital.child.disease));
            fscanf(file, "%s", &((*info + i)->information.hospital.child.familyDoctor));
            fscanf(file, "%s", &((*info + i)->information.hospital.address));
            fscanf(file, "%d", &((*info + i)->information.hospital.campusNumber));
            fscanf(file, "%s", &((*info + i)->information.hospital.hospitalDoctor));
        }
        else
        {
            fscanf(file, "%s", &((*info + i)->information.child.disease));
            fscanf(file, "%s", &((*info + i)->information.child.familyDoctor));
        }
    }
}
