#include "headerUnion2.h"
#include "../myLibrary.h"

int main()
{
    bool taskIsFound, end = true;
    enum choice doTask;
    struct child *info = NULL, *sortInfo = NULL;
    char* task = NULL, *fileName = NULL, *disease = NULL;
    int n = 1, size = 1, k;;
    const char* tasks[] = {"input", "read", "add", "delete", "look", "write", "finish"};
    do
    {

        choiseTask(&task, &doTask, tasks, &taskIsFound);
        if(taskIsFound)
        {
            switch (doTask)
            {
                case input:
                    inputStruct(&info, &n);
                    outputStruct(info, n);
                    break;
                case read:
                    printf("Введите имя файла ");
                    inputStr(&fileName);
                    readWithFile(&info, &n, fileName);
                    outputStruct(info, n);
                    break;
                case add:
                    addChild(&info, &n);
                    outputStruct(info, n);
                    break;
                case delete:
                    printf("Введите номер ребенка, которого нужно удалить");
                    inputInt(&k, 0, n-1);
                    deleteChild(&info, &n, k);
                    outputStruct(info, n);
                    break;
                case look:
                    printf("Введите болезнь, которую нужно найти ");
                    inputStr(&disease);
                    findDisease(info, &sortInfo, n, &size, disease);
                    quickSorting(sortInfo, 0, size - 1, comparatorSurnames);
                    outputStruct(sortInfo, size);
                    break;
                case write:
                    printf("Введите имя файла ");
                    inputStr(&fileName);
                    inputWithFile(info, n, fileName);
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
    return 0;
}