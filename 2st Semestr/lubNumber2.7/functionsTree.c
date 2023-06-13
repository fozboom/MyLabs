#include "headerTree.h"
#include "../myLibrary.h"

//функция проверки элемента на то, является ли он оператором
int isOperator (char s)
{
    if (s == '+' || s == '-' || s == '*' || s == '/')
        return 1;
    return 0;
}



//функции проверки элемента на то, является ли он числом
int isNumber (char s)
{
    if (s >= '0' && s <= '9')
        return 1;
    return 0;
}



//функция проверки ASCII кода, является ли он оператором
int check (int x)
{
    if (x == 42 || x == 43 || x == 45 || x == 47)
        return 0;
    return 1;
}



//функция поиска числа в строке (atoi)
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



//функция создания дерева из польской нотации
struct tree * polishToTree (char * mas)
{
    int n = strlen(mas), top = -1;                              //top - параметр по массиву указателей stack,
    struct tree * stack[SIZE], * tmp;
    for (int i = 0; i < n; i++)
    {
        if (isNumber(mas[i]))                                   //если число, создаю узел и заношу его в массив
        {
            stack[++top] = makeNode(poiskNumber(mas, &i));
        }
        if (isOperator(mas[i]))                                 //если встретил оператор
        {
            tmp = makeNode((int)mas[i]) ;                     //создаю узел tmp, который хранит ASCII код оператора
            tmp->left = stack[top--];                              //потомками tmp являются два числа из массива
            tmp->right = stack[top--];
            stack[++top] = tmp;                                    //новый узел заношу в массив
        }
    }
    return stack[top];
}



//функция вычисления дерева
int calculateTree (struct tree * root)
{
    if(check(root->data))                           //если встретил число, вернуть его
        return root->data;
    int num1 = calculateTree(root->left);        //num1 - первое число, num2 - второе число
    int num2 = calculateTree(root->right);
    if (isOperator(root->data))                     //если встретил оператор, выполняю соответствующею операцию
    {
        switch (root->data)
        {
            case '+':
                return num1 + num2;
            case '-':
                return num1 - num2;
            case '*':
                return num1 * num2;
            case '/':
                return num1 / num2;

        }
    }
    else                                                //в случае ошибки вернуть 0
    {
        return 0;
    }
}



//функция создания нового узла дерева
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
        printf("\nОшибка при создании нового узла\n");
        return NULL;
    }

}



//функция добавления нового узла в дерево
void addNode (struct tree * tmp, struct tree ** root)
{
    if (*root == NULL)                              //если нашел нужное место, добавляю элемент
    {
        *root = tmp;
    }
    else if (tmp->data < (*root)->data)             //если элемент меньший, ухожу в левое поддерево
    {
        addNode(tmp, &(*root)->left);
    }
    else if (tmp->data > (*root)->data)             //если элемент больший, ухожу в правое поддерево
    {
        addNode(tmp, &(*root)->right);
    }
    else
    {
        printf("\nТакое число уже есть в дереве\n");
    }
}



//функция поиска элемента в дереве
void findNode (int info, struct tree * root)
{
    if(root == NULL)                                                //проверка на пустое дерево
    {
        printf("\033[3;41mДерево пустое\033[0m\n");
        return;
    }
    struct tree * tmp = root;                                       //вспомогательный указатель для обхода дерева
    while (tmp != NULL)
    {
        if (tmp->data == info)                                      //если нашел элемент, вывожу его
        {
            printTree(root, 0, 0, tmp->data);
            return;
        }
        else if (info < tmp->data)                                  //если элемент меньше текущего узла дерева, ухожу влево
        {
            tmp = tmp->left;
        }
        else if (info > tmp->data)                                  //если элемент больше текущего узла дерева, ухожу вправо
        {
            tmp = tmp->right;
        }
    }
    printf("\033[3;41mТакого элемента в дереве нет\033[0m\n");
}



//функция удаления узла из дерева
void deleteNode (struct tree ** root, int info)
{
    if (*root == NULL)                                          //если элемента нет, вывести ошибку
    {
        printf("\nВ дереве нет элемента '%d'\n", info);
        return;
    }

    if ((*root)->data > info)                                   //если элемент меньше текущего узла дерева, ухожу влево
    {
        deleteNode(&(*root)->left, info);
    }
    else if ((*root)->data < info)                              //если элемент больше текущего узла дерева, ухожу вправо
    {
        deleteNode(&(*root)->right, info);
    }
    else if ((*root)->data == info)                             //если нашел узел
    {
        struct tree * tmp;                                      //вспомогательный указатель для очистки памяти
        if((*root)->right == NULL)                              //если правое поддерево пустое, левое поддерево становится на это место
        {
            tmp = *root;
            (*root) = (*root)->left;
            free(tmp);
        }
        else if((*root)->left == NULL)                          //если левое поддерево пустое, правое поддерево становится на это место
        {
            tmp = *root;
            (*root) = (*root)->right;
            free(tmp);
        }
        else                                                    //если есть два потомка
        {
            tmp = (*root)->left;                                //ищу в левом поддереве свободное место в правой части
            while(tmp->right != NULL)
            {
                tmp = tmp->right;
            }
            tmp->right = (*root)->right;                        //присоединяю в найденное место правую часть удаляемого дерева
            tmp = (*root);
            (*root) = (*root)->left;
            free(tmp);

        }
    }
}



