#include "headerUnion.h"
#include "../myLibrary.h"


/*
                                                            Лабораторная работа 4
                                                             Гнетецкого Даниеля
                                                                  Вариант 2
         Условие: В массиве структур хранится информация о детях детского сада. Элементом структуры является объединение,
                    в котором хранится следующая информация: последнее заболевание ребенка (грипп, ангина и т. д.)и имя
                    участкового врача. Если ребенок находился в больнице, то и номер больницы, ее адрес и фамилия лечащего врача.
                    Вывести в алфавитном порядке фамилии детей имеющих определенное заболевание
 */

int main()
{
    bool taskIsFound, end = true;                                     //taskIsFound - переменная для проверки правильности выбора задачи, end - для завершения
    enum choice doTask;                                               //doTask - пересечение для удобства читабельности кода, k - номер удаляемого ребенка
    struct child *info = NULL, *sortInfo = NULL;                      //info - исходный массив, sortInfo - массив детей с определенным заболеванием
    char* task = NULL, *fileName = NULL, *disease = NULL;             //task - имя задачи, fileName - имя файла, disease - название заболевания
    int n = 1, size = 1, k;                                           //n - число структур массива info, size - число структур массива sortInfo
    const char* tasks[] = {"input", "read", "add", "delete", "look", "write", "finish"};
    do
    {
        choiseTask(&task, &doTask, tasks, &taskIsFound);              //выбор задачи, которую нужно сделать
        if(taskIsFound)                                               //если пользователь ввел задачу правильно
        {
            switch (doTask)
            {
                case input:
                    inputStruct(&info, &n);                           //ввод массива структур с клавиатуры
                    outputStruct(info, n);                            //вывод массива структур на экран
                    break;
                case read:
                    printf("Введите имя файла ");
                    inputStr(&fileName);                         //ввод имени файла
                    readWithFile(&info, &n, fileName);                //чтение данных из файла
                    outputStruct(info, n);                            //вывод массива структур на экран
                    break;
                case add:
                    addChild(&info, &n);                              //добавление ребенка в массив структур
                    outputStruct(info, n);                            //вывод массива структур на экран
                    break;
                case delete:
                    printf("Введите номер ребенка, которого нужно удалить");
                    inputInt(&k, 0, n-1);                     //ввод номера ребенка, которого надо удалить
                    deleteChild(&info, &n, k);                      //удаление элемента из массива структур
                    outputStruct(info, n);                             //вывод массива структур на экран
                    break;
                case look:
                    printf("Введите болезнь, которую нужно найти ");
                    inputStr(&disease);                           //ввод болезни, которую нужно найти
                    findDisease(info, &sortInfo, n, &size, disease);   //создание массива структур детей с конкретной болезнью
                    quickSorting(sortInfo, 0, size - 1, comparatorSurnames);
                    outputStruct(sortInfo, size);              //сортировка по алфавиту и вывод на экран
                    break;
                case write:
                    printf("Введите имя файла ");
                    inputStr(&fileName);                          //ввод имени файла
                    inputWithFile(info, n, fileName);                  //запись массива структур в файл
                    break;
                case finish:
                    end = false;
                    break;
            }
        }
        else
            printf("Команда введена неверно");
    }while(end);
    freeMemory(info, sortInfo, task, fileName, disease);
    return 0;                                                         //очистка памяти
}