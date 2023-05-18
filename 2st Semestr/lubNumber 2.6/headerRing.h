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

enum commands {mergeRings, sortRing, counting, finish};

void inputRing (struct Ring **p);
struct Ring* sortingRing(struct Ring *p);
struct Ring* mergeRingsInOne (struct Ring *p1, struct Ring *p2);
void inputRing (struct Ring **p);
void printRing (struct Ring *p);
void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound);