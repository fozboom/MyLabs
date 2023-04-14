#ifndef MYPROJECTS_HEADERUNION2_H
#define MYPROJECTS_HEADERUNION2_H

#endif //MYPROJECTS_HEADERUNION2_H

#define SIZE 30
#include "../myLibrary.h"
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
    int age;
    union health information[5];
};




void inputString (char* str);
void inputStruct (struct child **info, int *n);
void readInformation (struct child **info, int*n);
void outputStruct(struct child* info, int n);
void quickSorting(struct child *info, int first, int last, int (*function)(struct child* info, int i, int j));
int comparatorSurnames (struct child *info, int i, int j);
void writeInBinaryFile (struct child *info, int n, const char* name);
void readFromBinaryFile (struct child **info, const char* name, int* n);
