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


void printStack (struct FILO *head);                //функция вывода элементов стека
void push (struct FILO **head, union hold info);    //функция занесения элемента в стек
union hold popStruct (struct FILO **head);          //функция удаления элемента из стека
int ifNumber (char s);                              //функция проверки символа на число
int ifOperator (char s);                            //функция проверки элемента на оператор
int poiskNumber (char* mas, int* i);                //функция поиска числа в строке
int preoritet (char s);                             //функция определения приоритета операций
void repeatProgram(int *end);                       //функция для зацикливания программы

int taskBrackets (char* mas);                       //функция проверки на правильности расставленных скобок
char* writeToPolish(char *mas);                     //функция записи математического выражения польской нотацией
void calculateMath (char* mas);                     //функция вычисления выражения, записанного польской нотацией