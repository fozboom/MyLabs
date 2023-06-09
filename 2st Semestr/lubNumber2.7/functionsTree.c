#include "headerTree.h"


struct tree * makeNode (int info)
{
    struct tree * tmp = (struct tree *)malloc(sizeof(struct tree));
    if(tmp != NULL)
    {
        tmp->data = info;
        tmp->right = NULL;
        tmp->left = NULL;
        return tmp;
    }
    else
    {
        printf("\nОшибка при создании нового узла");
        return NULL;
    }

}

void addNode (struct tree * tmp, struct tree ** root)
{
    if (*root == NULL)
    {
        *root = tmp;
    }
    else if (tmp->data < (*root)->data)
    {
        addNode(tmp, &(*root)->left);
    }
    else if (tmp->data > (*root)->data)
    {
        addNode(tmp, &(*root)->right);
    }
    else
    {
        printf("\nТакое число уже есть в дереве");
    }
}

struct tree * findNode (int info, struct tree * root)
{
    if(root == NULL)
    {
        printf("\nДерево пустое");
        return NULL;
    }
    struct tree * tmp = root;
    while (tmp != NULL)
    {
        if (tmp->data == info)
        {
            return tmp;
        }
        else if (info < tmp->data)
        {
            tmp = tmp->left;
        }
        else if (info > tmp->data)
        {
            tmp = tmp->right;
        }
    }
    printf("\nТакого элемента в дереве нет");
    return NULL;
}


void deleteNode (struct tree ** root, int info)
{
    if ((*root)->data > info)
    {
        deleteNode(&(*root)->left, info);
    }
    else if ((*root)->data < info)
    {
        deleteNode(&(*root)->right, info);
    }
    else if ((*root)->data == info)
    {
        struct tree * tmp;
        if((*root)->right == NULL)
        {
            tmp = *root;
            (*root) = (*root)->left;
            free(tmp);
        }
        else if((*root)->left == NULL)
        {
            tmp = *root;
            (*root) = (*root)->right;
            free(tmp);
        }
        else
        {
            tmp = (*root)->left;
            while(tmp->right != NULL)
            {
                tmp = tmp->right;
            }
            tmp->right = (*root)->right;
            tmp = (*root);
            (*root) = (*root)->left;
            free(tmp);

        }
    }
}
