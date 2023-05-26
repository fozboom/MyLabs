#include "headerPractice.h"
#include "../myLibrary.h"



int main()
{
    const char* commands[] = {"input", "read", "encoding", "decoding", "save", "finish"};
    enum choiceCommand command;
    int end = 1;
    char **text = NULL, box1[SIZE][SIZE], box2[SIZE][SIZE], box3[SIZE][SIZE], box4[SIZE][SIZE], **newText;
    bool taskIsFound;
    struct dataCode* keys;
    long **codeText = NULL, countKeys, rows, n;
    readInfo(box1, SIZE, "box1.txt");
    readInfo(box4, SIZE, "box4.txt");
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
                    caseReadText(&text, &n);
                    break;
                case encoding:
                    caseEncoding(&keys, &countKeys, &codeText, text, n, &newText);
                    break;
                case decoding:
                    caseDecoding(&text, codeText, newText, keys, countKeys, box1, &rows);
                    break;
                case save:
                    saveInformation(text, newText, codeText, n, keys, countKeys);
                    break;
                case finish:
                    saveStructInfo(keys, countKeys);
                    end = 0;
                    break;
            }
        }
        else
        {
            printf("\n\033[3;31m Команда введена неверно, попробуйте еще раз \033[0m\n");
        }

    }while(end);
    return 0;
}


