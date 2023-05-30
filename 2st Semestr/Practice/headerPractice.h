#ifndef MYLABS_HEADERPRACTICE_H
#define MYLABS_HEADERPRACTICE_H

#endif //MYLABS_HEADERPRACTICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define SIZE 6                  //SIZE - размеры квадратов для шифрования шифром четырех квадратов
#define N 21                    //N - длина имени файла
#define MAX_LENGTH 80           //MAX_LENGTH - максимальная длина строки

struct dataCode{
    char fileName[N];           //имя зашифрованного файла
    long e;                     //открытая экспонента для шифрования алгоритмом RSA
    long d;                     //закрытая экспонента для дешифрования
    long n;                     //часть открытого и закрытого ключа в алгоритме RSA
    int flag;                   //флажок для определения, каким алгоритмом зашифрован файл
    char box2[SIZE][SIZE];      //ключ для шифрования шифром четырех квадратов
    char box3[SIZE][SIZE];      //ключ для шифрования шифром четырех квадратов
};


enum choiceCommand {input, read, encoding, decoding, save, finish};

//////////////////////////////////////////////////////функции для шифрования алгоритмом RSA/////////////////////////////

//функция проверки числа на простоту
long isPrimes (long x);
//функция создания простого числа
void createPrime (long *x);
//функция создания чисел p, q, n, fi
void createNumbers (long *p, long *q, long *n, long *fi);
//функция создания числа e - части открытого ключа
void createEilerNumber (long *e, long fi);
//функция нахождения НОД алгоритмом Евклида
long NOD (long x, long y);
//расширенный алгоритм Евклида для нахождения обратного по модулю числа
void search_d(long* x, long e, long fi);
//функция бинарного возведения в степень по модулю
long powerMod(long x, long y, long n);
//функция кодирования текста алгоритмом RSA
long** coding (char** mas, long e, long n, long rows);
//функция декодирования текста алгоритмом RSA
char** decodingRSA(long** codeText, long d, long n, long rows);

//////////////////////////////////////////////////////функции для шифрования алгоритмом четырех квадратов///////////////

//функция для создания квадрата
void writeBox(char box[SIZE][SIZE], int n);
//функция вывода шифра для шифра четырех квадратов
void outputBox (char box[SIZE][SIZE]);
//кодирование текста алгоритмом четырех квадратов
char** codingSquare(char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char **text, int size);
//функция декодирования текста алгоритмом четырех квадратов
char** decodeSquare(char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char** text, long rows);
//функция проверки, является ли символ буквой
int checkLetter (char s);
//функция проверки текста на возможность шифрования алгоритмом четырех квадратов
int checkTextForSquare (char** text, long rows);
//функция вставки элемента в случайную позицию
void pushRandom(char box[SIZE][SIZE], char s, int i, int j);
//функция поиска индексов символа в квадрате
void searchLetterIndex (char box[SIZE][SIZE], int *i, int* j, int n, char s);
//функция выбора команды
void choiceTask (enum choiceCommand *doTask, const char* tasks[], bool *taskIsFound);


//////////////////////////////////////////Основные функции вызов функций для кодирования и декодирования////////////////

//функция чтения квадрата из файла
void readInfo(char box[SIZE][SIZE], int n, const char* name);
//основная функция для кодирования текста
struct dataCode encodingText (char** text, int n, long ***codeText, char ***newText);
//декодирование текста из файла
char** decodingTextFromFile(long** codeText, char** newText, struct dataCode* keys, int count, char box[SIZE][SIZE], long* rows);
//функция декодирования текста, введенного с клавиатуры
char** decodingInputText(char box[SIZE][SIZE], long* rows);

///////////////////////////////////////////////////////Функции работы с файлами/////////////////////////////////////////

//функция сохранения массива структур с данными о зашифрованных файлах в бинарный файл
void saveStructInfo (struct dataCode* key, long count);
//функция чтения массива структур с данными о зашифрованных файлах
void readStructInfo(struct dataCode** key, long* count);
//функция сохранения двумерного массива чисел в файл
void saveNumberToFile(long** code, long rows, char* fileName);
//функция чтение зашифрованного текста RSA из файла
long** loadNumberFromFile(long** code, long* rows, char* fileName);
//функция сохранения текста в файл
void saveTextToFile(char** text, long rows, char* fileName);
//функция считывания текста в двумерный массив из файла
char** loadTextFromFile(long* rows, char* fileName);
//функция перевода двумерного массива чисел в массив строк
long** myAtoi2DText(char** text, long rows);
//функция для кодирования текста

////////////////////////Вспомогательные функции которые вызывают другие функции/////////////////////////////////////////

void caseEncoding (struct dataCode **keys, long *countKeys, long*** codeText, char** text, int n, char*** newText);
//функция для декодирования текста
void caseDecoding (char ***text, long **codeText, char **newText, struct dataCode *keys, long countKeys, long *rows);
//функция для сохранения информации в файл
void saveInformation (char** text, char** newText, long** code, long rows, struct dataCode *keys, long countKeys);
//функция чтения текста из файла
void caseReadText (char*** text, long* rows);
//функция очистки памяти
void freeMemory(char** text, char** newText, long** codeText, struct dataCode* keys, long countKeys, long n);

////////////////////////Вспомогательные функции из библиотеки///////////////////////////////////////////////////////////

//функция ввода строки произвольной длины
void inputStr (char** mas);
//функция ввода числа типа int
void inputInt (int* x, int a, int b);
//функция вода числа типа long
void inputLong (long* x, int a, int b);
//функция ввода массива строк с клавиатуры
void input2DString (char*** text, long* n);
//функция вывода двумерного массива чисел long** на экран
void output2DNumbers (long** mas, long n);
//функция вывода массива строк на экран
void output2DString (char** mas, int n);
//функция удаления символа '\n' из строки
void deleteSymbolN (char** str);