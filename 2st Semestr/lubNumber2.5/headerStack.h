#ifndef MYPROJECTS_HEADERSTACK_H
#define MYPROJECTS_HEADERSTACK_H

#endif //MYPROJECTS_HEADERSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


struct FILO
{
    union hold{
        int number;
        char symbol;
    }data;
    int num;
    char symbol;
    struct Stack *next;
};

char* inputStr ();
void printStack (struct FILO *head);
void push (struct FILO **head, union hold info);
union hold popStruct (struct FILO **head);
int ifNumber (char s);
int ifOperator (char s);
int poiskNumber (char* mas, int* i);
char* writeInPolish (char* mas);
void mainTask (char* mas, struct FILO **head);
void writeToPostfix(char *mas, char *postfix);
int preoritet (char s);