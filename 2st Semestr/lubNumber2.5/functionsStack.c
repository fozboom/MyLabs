#include "headerStack.h"
#include "../myLibrary.h"





//функция занесения числа или символа в стек
void push (struct FILO **head, union hold info)
{
    struct FILO *tmp = (struct FILO*)malloc(sizeof(struct FILO));   //создание нового элемента
    tmp->next = NULL;
    tmp->data = info;
    if(*head == NULL)                                                   //если голова пустая, то новый элемент теперь голова
        *head = tmp;
    else                                                                //иначе переписать элементы
    {
        tmp->next = *head;
        *head = tmp;
    }
}



//функция удаления числа или символа из стека
union hold popStruct (struct FILO **head)
{
    union hold info = {0};              //info - объединение, которое хранит число или символ
    struct FILO *tmp = *head;
    if(*head != NULL)                   //если стек не пустой
    {
        info = (*head)->data;           //записать данные
        *head = (*head)->next;          //удалить элемент
        free(tmp);
    }

    return info;
}



//функция вычисления выражения записанного обратной польской нотацией
void calculateMath (char* mas)
{
    struct FILO *head;                                  //head - голова стека
    union hold n1, n2, result;                          //n1 - первое число, n2 - второе число
    int i = 0;                                          //i - параметр цикла по строке, result - результат выполнения операции над n1 и n2
    while(mas[i] != '\0')                               //пока не конец строки
    {
        if (ifNumber(mas[i]))                       //если число - заношу его в стек
        {
            result.number = poiskNumber(mas, &i);
            push(&head, result);
        }
        else if (ifOperator(mas[i]))                //если оператор, удаляю два числа из стека и выполняю операцию
        {
            if (mas[i] == '+') {
                n1 = popStruct(&head);                  //удаляю первое число
                n2 = popStruct(&head);                  //удаляю второе число
                result.number = n1.number + n2.number;  //вычисляю
                push(&head, result);               //заношу в стек
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



//функция проверки символа на число
int ifNumber (char s)
{
    if (s >= '0' && s <= '9') return 1;
    else return 0;
}



//функция проверки на оператор
int ifOperator (char s)
{
    if (s == '+' || s == '-' || s == '*' || s == '/' )
        return 1;
    else return 0;
}



//функция нахождения числа
int poiskNumber (char* mas, int* i)
{
    int n = 0;                          //n - число которое нужно взять из строки
    while(mas[*i] != ' ')               //пока не пробел
    {
        n = n*10 + (mas[*i] - '0');     //добавляем цифру к числу
        (*i)++;
    }
    return n;
}



//функция для определения приоритетов операций
int preoritet (char s)
{
    if (s == '*' || s == '/')
        return 2;
    if (s == '+' || s == '-')
        return 1;
    else return 0;
}



//функция записи выражения польской нотацией
char* writeToPolish(char *mas)
{
    char* postfix = (char*)calloc(2* strlen(mas), sizeof(char));    //postfix - строка в польской нотации
    int i, j = 0;                                                                 //i,j - параметры цикла по строкам mas и postfix
    struct FILO *head = NULL;                                                     //head - голова стека
    union hold info;                                                              //info - объединение, которое хранит число или символ
    for (i = 0; mas[i] != '\0'; i++)
    {
        if (ifOperator(mas[i]))                     //если встретил оператор
        {                                              //выталкиваю из стека все операторы, имеющие приоритет выше рассматриваемого
            while (head != NULL && preoritet(head->data.number) >= preoritet(mas[i]))
            {
                postfix[j++] = popStruct(&head).number;
                postfix[j++] = ' ';
            }
            info.number = mas[i];                       //заношу в стек оператор
            push(&head, info);
        }
        else if (mas[i] == '(')                         //если открывающая скобка, заношу в стек
        {
            info.number = mas[i];
            push(&head, info);
        }
        else if (mas[i] == ')')                         //если закрывающая скобка, выталкиваю из стека все операторы до открывающей скобки,
        {                                               // а открывающую скобку удаляю из стека
            while (head != NULL && head->data.number != '(')
            {
                postfix[j++] = popStruct(&head).number;
                postfix[j++] = ' ';
            }
            popStruct(&head);
        }
        if (ifNumber(mas[i]))                       //при нахождении числа заношу его в строку
        {
            while(ifNumber(mas[i])) {
                postfix[j++] = mas[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
    }
    while (head != NULL) {                              //выталкиваем оставшиеся операции из стека
        postfix[j++] = popStruct(&head).number;
    }
    postfix[j] = '\0';
   return postfix;
}



//функция проверки правильности расставленных скобок
int taskBrackets (char* mas)
{
    struct FILO *head = NULL;                               //head - голова стека
    union hold info;                                        //info - объединение, которое хранит число или символ
    for(int i = 0; mas[i] != '\0'; i++)
    {
        char s = mas[i];
        if(s == '(' || s == '{' || s == '[')                //если встретил открывающую скобку, заношу ее в стек
        {
            info.symbol = s;                                //считываю и объединение
            push(&head, info);                              //заношу в стек
        }
        else if (s == ')' || s == '}' || s == ']')          //если встречаю закрывающую скобку, проверяю, что в стеке
        {
            if ((s == ')' && head->data.symbol != '(') ||
                (s == '}' && head->data.symbol != '{') ||
                (s == '}' && head->data.symbol != '{'))
            {
                return 0;                                   //если скобки разного типа, возвращаю ноль
            }
            else
                popStruct(&head);
        }
    }
    if (head != NULL) return 0;                             //если стек не пустой, значит скобки расставлены неверно
    return 1;
}



//функция для продолжения или завершения программы
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







