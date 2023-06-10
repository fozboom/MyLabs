#include "myLibrary.h"

//функция вывода строки
void outputString(char* mas)
{
    printf("\n");
    for(int i = 0; mas[i] != '\0'; i++)
        printf("\033[1;32m\033[1m%c\033[0m", mas[i]);

    printf("\n");
}



//функция вывода массива чисел
void outputMasNumbers (long* mas)
{
    printf("\n");
    for(int i = 0; i < mas[0]; i++)
        printf("%ld ", mas[i]);
}

void output2DString (char** mas, int n)
{
    if(mas == NULL)
    {
        return;
    }
    for(int i = 0; i < n; i++)
    {
        printf("\n");
        for(int j = 0; mas[i][j] != '\0'; j++)
            printf("%c", mas[i][j]);
    }
}



//функция ввода числа с првоеркой
void inputInt (int* x, int a, int b)
{
    rewind(stdin);
    while(!scanf("%d", x) || (((*x) < a) || ((*x) > b)))
    {
        rewind(stdin);
        printf("\nОшибка ввода числа, попробуйте еще раз: ");
    }
    rewind(stdin);
}


void inputLong (long* x, int a, int b)
{
    while(!scanf("%ld", x) || (((*x) < a) || ((*x) > b)))
    {
        rewind(stdin);
        printf("\nОшибка ввода числа, попробуйте еще раз: ");
    }
    rewind(stdin);
}



//функция ввода строки произвольной длины
void inputStr (char** mas)
{
    rewind(stdin);
    int n = 1, i = 0;                                                //n - длина строки, i - параметр цикла
    char s;
    *mas = (char*)calloc(n, sizeof(char));          //выделение памяти на один элемент
    while ((s = getchar()) != '\n')
    {
        *(*mas + i) = s;                                                 //запись символа в строку
        *mas = (char*)realloc(*mas,(++n) * sizeof(char));    //перевыделение памяти
        i++;
    }
    *(*mas + i) = '\0';                                                  //запись нуль-терминатора
}

void inputNumberMas (int** mas, int n)
{
    *mas = (int*)calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
        scanf("%d", &(*(*mas + i)));
}

void outputNumberMas (int* mas, int n)
{
    printf("\n");
    for(int i = 0; i < n; i++)
        printf("%d", mas[i]);
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
void input2DString (char*** text, long* n)
{
    printf("\nВведите текст, чтобы завершить ввод введите Enter\n");
    int i = 0;
    *text = (char**)calloc(1, sizeof(char*));
    *(*text + i) = (char*)calloc(80, sizeof(char));
    do
    {
        fgets(*(*text + i), 80, stdin);
        if(*(*(*text + i)) == '\n') break;
        deleteSymbolN(&(*(*text + i)));
        i++;
        *text = (char**)realloc(*text, (i+1) * sizeof(char*));
        *(*text + i) = (char*)calloc(80, sizeof(char));
    }while(true);
    *n = i;
}

void deleteSymbolN (char** str)
{
    int n = strlen(*str);
    *(*str + n - 1) = '\0';
    *str = (char*)realloc(*str, n * sizeof(char));
}

void readIn2DString (char*** text, long* n)
{
    FILE* file;
    int i = 0;
    char* fileName = NULL;
    printf("\nВведите имя файла: ");
    inputStr(&fileName);
    file = fopen(fileName, "r");
    if(file == NULL)
    {
        printf("\nОшибка открытия файла\n");
        exit(EXIT_FAILURE);
    }
    *text = (char**)calloc(1, sizeof(char*));
    *(*text + i) = (char*)calloc(80, sizeof(char));
    while(fgets(*(*text + i), 80, file) != NULL)
    {
        deleteSymbolN(&(*(*text + i)));
        i++;
        *text = (char**)realloc(*text, (i+1) * sizeof(char*));
        *(*text + i) = (char*)calloc(80, sizeof(char));
    }
    *n = i;
    *text = (char**)realloc(*text, (*n) * sizeof(char*));
    printf("\nПрочитанный из файла текст:\n");
    output2DString(*text, *n);
}

void output2DNumbers (long** mas, long n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\n");
        for(int j = 0; j < mas[i][0]; j++)
            printf("%ld ", mas[i][j]);
    }
}


void inputIntMas (int ** mas, int * n)
{
    printf("\nВведите числа через пробел, чтобы завершить ввод, введите не число\n");
    *n = 1;
    int i = 0, x;
    *mas = (int*)calloc((*n), sizeof(int));
    while(scanf("%d", &x))
    {
        *mas = (int*)realloc(*mas, (*n)++ * sizeof(int));
        *(*mas + i++) = x;
    }
    (*n)--;
}

void outputIntMas (int * mas, int n)
{
    printf("\n");
    for(int i = 0; i < n; i++)
        printf("%d ", mas[i]);
    printf("\n");
}

int proverka (char* mas)
{
    for(int i = 0; mas[i] != '\0'; i++)
    {
        if(mas[i] != ' ')
            return 0;
    }
    return 1;
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

//функция для определения приоритетов операций
int preoritet (char s)
{
    if (s == '*' || s == '/')
        return 2;
    if (s == '+' || s == '-')
        return 1;
    else return 0;
}

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


















