#include "headerTree.h"
#include "../myLibrary.h"





int main()
{
    struct tree * root = NULL;
    bool taskIsFound;
    enum commands doTask;
    int end = 1, * mas, n, result;
    const char* tasks[] = {"create", "read", "add", "delete", "preOrder", "inOrder", "postOrder", "polishTree","find", "save", "finish"};
    char* str;
    do
    {
        choiceTask(&doTask, tasks, &taskIsFound);
        if (taskIsFound)
        {
            switch (doTask)
            {
                case create:
                    caseCreate(&root, &mas, &n);
                    break;
                case read:
                    root = loadTreeFromFile();
                    printTree(root, 0, 0, -1);
                    break;
                case add:
                    caseAdd(&root);
                    break;
                case delete:
                    caseDelete(&root);
                    break;
                case find:
                    caseFind(root);
                    break;
                case preOrder:
                    printf("Вывод дерева в прямом порядке:\n");
                    pre_Order(root);
                    break;
                case inOrder:
                    printf("Вывод дерева в симметричном порядке:\n");
                    in_Order(root);
                    break;
                case postOrder:
                    printf("Вывод дерева в обратном порядке:\n");
                    post_Order(root);
                    break;
                case polishTree:
                    casePolishTree(&str, &root, &result);
                    break;
                case save:
                    saveTreeToFile(root);
                case finish:
                    end = 0;
                    break;
            }
        }
        else
            printf("\n\033[1;41m\033[1mНеверная команда\033[0m");
    }while(end);
    freeTree(root);
    return 0;
}