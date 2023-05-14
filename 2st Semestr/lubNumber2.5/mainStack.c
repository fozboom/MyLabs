#include "headerStack.h"
#include "../myLibrary.h"

/*
                                                Лабораторная работа 5
                                                 Гнетецкого Даниеля
        Условие: Дано некоторое математическое выражение, в котором есть несколько уровней вложенных скобок. Проверить
                 правильность расставленных скобок и исправить ошибки. Я также реализовал несколько дополнительных функций:
                 запись выражения польской нотацией через стек, подсчет этого выражения через стек, перевод результата
                 в любую систему счисления тоже через стек.

*/

int main()
{
    int result;                                                 //end - переменная для продолжения/завершения программы, result - результат мат выражения
    char *str = NULL, *newStr, *strInNewSystem;                 //str - исходное выражение, newStr - выражение польской нотацией
    const char* tasks[] = {"polish","calculate", "convert", "finish"};
    enum commands doTask;                                       //tasks - массив команд, doTask - перечисление для читабельности кода
    bool taskIsFound, end = true;                               //taskIsFound - переменная для проверки правильности введенной команды

    printf("Введите математическое выражение ");
    inputStr(&str);                                        //ввод исходного математического выражения
    taskBrackets(str);                                     //проверка правильности расставленных скобок и исправление
    do                                                          //зацикливание программы
    {
        choiceTask(&doTask, tasks, &taskIsFound);               //выбор команды
        if(taskIsFound)
        {
            switch (doTask)
            {
                case polish:                                    //команда записи выражения польской нотацией
                    newStr = writeToPolish(str);           //функция записи польской нотацией в строку newStr
                    outputString(newStr);                  //функция вывода выражения на экран
                    break;
                case calculate:                                 //команда вычисления математического выражения
                    result = calculateMath(str);           //функция вычисления значения выражения
                    printf("\nРезультат вычисления данного выражения: %d", result);
                    break;
                case convert:                                   //команда перевода результата в любую систему счисления
                    strInNewSystem = translateDecimal(str);//функция перевода в любую систему счисления
                    outputString(strInNewSystem);
                    break;
                case finish:                                    //команда завершения программы
                    end = false;
                    break;
            }
        }
        else                                                    //если команда введена неверно, выдать предупреждение
        {
            printf("\nКоманда введена неверно, попробуйте еще раз\n");
        }
    } while (end);
    freeMemory (str, newStr, strInNewSystem);
    return 0;
}