


#include "headerPractice.h"
#include "../myLibrary.h"


int main()
{
    char *task, *str;
    const char* fileName;
    long  p, q, n, fi, d = 1, e, *code, end = 1, size = 0;
    FILE* file;
    do
    {
        printf("Выберите действие:\n");
        printf("'coding' - закодировать текст\n");
        printf("'decoding' - раскодировать текст\n");
        printf("'exit' - завершить программу\n");
        inputStr(&task);

        if (strcmp(task, "coding") == 0)
        {
            printf("Введите сообщение, которое хотите закодировать\n");
            inputStr(&str);
            createNumbers(&p, &q, &n, &fi);
            createEilerNumber(&e, fi);
            search_d(&d, e, fi);
            code = coding(str, e, n, &size);
            outputMasNumbers(code, size);

            printf("\nХотите сокхранить закодированный текст в файл?\n");
            printf("'yes' - да\n");
            printf("'no' - нет\n");
            inputStr(&task);
            if (strcmp(task, "yes") == 0)
            {
                tekstRSA(code, size, d, n);
            }
        }
        else if (strcmp(task, "decoding") == 0)
        {
            printf("Введите имя файла, который хотите раскодировать:\n");

        }
        else if (strcmp(task, "exit") == 0)
        {
            end = 0;
        }

    }while(end);
    printf("\n p = %ld", p);
    printf("\n q = %ld", q);
    printf("\n n = %ld", n);
    printf("\n fi = %ld", fi);
    printf("\n e = %ld", e);
    printf("\n d = %ld", d);

}
