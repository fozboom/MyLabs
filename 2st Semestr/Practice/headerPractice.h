#ifndef MYLABS_HEADERPRACTICE_H
#define MYLABS_HEADERPRACTICE_H

#endif //MYLABS_HEADERPRACTICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 6
#define N 21

struct dataCode{
    char fileName[N];
    long e;
    long d;
    long n;
    bool flag;
    char box2[SIZE][SIZE];
    char box3[SIZE][SIZE];
};


enum choiceCommand {input, createKey, read, encoding, decoding, save, finish};

long isPrimes (long x);
void createPrime (long *x);
void createNumbers (long *p, long *q, long *n, long *fi);
void createEilerNumber (long *e, long fi);
void search_d (long *d, long e, long fi);
long power (long x, long n);
long NOD (long x, long y);

long powerMod(long x, long y, long n);
long* coding (char* mas, long e, long n);
//char* decoding (long* cods, long d, long n, int size);

void textRSA(long* code, long size, long d, long n);



void writeBox (char **box, int n);
void outputBox (char** box, int n);
void readInfo (char** box, int n, const char* name);
void createBoxes (char*** box1, char*** box2, char*** box3, char*** box4, int n);
void mainTask (char** box1, char** box2, char** box3, char** box4, int n, char* s1, char* s2);
int checkLetter (char s);
void pushRandom (char** box, char s, int i, int j);
void searchLetterIndex (char **box, int *i, int* j, int n, char s);
char* codingSquare (char** box1, char** box2, char** box3, char** box4, char *mas);
//void decodeSquare (char** box1, char** box2, char** box3, char** box4, char* mas);


void choiceTask (enum choiceCommand *doTask, const char* tasks[], bool *taskIsFound);

struct dataCode createKeyCoding (char **box2, char **box3);
void encodingText (char** text, int n, struct dataCode key);