#ifndef MYPROJECTS_HEADERUNION2_H
#define MYPROJECTS_HEADERUNION2_H

#endif //MYPROJECTS_HEADERUNION2_H

#define SIZE 30

#include <stdio.h>
#include <string.h>
#include <stdlib.h>





union health {
    char disease[SIZE];
    char familyDoctor[SIZE];
    int campusNumber;
    char address[SIZE];
    char hospitalDoctor[SIZE];
};

struct child {
    char sureName[SIZE];
    char firstName[SIZE];
    int flag;
    union health information[5];
};




void inputStr (char* str);
void inputStruct (struct child **info, int *n);
void readInformation (struct child **info, int*n);
void outputStr(struct child* info, int n);
void quickSort(struct child *info, int first, int last);
void sortirovka (struct child *info, int n);