#include "headerStack.h"

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>




int main ()
{
    struct FILO *head = NULL;
    char* str = NULL, *new;
    printf("Введите математичское выражение ");
    str = inputStr();
    new = (char*)calloc(strlen(str), sizeof(char));
    writeToPostfix(str, new);
    for(int i = 0; new[i] != '\0'; i++)
        printf("%c", new[i], 1);
    mainTask (new, &head);
    return 0;
}