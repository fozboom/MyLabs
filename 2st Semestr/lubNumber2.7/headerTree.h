#ifndef MYLABS_HEADERTREE_H
#define MYLABS_HEADERTREE_H

#endif //MYLABS_HEADERTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define SIZE 30

struct tree{
    int data;               //ключ дерева
    struct tree *right;     //указатель на правого потомка
    struct tree *left;      //указатель на левого потомка
};

enum commands {create, read, add, delete, preOrder, inOrder, postOrder, polishTree, find, save, deleteTree, finish};

struct tree * makeNode (int info);
void addNode (struct tree * tmp, struct tree ** root);
void findNode (int info, struct tree * root);
void deleteNode (struct tree ** node, int info);
void printTree(struct tree * root, int indent, bool isLeft, int info);
void createTree (struct tree ** root, int * mas, int n);
void saveTreeToFile(struct tree * root);
struct tree *loadTreeFromFile();
void pre_Order (struct tree * root);
void in_Order (struct tree * root);
void post_Order (struct tree * root);
void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound);
void caseAdd (struct tree ** root);
void caseDelete (struct tree ** root);
struct tree * polishToTree (char * mas);
int calculateTree (struct tree * root);
void caseCreate (struct tree ** root, int ** mas, int * n);
void casePolishTree (char ** str, struct tree ** root, int * result);
void caseFind (struct tree * root);
void freeTree (struct tree * root);
void caseDeleteTree (struct tree ** root);