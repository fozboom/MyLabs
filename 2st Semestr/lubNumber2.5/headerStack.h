#ifndef MYPROJECTS_HEADERSTACK_H
#define MYPROJECTS_HEADERSTACK_H

#endif //MYPROJECTS_HEADERSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

union hold{                                         //объединение для записи символа или числа в стек
    int number;                                     //number - число, записываемое в стек
    char symbol;                                    //symbol - символ, записываемый в стек
};

struct FILO                                         //структура стека
{
    union hold data;                                //объединение, записываемое в стек
    struct FILO *next;                              //указатель на следующий элемент
};


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