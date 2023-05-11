#include "headerPractice.h"
#include "../myLibrary.h"


/*
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
                textRSA(code, size, d, n);
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
    return 0;
}
*/
/*int main()
{
    char s1 = 'A', s2 = 'B';
    char* mas = NULL;
    inputStr(&mas);
    char **box1, **box2, **box3, **box4;
    createBoxes(&box1, &box2, &box3, &box4, SIZE);
    writeBox(box2, SIZE);
    writeBox(box3, SIZE);
    readInfo(box1, SIZE, "box1.txt");
    readInfo(box4, SIZE, "box4.txt");

    outputBox(box1, SIZE);
    outputBox(box2, SIZE);
    outputBox(box3, SIZE);
    outputBox(box4, SIZE);
    mas = codingSquare(box1, box2, box3, box4, mas);
    decodeSquare(box1, box2, box3, box4, mas);
    return 0;
}*/

int main()
{
    const char* commands[] = {"input", "createKey", "read", "encoding", "decoding", "save", "finish"};
    enum choiceCommand command;
    int end = 1;
    char **text = NULL;
    bool taskIsFound;
    do
    {
        choiceTask(&command, commands, &taskIsFound);
        if (taskIsFound)
        {
            switch(command)
            {
                case input:
                    input2DString(&text);
                    break;
                case createKey:
                    break;
                case read:
                    break;
                case encoding:
                    break;
                case decoding:
                    break;
                case save:
                    break;
                case finish:
                    end = 0;
                    break;
            }
        }
        else
        {
            printf("\nКоманда введена неверно, попробуй еще раз\n");
        }

    }while(end);
    return 0;
}

