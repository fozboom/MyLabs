#include "headerSystems.h"
#include "../myLibrary.h"

int main() {
    char* num = NULL;                   //num - исходное выражение, system1, system2 - системы счисления, decimal - значение в десятичной
    int system1, system2, decimal = 0;

    printf("Введите число: ");
    inputStr(&num);

    printf("Введите систему счисления, в которой записано число: ");
    inputInt(&system1, 2, 16);

    printf("Введите систему счисления, в которую надо перевести  число: ");
    inputInt(&system2, 2, 16);

    convertToDecimal(num, strlen(num), &decimal, system1);          //перевод в десятичную
    //printf("\n%d", decimal);
    num = convertFromDecimal(decimal, system2);                                  //перевод в систему system2
    outputString(num);

    return 0;
}