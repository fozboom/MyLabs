/*
                                                            Лабораторная работа 6
                                                             Гнетецкого Даниеля
                                                                  Вариант 2
         Условие: Имеются два двунаправленных упорядоченных кольца, в которых могут быть одинаковые элементы.
                  Объединить оба кольца в одно упорядоченное кольцо, исключив повторяющиеся элементы
 */






#include "headerRing.h"
#include "../myLibrary.h"


int main()
{
    struct Ring *p1 = NULL, *p2 = NULL, *newRing = NULL;
    bool taskIsFound;
    enum commands doTask;
    int end = 1;
    char* task = NULL, *fileName = NULL, *disease = NULL;
    const char* tasks[] = {"mergeRings", "sortRing", "counting", "finish"};
    do
    {
        choiceTask(&doTask, tasks, &taskIsFound);
        if (taskIsFound)
        {
            switch (doTask)
            {
                case mergeRings:
                    inputRing(&p1);
                    inputRing(&p2);
                    p1 = sortingRing(p1);
                    p2 = sortingRing(p2);
                    newRing = mergeRingsInOne(p1, p2);
                    printRing(newRing);
                    break;
                case sortRing:
                    inputRing(&p1);
                    printRing(p1);
                    newRing = sortingRing(p1);
                    break;
                case counting:

                    break;

                case finish:
                    end = 0;
                    break;
            }
        }
    }while(end);
    return 0;
}