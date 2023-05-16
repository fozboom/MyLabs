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
    while(!scanf("%d", x) || (((*x) < a) || ((*x) > b)))
    {
        rewind(stdin);
        printf("\nОшибка ввода числа, попробуйте еще раз: ");
    }
    rewind(stdin);
}



//функция ввода строки произвольной длины
void inputStr (char** mas)
{
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




void addNode (struct tree *root, struct tree *newNode, int a)
{
    if(a < root->data)
    {
        if (root->left != NULL)
            addNode(root->left, newNode, a);
        else
            root->left = newNode;
    }

    else
    {
        if (a > root->data)
        {
            if(root->right != NULL)
                addNode(root->right, newNode, a);
            else
                root->right = newNode;
        }
    }
}

struct tree* makeNode (int a)
{
    struct tree *tmp = (struct tree *)malloc(sizeof(struct tree));
    if(tmp != NULL)
    {
        tmp->data = a;
        tmp->left = NULL;
        tmp->right = NULL;
    }
    else
        printf("\nОшибка выделения памяти на листья дерева\n");
    return tmp;
}



void printTree (struct tree *root, int n)
{
    if(root == NULL) return;
    n += 10;
    printTree(root->right, n);
    for(int i = 10; i < n; i++)
        printf("\t");
    printTree(root->left, n);
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
void input2DString (char*** text, int* n)
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

void readIn2DString (char*** text, int* n)
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

void output2DNumbers (long** mas, long n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\n");
        for(int j = 0; j < mas[i][0]; j++)
            printf("%ld ", mas[i][j]);
    }
}














