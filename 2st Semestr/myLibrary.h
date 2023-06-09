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
void output2DNumbers (long** mas, long n);
void inputInt (int* x, int a, int b);                                       //функция ввода числа с проверкой
void inputNumberMas (int** mas, int n);                                     //функция заполнения массива целых чисел
void input2DString (char*** text, long* n);
void readIn2DString (char*** text, long* n);
void deleteSymbolN (char** str);
void inputLong (long* x, int a, int b);
int proverka (char* mas);
void output2DString (char** mas, int n);


