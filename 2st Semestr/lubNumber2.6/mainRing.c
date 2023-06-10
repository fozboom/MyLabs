/*
                                                            Лабораторная работа 6
                                                             Гнетецкого Даниеля
                                                                  Вариант 2
         Условие: Имеются два двунаправленных упорядоченных кольца, в которых могут быть одинаковые элементы.
                  Объединить оба кольца в одно упорядоченное кольцо, исключив повторяющиеся элементы. В кольце я храню
                  имена, чтобы потом использовать их для игры "считалочка". Также кольца я могу сортировать и сливать в
                  одно кольцо. Данные в кольцо можно прочитать из бинарного или текстового файла. Аналогично с записью.
                  Присутствует также возможность удаления имени из кольца.
 */
#include "headerRing.h"
#include "../myLibrary.h"


int main()
{
    struct Ring *p1 = NULL, *p2 = NULL, *newRing = NULL;
    bool taskIsFound;
    enum commands doTask;
    int end = 1, input, format;
    const char* tasks[] = {"mergeRings", "sortRing", "counting", "save", "finish"};
    do
    {
        choiceTask(&doTask, tasks, &taskIsFound);
        if (taskIsFound)
        {
            switch (doTask)
            {
                case mergeRings:
                    caseMergeRings(&input, &format, &p1, &p2, &newRing);
                    break;
                case sortRing:
                    caseSortRing(&input, &format, &p1, &newRing);
                    break;
                case counting:
                    caseCounting(&input, &format, &newRing);
                    break;
                case save:
                    howToSave(&format, newRing);
                    break;
                case finish:
                    end = 0;
                    break;
            }
        }
        else
            printf("\n\033[1;41m\033[1mНеверная команда\033[0m");
    }while(end);
    freeRing(p1, p2, newRing);
    return 0;
}