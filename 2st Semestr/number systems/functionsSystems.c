#include "headerSystems.h"
#include "../myLibrary.h"

void convertToDecimal (char* num, int n, int* numInDecimal, int system)
{
    int power = 1;
    for (int i = n - 1; i >= 0; i--)
    {
        int number;
        if (ifNumber(num[i])) {
            number = num[i] - '0';
        }

        else
        {
            number = num[i] - 'A' + 10;
        }

        *numInDecimal += number * power;
        power *= system;
    }


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

