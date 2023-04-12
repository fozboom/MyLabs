#ifndef MYLABS_HEADERLECTIONS_H
#define MYLABS_HEADERLECTIONS_H

#endif //MYLABS_HEADERLECTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ring{
    int data;
    struct Ring *next;
};


struct DoubleRing{
    int data;
    struct DoubleRing *next;
    struct DoubleRing *prev;
};
