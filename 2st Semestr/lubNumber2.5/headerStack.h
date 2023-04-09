#ifndef MYPROJECTS_HEADERSTACK_H
#define MYPROJECTS_HEADERSTACK_H

#endif //MYPROJECTS_HEADERSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

union hold{
    int number;
    char symbol;
};

struct FILO
{
    union hold data;
    struct FILO *next;
};

char* inputStr ();
void printStack (struct FILO *head);
void push (struct FILO **head, union hold info);
union hold popStruct (struct FILO **head);
int ifNumber (char s);
int ifOperator (char s);
int poiskNumber (char* mas, int* i);
int preoritet (char s);
void repeatProgram(int *end);

int taskBrackets (char* mas);
char* writeToPolish(char *mas);
void calculateMath (char* mas);