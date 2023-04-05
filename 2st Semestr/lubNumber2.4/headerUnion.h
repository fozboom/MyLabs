#ifndef MYPROJECTS_HEADERUNION_H
#define MYPROJECTS_HEADERUNION_H

#endif //MYPROJECTS_HEADERUNION_H

#define SIZE 30

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct kindergarten_info {
    char disease[SIZE];
    char familyDoctor[SIZE];
};

struct hospital_info {
    struct kindergarten_info child;
    int campusNumber;
    char address[SIZE];
    char hospitalDoctor[SIZE];
};

union health {
    struct kindergarten_info child;
    struct hospital_info hospital;
};

struct child{
    char sureName[SIZE];
    char firstName[SIZE];
    int flag;
    union health information;
};

void inputStr (char* str);
void inputStruct (struct child **info, int *n);
void readInformation (struct child **info, int*n);
void outputStr(struct child* info, int n);
void quickSort(struct child *info, int first, int last);å
void sortirovka (struct child *info, int n);