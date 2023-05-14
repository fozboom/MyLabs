#include "headerSystems.h"
#include "../myLibrary.h"

void convertToDecimal (char* num, int n, int* numInDecimal, int system)
{
    int power = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        int number;
        if (ifNumber(num[i])) {
            number = num[i] - '0';                  //перевод число
        }

        else
        {
            number = (int)(num[i] - 'A' + 10);      //перевод буквы в число
        }

        *numInDecimal += number * power;            //запись цифры
        power *= system;
    }


}


char* convertFromDecimal (int num, int system)
{
    const char digits[] = "0123456789ABCDEF";                           //массив для определения буквы/цифры
    char* result = (char*)calloc(100, sizeof(char));         //результат
    int i = 0;
    while (num > 0)
    {
        int digit = num % system;                                       //берем цифру с конца
        result[i++] = digits[digit];                                    //заносим цифру в массив
        num /= system;                                                  //удаляем крайнюю цифру
    }
    result = (char*)realloc(result, (++i) * sizeof(char));
    result[i-1] = '\0';
    reverse(result, 0, i-2);                                    //реверс строки
    return result;
}


int ifNumber (char symbol)
{
    if (symbol >= '0' && symbol <= '9')
        return 1;
    else
        return 0;
}

int ifLetter (char symbol)
{
    if (symbol >= 'A' && symbol <= 'F')
        return 1;
    else
        return 0;
}

void reverse (char* str, int i, int j)      
{
    if (j < i)
        return;
    else
    {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        reverse (str, i + 1, j - 1);
    }
}

