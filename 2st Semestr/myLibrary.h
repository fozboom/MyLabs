#pragma once
#ifndef MYLABS_MYLIBRARY_H
#define MYLABS_MYLIBRARY_H

#endif //MYLABS_MYLIBRARY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void inputStr (char** mas);                                                 //функция ввода строки произвольной длины
void outputString(char* mas);                                               //функция вывода строки
void outputMasNumbers (long* mas);                                  //функция вывода массива чисел
void inputInt (int* x, int a, int b);                                       //функция ввода числа с проверкой
void inputNumberMas (int** mas, int n);                                     //функция заполнения массива целых чисел
void input2DString (char*** text, int* n);
void readIn2DString (char*** text, int* n);
void deleteSymbolN (char** str);
int proverka (char* mas);




struct tree{
    int data;
    struct tree *left;
    struct tree *right;
};
struct tree* makeNode (int a);
void printTree (struct tree *root, int n);
void addNode (struct tree *root, struct tree *newNode, int a);
