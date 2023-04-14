#include "headerLections.h"
#include "../myLibrary.h"

int main ()
{
    int n, s;
    char* str;
    struct Ring *p = NULL;
    struct Ring *tmp = (struct Ring*)malloc(sizeof(struct Ring));
    printf("Введите кол-во игроков\n");
    scanf("%d", &n);
    rewind(stdin);
    for(int i = 0; i < n; i++)
    {
        printf("Введите %d фамилию   ", i+1 );
        inputStr((&str));
        push_after(&p, str);
    }
    print(p);
    printf("Введите кол-во слов считалочки\n");
    scanf("%d", &s);
    rewind(stdin);
    while(p != p->next)
    {
        tmp = p;
        for(int i = 0; i < s - 2; i++)
        {
            tmp = tmp->next;
        }
        p = tmp;
        pop(&p);

    }
    print(p);
    return 0;
}
