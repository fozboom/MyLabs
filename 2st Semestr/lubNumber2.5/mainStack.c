#include "headerStack.h"
#include "../myLibrary.h"


int main()
{
    struct FILO *head = NULL;                               //head - голова стека, верхний элемент
    int end;                                                //end - переменная для продолжения/завершения программы
    char *str = NULL, *newStr, *task;                       //str - исходное выражение, newStr - выражение польской нотацией
    printf("Введите математичское выражение ");             //task - переменная для выбора задачи
    inputStr(&str);                                    //ввод исходного математического выражения
    if (taskBrackets(str))                             //проверка правильности расставленных скобок
        printf("Скобки расставлены верно\n");
    else
    {
        printf("Скобки расставлены неверно\n");
        exit(EXIT_FAILURE);
    }
    do                                                      //зацикливание программы
    {
        printf("Выберите действие:\n");
        printf("'polish' - записать выражение польской нотацией\n");
        printf("'calculate' - посчитать значение выражения\n");
        inputStr(&task);                                //ввод нужной задачи
        if (strcmp(task, "polish") == 0)                     //команда записи польской нотацией
        {
            newStr = writeToPolish(str);                //запись польской нотацией в строку newStr
            outputString(newStr);
        }
        else if (strcmp(task, "calculate") == 0)             //функция вычисления математического выражения
        {
            newStr = writeToPolish(str);                //запись выражения польской нотацией
            calculateMath(newStr);                      //вычисление значения выражения
        }
        else
            printf("Команда введена неверно");
        repeatProgram(&end);                                //зацикливание программы
    } while (!end);
    return 0;
}