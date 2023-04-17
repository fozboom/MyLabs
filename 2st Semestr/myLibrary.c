#include "myLibrary.h"

//функция вывода строки
void outputString(char* mas)
{
    printf("\n");
    for(int i = 0; mas[i] != '\0'; i++)
        printf("%c", mas[i]);
    printf("\n");
}



//функция вывода массива чисел
void outputMasNumbers (long* mas, long n)
{
    for(int i = 0; i < n; i++)
        printf("%ld ", mas[i]);
}



//функция ввода числа с првоеркой
void inputInt (int* x, int a, int b)
{
    while(!scanf("%d", x) || (((*x) < a) || ((*x) > b)))
    {
        rewind(stdin);
        printf("\nОшибка ввода числа, попробуйте еще раз: ");
    }
    rewind(stdin);
}



//функция ввода строки произвольной длины
void inputStr (char** mas)
{
    int n = 1, i = 0;                                                //n - длина строки, i - параметр цикла
    char s;
    *mas = (char*)calloc(n, sizeof(char));          //выделение памяти на один элемент
    while ((s = getchar()) != '\n')
    {
        *(*mas + i) = s;                                                 //запись символа в строку
        *mas = (char*)realloc(*mas,(++n) * sizeof(char));    //перевыделение памяти
        i++;
    }
    *(*mas + i) = '\0';                                                  //запись нуль-терминатора
}
