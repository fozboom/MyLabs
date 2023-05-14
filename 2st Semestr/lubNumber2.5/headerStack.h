#ifndef MYPROJECTS_HEADERSTACK_H
#define MYPROJECTS_HEADERSTACK_H

#endif //MYPROJECTS_HEADERSTACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdbool.h>

enum commands  {polish, calculate, convert, finish};

union hold{                                         //объединение для записи символа или числа в стек
    int number;                                     //number - число, записываемое в стек
    char symbol;                                    //symbol - символ, записываемый в стек
};

struct FILO                                         //структура стека
{
    union hold data;                                //объединение, записываемое в стек
    int index;
    struct FILO *next;                              //указатель на следующий элемент
};

void push (struct FILO **head, union hold info);    //функция занесения элемента в стек
union hold popStruct (struct FILO **head);          //функция удаления элемента из стека
void printStack (struct FILO *head);                //функция вывода элементов стека

int ifNumber (char s);                              //функция проверки символа на число
int ifBracket (char s);                             //функция проверки символа на скобку
int ifOperator (char s);                            //функция проверки элемента на оператор
char getBracket (char s);                           //функция получения закрывающей скобки
int poiskNumber (char* mas, int* i);                //функция поиска числа в строке
int preoritet (char s);                             //функция определения приоритета операций

void taskBrackets (char* mas);                      //функция проверки на правильности расставленных скобок
char* writeToPolish(char *mas);                     //функция записи математического выражения польской нотацией
int calculateMath (char* mas);                      //функция вычисления выражения, записанного польской нотацией
char* translateDecimal (char *num);                 //функция перевода выражения в другую систему счисления

void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound);
char* convertFromDecimal (int num, int system);     //функция перевода числа из десятичной системы в любую через стек
void checkMath (char* str);                         //функция проверки, можно ли посчитать это выражение
void freeMemory (char* str, char* newStr, char* strInNewSystem);










