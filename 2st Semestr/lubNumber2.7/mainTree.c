#include "headerTree.h"

int main()
{
    struct tree * root = NULL, * tmp = NULL;
    tmp = makeNode(5);
    addNode(tmp, &root);
    tmp = makeNode(6);
    addNode(tmp, &root);
    tmp = makeNode(3);
    addNode(tmp, &root);
    tmp = makeNode(4);
    addNode(tmp, &root);
    tmp = makeNode(7);
    addNode(tmp, &root);
    tmp = makeNode(9);
    addNode(tmp, &root);
    deleteNode(&root, 5);
    return 0;
}