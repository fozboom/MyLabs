#pragma once
#ifndef MYLABS_HEADERRING_H
#define MYLABS_HEADERRING_H

#endif //MYLABS_HEADERRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 21

struct Ring
{
    char name[SIZE];
    struct Ring *next;
    struct Ring *prev;
};

enum commands {mergeRings, sortRing, counting, save, finish};

void pushAfter (struct Ring **p, char* newName);                                //функция добавления элемента после точки входа
void deleteCurrent (struct Ring **p);                                           //функция удаления текущего элемента
void connectRingElements(struct Ring* , struct Ring* );                         //функция для связывания элементов кольца
void appendRemainingElements(struct Ring* , struct Ring** , struct Ring** );    //функция для объединения оставшихся элементов

struct Ring* mergeRingsInOne(struct Ring* p1, struct Ring* p2);                 //функция слияния двух отсортированных колец в одно
struct Ring* sortingRing(struct Ring *p);                                       //функция сортировки кольца
void countingHumans (struct Ring **p);                                          //функция игры 'считалочка'

void saveToFile(struct Ring* p, char* filename, int format);                    //функция сохранения кольца в файл
struct Ring* readFromFile(char* filename, int format);                          //функция чтения кольца из файла

void deleteName (struct Ring **p);                                              //функция удаления определенного имени из файла
void printRing (struct Ring *p);                                                //функция вывода кольца на экран
void inputRing (struct Ring **p);                                               //функция ввода элементов кольца с клавиатуры
void choiceTask (enum commands* , const char* tasks[] , bool* );                //функция для выбора задачи
int ifLetter (char s);                                                          //функция для проверки символа на букву
void freeRing(struct Ring *p1, struct Ring *p2, struct Ring *newRing);          //функция очистки памяти

void howToInput (int* input, int* format, struct Ring **tmp);                   //функция для запроса у пользователя, как инициализировать кольцо
void howToSave (int* format, struct Ring *tmp);                                 //функция для запроса у пользователя, как сохранить кольцо
void doYouWantToDelete (struct Ring **p);                                       //функция для запроса, хочет ли пользователь удалить элемент кольца
void caseMergeRings (int*, int*, struct Ring**, struct Ring**, struct Ring**);  //функция для вызова функций, чтобы объединить кольца
void caseSortRing (int*, int*, struct Ring**, struct Ring**);                   //функция для вызова функций, чтобы отсортировать кольцо
void caseCounting (int* input, int* format, struct Ring **newRing);             //функция для вызова функций, чтобы сыграть в 'считалочку'





