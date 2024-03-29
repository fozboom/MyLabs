#include "headerTree.h"

//                                                      Лабораторная работа 7
//                                                       Гнетецкого Даниеля
/*      Условие: Пусть есть поток чисел: 14, 15, 4, 9, 7, 18, 3, нужно занести это все в дерево.
                 Написать три обхода дерева: в прямом порядке, в симметричном порядке, в обратном порядке.
                 Реализовать функции добавления, удаления, нахождения элемента в дереве, полное удаление дерева.
                 Также я реализовал чтение и запись дерева в файл с помощью сериализации, также подсчет математического
                 выражения через дерево.                                                                                                                                        */
int main()
{
    struct tree * root = NULL;
    bool taskIsFound;
    enum commands doTask;
    int end = 1, * mas, n, result;
    const char* tasks[] = {"create", "read", "add", "delete", "preOrder", "inOrder", "postOrder", "BFT", "polishTree","find", "save", "deleteTree", "finish"};
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
                case BFT:
                    printf("Вывод дерева в ширину порядке:\n");
                    caseBFT(root);
                    break;
                case polishTree:
                    casePolishTree(&str, &root, &result);
                    break;
                case deleteTree:
                    caseDeleteTree(&root);
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