// Функция для вывода бинарного дерева
void printTree(struct tree * root, int space, bool position, int info)
{
    //space - кол-во отступов, position - определение, какая это ветка (левая или правая), info - число, которое надо вывести цветным
    if (root == NULL)
        return;
    printTree(root->right, space + 1, false, info);      //вывод правого поддерева
    for (int i = 0; i < space; i++)
        printf("    ");
    if (!position)
        printf("┌───");
    else
        printf("└───");
    if (isOperator(root->data))
        printf("\033[3;32m %c\033[0m\n", (char)root->data);
    else if (root->data == info)
        printf("\033[3;41m %d\033[0m\n", root->data);
    else
        printf("%d\n", root->data);
    printTree(root->left, space + 1, true, info);        //вывод левого поддерева
}



//функция создания дерева из массива чисел
void createTree (struct tree ** root, int * mas, int n)
{
    if (*root != NULL)
    {
        printf("\nБинарное дерево уже создано\n");
        return;
    }
    struct tree * tmp;
    for(int i = 0; i < n; i++)
    {
        tmp = makeNode(mas[i]);
        addNode(tmp, root);
    }
}



//функция сохранения текста в текстовый файл
void serializeTextFile (struct tree * root, FILE * file)
{
    if (root == NULL)
    {
        fprintf(file, "-1 ");                           //значение NULL сохраняю как -1
        return;
    }
    //сохраняю информацию через прямой обход дерева
    fprintf(file, "%d ", root->data);
    serializeTextFile(root->left, file);
    serializeTextFile(root->right, file);
}



//функция сохранения текста в бинарный файл
void serializeBinaryFile (struct tree * root, FILE * file)
{
    if (root == NULL)
    {
        int x = -1;                                     //значение NULL сохраняю как -1
        fwrite(&x, sizeof(int), 1, file);
        return;
    }
    //читаю информацию, сохраненную прямым обходом
    fwrite(&(root->data), sizeof(int), 1, file);
    serializeBinaryFile(root->left, file);
    serializeBinaryFile(root->right, file);
}



//функция чтения информации из текстового файла
struct tree * deserializeTextFile (FILE * file)
{
    //читаю информацию, сохраненную прямым обходом
    int data;
    if (fscanf(file, "%d", &data) == 1)
    {
        if (data == -1)                             //значение -1 обозначает NULL
            return NULL;
        struct tree * root = makeNode(data);
        root->left = deserializeTextFile(file);
        root->right = deserializeTextFile(file);
        return root;
    }
    return NULL;
}



//функция чтения информации из бинарного файла
struct tree * deserializeBinaryFile (FILE * file)
{
    //читаю информацию, сохраненную прямым обходом
    int data;
    if (fread(&data, sizeof(int), 1, file) == 1)
    {
        if (data == -1)                             //значение -1 обозначает NULL
            return NULL;
        struct tree * root = makeNode(data);
        root->left = deserializeBinaryFile(file);
        root->right = deserializeBinaryFile(file);
        return root;
    }
    return NULL;
}


//функция меню сохранения в файл
void saveTreeToFile(struct tree * root)
{
    int choice;
    char* fileName;
    printf("\nВ какой файл вы хотите сохранить дерево?");
    printf("\n0 - текстовый файл");
    printf("\n1 - бинарный файл\n");
    inputInt(&choice, 0, 1);
    printf("\nВведите имя файла: ");
    inputStr(&fileName);
    FILE *file = fopen(fileName, choice == 1 ? "wb" : "wt");
    if (file == NULL)
    {
        printf("\nНе удалось открыть файл для записи");
        return;
    }
    if (!choice)
    {
        serializeTextFile(root, file); // Сохраняем в текстовый файл
    }
    else if (choice)
    {
        serializeBinaryFile(root, file); // Сохраняем в бинарный файл
    }
    fclose(file);
}



//функция меню чтения данных из файла
struct tree *loadTreeFromFile()
{
    int choice;
    char* fileName;
    printf("\nИз какого файла вы хотите прочитать дерево?");
    printf("\n0 - текстовый файл");
    printf("\n1 - бинарный файл\n");
    inputInt(&choice, 0, 1);
    printf("\nВведите имя файла: ");
    inputStr(&fileName);
    FILE *file = fopen(fileName, choice == 1 ? "rb" : "rt");
    if (file == NULL)
    {
        printf("\nНе удалось открыть файл для чтения");
        return NULL;
    }
    struct tree *root = NULL;
    if (!choice)
    {
        root = deserializeTextFile(file); // Загружаем из текстового файла
    }
    else if (choice)
    {
        root = deserializeBinaryFile(file); // Загружаем из бинарного файла
    }
    fclose(file);
    return root;
}



