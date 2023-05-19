#pragma once
#ifndef MYLABS_HEADERRING_H
#define MYLABS_HEADERRING_H

#endif //MYLABS_HEADERRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 21

struct Ring
{
    char name[SIZE];
    struct Ring *next;
    struct Ring *prev;
};

enum commands {mergeRings, sortRing, counting, save, finish};

void inputRing (struct Ring **p);
struct Ring* sortingRing(struct Ring *p);
struct Ring* mergeRingsInOne (struct Ring *p1, struct Ring *p2);
void inputRing (struct Ring **p);
void printRing (struct Ring *p);
int ifLetter (char s);
void countingHumans (struct Ring **p);
void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound);
void freeRing(struct Ring *p1, struct Ring *p2, struct Ring *newRing);
void saveToFile(struct Ring* p, char* filename, int format);
struct Ring* readFromFile(char* filename, int format);
void howToInput (int* input, int* format, struct Ring **tmp);
void howToSave (int* input, int* format, struct Ring *tmp);
void caseMergeRings (int* input, int* format, struct Ring **p1, struct Ring **p2, struct Ring **newRing);
void caseSortRing (int* input, int* format, struct Ring **p1, struct Ring **p2, struct Ring **newRing);
void caseCounting (int* input, int* format, struct Ring **newRing);
void deleteName (struct Ring **p);
void doYouWantToDelete (struct Ring **p);