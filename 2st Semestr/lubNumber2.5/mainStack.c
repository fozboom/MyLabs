#include "headerStack.h"
#include "../myLibrary.h"
#define _CRT_SECURE_NO_WARNINGS


int main()
{
    struct FILO *head = NULL;
    int end;
    char *str = NULL, *newStr, *task;
    printf("Введите математичское выражение ");
    inputStr(&str);
    if (taskBrackets(str))
        printf("Скобки расставлены верно\n");
    else
    {
        printf("Скобки расставлены неверно\n");
        exit(EXIT_FAILURE);
    }
    do
    {
        printf("Выберите действие:\n");
        printf("'polish' - записать выражение польской нотацией\n");
        printf("'calculate' - посчитать значение выражения\n");
        inputStr(&task);
        if (strcmp(task, "polish") == 0)
        {
            newStr = writeToPolish(str);
            for (int i = 0; newStr[i] != '\0'; i++)
                printf("%c", newStr[i]);
        } else if (strcmp(task, "calculate") == 0)
        {

            newStr = writeToPolish(str);
            calculateMath(newStr);
        } else
            printf("Команда введена неверно");
        repeatProgram(&end);
    } while (!end);
    return 0;
}