//обход в прямом порядке
void pre_Order (struct tree * root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    pre_Order(root->left);
    pre_Order(root->right);
}



//обход дерева в симметричном порядке
void in_Order (struct tree * root)
{
    if (root == NULL)
    {
        return;
    }
    in_Order(root->left);
    printf("%d ", root->data);
    in_Order(root->right);
}



//обход дерева в обратном порядке
void post_Order (struct tree * root)
{
    if (root == NULL)
    {
        return;
    }
    post_Order(root->left);
    post_Order(root->right);
    printf("%d ", root->data);
}



//функция обхода дерева в ширину
void caseBFT (struct tree * root)
{
    if (root == NULL)
    {
        printf("\033[3;41mДерево пустое\033[0m\n");
        return;
    }
    struct tree * FIFO[SIZE];               //массив указателей
    int head = 0, tail = 0;                 //head - первый элемент, tail - крайний элемент
    FIFO[tail++] = root;
    while (head < tail)                     //пока не обошел весь массив
    {
        struct tree * tmp = FIFO[head];     //создаю временный указатель, указывающий на первый элемент массива
        printf("%d ", tmp->data);           //вывожу элемент
        if (tmp->left != NULL)              //заношу левое поддерево в массив
        {
            FIFO[tail++] = tmp->left;
        }
        if (tmp->right != NULL)
        {
            FIFO[tail++] = tmp->right;      //заношу правое дерево в массив
        }
        head++;                             //перехожу к следующему элементу
    }
}


//функция меню выбора задачи
void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound)
{
    char* task = NULL;
    printf("\nВыберите действие:\n");
    printf("\033[30;42m 'create'\033[0m - создать дерево\n");
    printf("\033[30;42m 'read'\033[0m - прочитать дерево из файла\n");
    printf("\033[30;42m 'polishTree'\033[0m - подсчет математического выражения через дерево\n");
    printf("\033[30;42m 'add'\033[0m - добавить элемент в дерево\n");
    printf("\033[30;42m 'delete'\033[0m - удалить элемент из дерева\n");
    printf("\033[30;42m 'find'\033[0m - найти число в дереве\n");
    printf("\033[30;42m 'preOrder'\033[0m - прямой обход дерева\n");
    printf("\033[30;42m 'inOrder'\033[0m - симметричный обход дерева\n");
    printf("\033[30;42m 'postOrder'\033[0m - обратный обход дерева\n");
    printf("\033[30;42m 'BFT'\033[0m - обход дерева в ширину\n");
    printf("\033[30;42m 'save'\033[0m - сохранение дерева в файл\n");
    printf("\033[30;42m'finish'\033[0m - завершить программу\n");
    rewind(stdin);
    inputStr(&task);
    for(*doTask = create; *doTask < finish; (*doTask)++)
    {
        if(strcmp(task, tasks[*doTask]) == 0)
        {
            *taskIsFound = true;
            break;
        }
    }
    free(task);
}


//функция меню добавления элемента в дерево
void caseAdd (struct tree ** root)
{
    int x;
    printf("\nВведите число, которое надо добавить - ");
    inputInt(&x, 0, 100000);
    struct tree * tmp = makeNode(x);
    addNode(tmp, root);
    printTree(*root, 0, 0, x);
}


//функция меню удаления элемента из дерева
void caseDelete (struct tree ** root)
{
    int x;
    printf("\nВведите число, которое надо удалить - ");
    inputInt(&x, 0, 100000);
    deleteNode(root, x);
    printTree(*root, 0, 0, -1);
}



//функция меню создания дерева из массива
void caseCreate (struct tree ** root, int ** mas, int * n)
{
    inputIntMas(mas, n);
    createTree(root, *mas, *n);
    printTree(*root, 0, 0, -1);
}



//функция меню вычисления выражения через дерево
void casePolishTree (char ** str, struct tree ** root, int * result)
{
    freeTree(*root);
    char* polishStr;
    inputStr(str);
    polishStr = writeToPolish(*str);
    *root = polishToTree(polishStr);
    printf("\nВыражение, записанное польской нотацией:\n");
    outputString(polishStr); printf("\n\n\n");
    printTree(*root, 0, 0, -1);
    *result = calculateTree(*root);
    printf("\nРезультат вычисления данного выражения result = %d", *result);
}



//функция меню нахождения элемента в дереве
void caseFind (struct tree * root)
{
    int x;
    printf("\nВведите число, которое хотите найти в дереве - ");
    inputInt(&x, 0, 100000);
    findNode(x, root);
}



//функция меню удаления дерева
void caseDeleteTree (struct tree ** root)
{
    free(*root);
    *root = NULL;
    printf("\nДерево успешно очищено");
}



//функция очистки памяти
void freeTree (struct tree * root)
{
    if(root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}





