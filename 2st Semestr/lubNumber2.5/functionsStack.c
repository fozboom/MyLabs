#include "headerStack.h"

char* inputStr ()
{
    int n = 1, i = 0;
    char s;
    char* mas = (char*)calloc(n, sizeof(char));
    while ((s = getchar()) != '\n')
    {
        mas[i] = s;
        mas = (char*)realloc(mas,(++n) * sizeof(char));
        i++;
    }
    mas[i] = '\0';
    return mas;
}

void push (struct FILO **head, union hold info)
{
    struct FILO *tmp = (struct FILO*)malloc(sizeof(struct FILO));
    tmp->next = NULL;
    tmp->data = info;
    if(*head == NULL)
        *head = tmp;
    else
    {
        tmp->next = *head;
        *head = tmp;
    }
}


union hold popStruct (struct FILO **head)
{
    union hold info;
    if(*head != NULL)
    {
        info = (*head)->data;
        *head = (*head)->next;
    }
    return info;
}




void calculateMath (char* mas)
{
    struct FILO *head;
    union hold n1, n2, result;
    int i = 0, operator;
    while(mas[i] != '\0')
    {
        if (ifNumber(mas[i]))
        {
            result.number = poiskNumber(mas, &i);
            push(&head, result);
        }
        else if (ifOperator(mas[i]))
        {
            if (mas[i] == '+') {
                n1 = popStruct(&head);
                n2 = popStruct(&head);
                result.number = n1.number + n2.number;
                push(&head, result);
            }
            else if (mas[i] == '-') {
                n1 = popStruct(&head);
                n2 = popStruct(&head);
                result.number = n2.number - n1.number;
                push(&head, result);
            }
            else if (mas[i] == '*') {
                n1 = popStruct(&head);
                n2 = popStruct(&head);
                result.number = n2.number * n1.number;
                push(&head, result);
            }
            else if (mas[i] == '/') {
                n1 = popStruct(&head);
                n2 = popStruct(&head);
                result.number = n2.number / n1.number;
                push(&head, result);
            }

        }
        i++;
    }
    printf("\nРезультат вычисления данного выражения: %d", result.number);
}

int ifNumber (char s)
{
    if (s >= '0' && s <= '9') return 1;
    else return 0;
}

int ifOperator (char s)
{
    if (s == '+' || s == '-' || s == '*' || s == '/' )
        return 1;
    else return 0;
}

int poiskNumber (char* mas, int* i)
{
    int n = 0;
    while(mas[*i] != ' ')
    {
        n = n*10 + (mas[*i] - '0');
        (*i)++;
    }
    return n;
}


void printStack (struct FILO *head)
{
    struct FILO *tmp = head;
    while(tmp != NULL)
    {
        printf("%d --", tmp->data.number);
        tmp = tmp->next;
    }
}

int preoritet (char s)
{
    if (s == '*' || s == '/')
        return 2;
    if (s == '+' || s == '-')
        return 1;
    else return 0;
}

char* writeToPolish(char *mas)
{
    char* postfix = (char*)calloc(2* strlen(mas), sizeof(char));
    int i, j = 0, n;
    struct FILO *head = NULL;
    union hold info;
    for (i = 0; mas[i] != '\0'; i++)
    {
        if (ifOperator(mas[i]))
        {
            while (head != NULL && preoritet(head->data.number) >= preoritet(mas[i]))
            {
                postfix[j++] = popStruct(&head).number;
            }
            info.number = mas[i];
            push(&head, info);
            postfix[j++] = ' ';
        }
        else if (mas[i] == '(')
        {
            info.number = mas[i];
            push(&head, info);
            postfix[j++] = ' ';
        }
        else if (mas[i] == ')')
        {
            while (head != NULL && head->data.number != '(')
            {
                postfix[j++] = popStruct(&head).number;
            }
            popStruct(&head);
            postfix[j++] = ' ';
        }
        if (ifNumber(mas[i]))
        {
            while(ifNumber(mas[i])) {
                postfix[j++] = mas[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
    }
    while (head != NULL) {
        postfix[j++] = popStruct(&head).number;
    }
    postfix[j] = '\0';
   return postfix;
}


int taskBrackets (char* mas)
{
    struct FILO *head = NULL;
    union hold info;
    for(int i = 0; mas[i] != '\0'; i++)
    {
        char s = mas[i];
        if(s == '(' || s == '{' || s == '[')
        {
            info.symbol = s;
            push(&head, info);
        }
        else if (s == ')' || s == '}' || s == ']')
        {
            if ((s == ')' && head->data.symbol != '(') ||
                (s == '}' && head->data.symbol != '{') ||
                (s == '}' && head->data.symbol != '{'))
            {
                return 0;
            }
            else
                popStruct(&head);
        }
    }
    if (head != NULL) return 0;
    return 1;
}


void repeatProgram(int *end)
{
    printf("\nЧтобы продолжить введите 0");
    printf("\nЧтобы завершить введите 1\n");
    while(!(scanf("%d", end)) || (*end != 0 && *end != 1))
    {
        rewind(stdin);
        printf("\nОшибка ввода числа");
    }
    rewind(stdin);
    system("clear");
}







