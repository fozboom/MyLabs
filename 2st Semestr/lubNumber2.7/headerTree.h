#ifndef MYLABS_HEADERTREE_H
#define MYLABS_HEADERTREE_H

#endif //MYLABS_HEADERTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tree{
    int data;
    struct tree *right;
    struct tree *left;
};

struct tree * makeNode (int info);
void addNode (struct tree * tmp, struct tree ** root);
struct tree * findNode (int info, struct tree * root);
void deleteNode (struct tree ** node, int info);