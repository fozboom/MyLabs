#pragma once
#ifndef MYPROJECTS_HEADERUNION2_H
#define MYPROJECTS_HEADERUNION2_H

#endif //MYPROJECTS_HEADERUNION2_H

#define SIZE 30
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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

enum choice {input, read, add, delete, look,  write, finish};




void inputString (char* str);
void inputStruct (struct child **info, int *n);
void readInformation (struct child **info, int*n);
void outputStruct(struct child* info, int n);
void quickSorting(struct child *info, int first, int last, int (*function)(struct child* info, int i, int j));
int comparatorSurnames (struct child *info, int i, int j);
void writeInBinaryFile (struct child *info, int n, const char* name);
void readFromBinaryFile (struct child **info, const char* name, int* n);
void findDisease (struct child *info, struct child **sortInfo, int n, int* size, char* disease);
void addChild (struct child **info, int* n);
void choiseTask (char **task,  enum choice *doTask, const char* tasks[], bool *taskIsFound);
void freeMemory (struct child *x, struct child *y, char* a, char* b, char* c);
void deleteChild (struct child **info, int *n, int i);

void writeInTekstFile (struct child *info, int n, const char* name);
void readFromTekstFile (struct child **info, const char* name, int* n);
void inputWithFile(struct child * info, int n, const char* fileName);
void readWithFile(struct child **info, int *n, const char* fileName);
