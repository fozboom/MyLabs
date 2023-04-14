#ifndef MYLABS_HEADERLECTIONS_H
#define MYLABS_HEADERLECTIONS_H

#endif //MYLABS_HEADERLECTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ring{
    char* name;
    struct Ring *next;
};

void push_after (struct Ring **p, char* str);
void pop (struct Ring **p);
void print(struct Ring* p);
