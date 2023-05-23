#include "headerPractice.h"
#include "../myLibrary.h"



int main()
{
    const char* commands[] = {"input", "read", "encoding", "decoding", "save", "finish"};
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
                    caseEncoding(&keys, &countKeys, &codeText, text, n, &newText);
                    break;
                case decoding:
                    caseDecoding(&text, codeText, newText, keys, countKeys, box1, &rows);
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

