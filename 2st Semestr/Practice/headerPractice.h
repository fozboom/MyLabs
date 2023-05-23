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
#define MAX_LENGTH 80

struct dataCode{
    char fileName[N];
    long e;
    long d;
    long n;
    int flag;
    char box2[SIZE][SIZE];
    char box3[SIZE][SIZE];
};


enum choiceCommand {input, read, encoding, decoding, save, finish};

long isPrimes (long x);
void createPrime (long *x);
void createNumbers (long *p, long *q, long *n, long *fi);
void createEilerNumber (long *e, long fi);
void search_d (long *d, long e, long fi);
long power (long x, long n);
long NOD (long x, long y);

long powerMod(long x, long y, long n);
long** coding (char** mas, long e, long n, long rows);
char** decodingRSA(long** codeText, long d, long n, long rows);

void textRSA(long* code, long size, long d, long n);



void writeBox (char box[SIZE][SIZE], int n);
void outputBox (char** box, int n);
void readInfo (char box[SIZE][SIZE], int n, const char* name);
void mainTask (char** box1, char** box2, char** box3, char** box4, int n, char* s1, char* s2);
int checkLetter (char s);
void pushRandom (char box[SIZE][SIZE], char s, int i, int j);
void searchLetterIndex (char box[SIZE][SIZE], int *i, int* j, int n, char s);
char** codingSquare (char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char **text, int size);
char** decodeSquare(char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char** text, long rows);


void choiceTask (enum choiceCommand *doTask, const char* tasks[], bool *taskIsFound);

struct dataCode createKeyCoding (char box2[SIZE][SIZE], char box3[SIZE][SIZE]);
struct dataCode encodingText (char** text, int n, long ***codeText, char ***newText);

void saveStructInfo (struct dataCode* key, long count);
void readStructInfo(struct dataCode** key, long* count);
char** decodingTextFromFile(long** codeText, char** newText, struct dataCode* keys, int count, char box[SIZE][SIZE], long* rows);
void saveNumberToFile(long** code, long rows, char* fileName);
void saveTextToFile(char** text, long rows, char* fileName);
struct dataCode saveEncodingInfo (char** newText, long** code, long rows, struct dataCode key);

void caseEncoding (struct dataCode **keys, long *countKeys, long*** codeText, char** text, int n, char*** newText);
long** myAtoi2DText(char** text, int rows);


void createKeyRSA (long *p, long* q, long*n, long* fi, long* e, long* d);
void decodingInputText ();
void caseDecoding (char ***text, long **codeText, char **newText, struct dataCode *keys, long countKeys, char box1[SIZE][SIZE], long *rows);