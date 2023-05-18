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
    int end = 1, n;
    char **text = NULL, box1[SIZE][SIZE], box2[SIZE][SIZE], box3[SIZE][SIZE], box4[SIZE][SIZE], **newText;
    bool taskIsFound;
    struct dataCode* keys;
    long **codeText = NULL, countKeys, rows;
    //createBoxes(&box1, &box2, &box3, &box4, SIZE);
    readInfo(box1, SIZE, "box1.txt");
    readStructInfo(&keys, &countKeys);
    do
    {
        choiceTask(&command, commands, &taskIsFound);
        if (taskIsFound)
        {
            switch(command)
            {
                case input:
                    input2DString(&text, &n);
                    break;
                case read:
                    readIn2DString(&text, &n);
                    break;
                case encoding:
                    countKeys++;
                    keys = (struct dataCode*)realloc(keys, countKeys * sizeof (struct dataCode));
                    keys[countKeys - 1] = encodingText(text, n, &codeText, &newText);
                    if(codeText != NULL)
                        output2DNumbers(codeText, n);
                    else
                        output2DString(newText, n);
                    break;
                case decoding:
                    text = decodingText(codeText, newText, keys, countKeys, box1, &rows);
                    printf("\nРаскодированный текст:\n");
                    output2DString(text, rows);
                    break;
                case save:
                    keys[countKeys- 1] = saveEncodingInfo (newText, codeText, n, keys[countKeys - 1]);
                    break;
                case finish:
                    saveStructInfo(keys, countKeys);
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

/*int main()
{
    struct dataCode* keys = (struct dataCode*)calloc(3, sizeof(struct dataCode));
    long count;
   *//* strcpy(keys[0].fileName, "one");
    keys[0].flag = 1;
    keys[0].e = 324;
    keys[0].d = 16;
    keys[0].n = 412;
    strcpy(keys[1].fileName, "");
    keys[1].flag = 1;
    keys[1].e = 34;
    keys[1].d = 1;
    keys[1].n = 4902;
    strcpy(keys[2].fileName, "one");
    keys[2].flag = 1;
    keys[2].e = 324;
    keys[2].d = 165;
    keys[2].n = 42;

    saveStructInfo(keys, 3);*//*
    readStructInfo(&keys, &count);
    printf(" ");
    return 0;
}*/

