#pragma once
#ifndef MYPROJECTS_HEADERUNION_H
#define MYPROJECTS_HEADERUNION_H

#endif //MYPROJECTS_HEADERUNION_H

#define SIZE 30
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

union health {
    char disease[SIZE];			        //название болезни
    char familyDoctor[SIZE];	        //фамилия участкового врача
    char address[SIZE];			        //адрес больницы
    int campusNumber;			        //номер больницы
    char hospitalDoctor[SIZE];	        //фамилия доктора в больнице
};

struct child {
    char sureName[SIZE];		        //фамилия ребенка
    char firstName[SIZE];		        //имя ребенка
    int age;					        //возраст ребенка
    int flag;					        //флажок для определения, был ли ребенок в больнице
    union health information[5];        //массив объединений
};


enum choice {input, read, add, delete, look,  write, finish};



void quickSorting(struct child *, int , int , int (*function)(struct child* info, int i, int j));   //функция быстрой сортировки с компаратором

int comparatorSurnames (struct child *info, int i, int j);                                          //компаратор для сортировки в алфавитном порядке фамилий
int comparatorNames (struct child *info, int i, int j);                                             //компаратор для сортировки в алфавитном порядке имен
int comparatorAge (struct child *info, int i, int j);                                               //компаратор для сортировки по возрасту

void writeInTekstFile (struct child *info, int n, const char* name);                                //функция записи массива структур в текстовый файл
void readFromTekstFile (struct child **info, const char* name, int* n);                             //функция чтения информации из текстового файла
void writeInBinaryFile (struct child *info, int n, const char* name);                               //функция записи массива структур в бинарный файл
void readFromBinaryFile (struct child **info, const char* name, int* n);                            //функция чтения информации из бинарного файла
void inputWithFile(struct child * info, int n, const char* fileName);                               //функция для записи информации в файл (бин. или текст.)
void readWithFile(struct child **info, int *n, const char* fileName);                               //функция чтения информации из файла (бин. или текст.)

void inputStruct (struct child **info, int *n);                                                     //функция заполнения массива структур с клавиатуры
void addChild (struct child **info, int* n);                                                        //функция добавления информации в массив структур
void deleteChild (struct child **info, int *n, int i);                                              //функция удаления ребенка из списка
void findDisease (struct child *info, struct child **sortInfo, int n, int* size, char* disease);    //функция поиска болезни и записи в новую структуру
void outputStruct(struct child* info, int n);                                                       //функция вывода массива структур в виде динамич. таблицы

void inputString (char* str);                                                                       //функция ввода строки
void choiseTask (char **task,  enum choice *doTask, const char* tasks[], bool *taskIsFound);        //функция для выбора задачи
void freeMemory (struct child *x, struct child *y, char* a, char* b, char* c);                      //функция очистки памяти

