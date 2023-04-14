#include "headerUnion2.h"
//#include "../myLibrary.h"

int main()
{
    int n = 1;
    struct child *info = NULL, *sortInfo = NULL;
    char* task, *fileName, *disease;
    do
    {
        printf("Выберите действие:\n");
        printf("'input' - ввод данных с клавиатуры\n");
        printf("'read' - использовать готовые данные из бинарного файла\n");
        printf("'add' - добавить данные в структуру\n");
        printf("'delete' - удалить данные из структуры\n");
        printf("'look' - найти людей с определенной болезнью\n");
        printf("'write' - сохранить данные в бинарный файл\n");
        printf("'exit' - завершить программу\n");
        inputStr(&task);
        if (strcmp(task, "input") == 0)
        {
            inputStruct(&info, &n);
        } else if (strcmp(task, "read") == 0)
        {
            printf("Введите имя файла ");
            inputStr(&fileName);
            readFromBinaryFile(&info, fileName, &n);
        } else if (strcmp(task, "look") == 0)
        {
            printf("Введите болезнь, которую нужно найти ");
            inputStr(&disease);

        } else if (strcmp(task, "write") == 0)
        {
            printf("Введите имя файла ");
            inputStr(&fileName);
            writeInBinaryFile(info, n, fileName);
            quickSorting(info, 0, n - 1, comparatorSurnames);
        }
        outputStruct(info, n);
    }while(strcmp(task, "exit") != 0);
    return 0;
}