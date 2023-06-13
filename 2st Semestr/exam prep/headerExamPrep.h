#ifndef MYLABS_HEADEREXAMPREP_H
#define MYLABS_HEADEREXAMPREP_H

#endif //MYLABS_HEADEREXAMPREP_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct FILO{
    int data;
    struct FILO * next;
};
void pushFILO (struct FILO ** head, int info, int * n);
void popFILO (struct FILO ** head, int * n);
void input2FILO (struct FILO ** head1, struct FILO ** head2, int * n1, int * n2, int max1, int max2);



struct FIFO{
    int data;
    struct FIFO * next;
};

void pushFIFO (struct FIFO ** head, struct FIFO ** tail, int * n, int info);
void popFIFO (struct FIFO ** head, struct FIFO ** tail, int * n, int * info);
void taskFIFO (struct FIFO ** head, struct FIFO ** tail, int * n, int max);




struct FIFO2{
    int data;
    struct FIFO2 * next;
    struct FIFO2 * prev;
};

void pushFIFO2 (struct FIFO2 ** head, struct FIFO2 ** tail, int info);
void popFIFO2 (struct FIFO2 ** head, struct FIFO ** tail, int * info);
void sortFIFO2 (struct FIFO2 ** head, struct FIFO2 ** tail);



struct Deq{
    int data;
    struct Deq * next;
    struct Deq * prev;
};
