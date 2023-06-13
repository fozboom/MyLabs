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

enum commands {create, read, add, delete, preOrder, inOrder, postOrder, BFT, polishTree, find, save, deleteTree, finish};

struct tree * makeNode (int info);                              //функция создания нового узла дерева
void addNode (struct tree * tmp, struct tree ** root);          //функция добавления нового узла в дерево
void findNode (int info, struct tree * root);                   //функция поиска элемента в дереве
void deleteNode (struct tree ** root, int info);                //функция удаления узла из дерева
void printTree(struct tree * , int , bool , int );              // Функция для вывода бинарного дерева
void createTree (struct tree ** root, int * mas, int n);        //функция создания дерева из массива чисел

void saveTreeToFile(struct tree * root);                        //функция меню сохранения в файл
struct tree *loadTreeFromFile();                                //функция меню чтения данных из файла

void pre_Order (struct tree * root);                            //обход в прямом порядке
void in_Order (struct tree * root);                             //обход дерева в симметричном порядке
void post_Order (struct tree * root);                           //обход дерева в обратном порядке
void caseBFT (struct tree * root);                              //функция обхода дерева в ширину

struct tree * polishToTree (char * mas);                        //функция создания дерева из польской нотации
int calculateTree (struct tree * root);                         //функция вычисления дерева

void choiceTask (enum commands *, const char* tasks[], bool *); //функция меню выбора задачи
void caseAdd (struct tree ** root);                             //функция меню добавления элемента в дерево
void caseDelete (struct tree ** root);                          //функция меню удаления элемента из дерева
void caseCreate (struct tree ** root, int ** mas, int * n);     //функция меню создания дерева из массива
void casePolishTree (char ** str, struct tree ** root, int * ); //функция меню вычисления выражения через дерево
void caseFind (struct tree * root);                             //функция меню нахождения элемента в дереве
void caseDeleteTree (struct tree ** root);                      //функция меню удаления дерева
void freeTree (struct tree * root);                             //функция очистки памяти













