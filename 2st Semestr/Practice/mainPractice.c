


#include "headerPractice.h"
#include "../myLibrary.h"


int main()
{
    char *task, *str;
    long  p, q, n, fi, d = 1, e, *code, end = 1;
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
            code = coding(str, e, n);
            outputMasNumbers(code, strlen(str));

        } else if (strcmp(task, "decoding") == 0)
        {
            printf("Введите ключ для расшифровки:\n");
            printf("d = ");
            scanf("%ld", &d);
            printf("\nn = ");
            scanf("%ld", &n);
            str = decoding(code, d, n, strlen(str));
        }
        else if (strcmp(task, "exit") == 0)
            end = 0;
        printf("\n p = %ld", p);
        printf("\n q = %ld", q);
        printf("\n n = %ld", n);
        printf("\n fi = %ld", fi);
        printf("\n e = %ld", e);
        printf("\n d = %ld", d);

        outputStr(str);
    }while(end);

}
