#include "headerStack.h"
#include "../myLibrary.h"


//функция проверки правильности расставленных скобок и исправления ошибок
void taskBrackets (char* mas)
{
    struct FILO* head = NULL;                                   //head - голова стека
    union hold info;                                            //info - объединение, которое хранит число или символ
    for (int i = 0; mas[i] != '\0'; i++)                        //цикл по выражению
    {
        char s = mas[i];
        if (s == '(' || s == '{' || s == '[')                   //если встретил открывающую скобку, заношу ее в стек
        {
            info.symbol = s;                                    //считываю в объединение
            push(&head, info);                                  //заношу в стек
            head->index = i;                                    //заношу также индекс, под которым эта скобка находится, чтобы можно было удалить
        }
        else if (s == ')' || s == '}' || s == ']')              //если встречаю закрывающую скобку, проверяю, что в стеке
        {
            if (head == NULL)                                   //если стек пустой, значит в выражении лишняя закрывающая скобка
            {
                mas[i] = ' ';                                   //удаляю лишнюю скобку
            }
            else if ((s == ')' && head->data.symbol != '(') ||
                     (s == '}' && head->data.symbol != '{') ||
                     (s == ']' && head->data.symbol != '['))
            {
                mas[i] = getBracket(head->data.symbol);      //если скобки разного типа, заменяю их
                popStruct(&head);

            }
            else                                                //если скобки одинаковые, удаляю открывающую скобку из стека
            {
                popStruct(&head);                               //функция удаления скобки из стека
            }
        }
    }
    while (head != NULL)                                        //если стек не пустой, значит в выражении лишняя открывающая скобка
    {
        mas[head->index] = ' ';                                 //удаляю лишнюю скобку
        popStruct(&head);
    }
    outputString(mas);                                          //вывод выражения на экран
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





//функция вычисления выражения записанного обратной польской нотацией
int calculateMath (char* str)
{
    char* mas = writeToPolish(str);
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
    return result.number;
}




//функция перевода числа в любую систему счисления
char* translateDecimal (char *num)
{
    char* newStr;                                   //newStr - строка, записанная польской нотацией для подсчетов
    int system, decimal, flag = 0, n;               //system - новая с/с, decimal - рез-т мат выр-я, flag - переменная для обозначения отрицательного числа
    newStr = writeToPolish(num);               //запись выражения польской нотацией
    decimal = calculateMath(newStr);            //вычисления мат выражения
    if(decimal <= 0)                                //если число отрицательное, делаем его положительным
    {
        flag = 1;                                   //помечаю, что потом его нужно обратно сделать отрицательным
        decimal *= -1;
    }
    printf("\nВведите систему счисления, в которую надо перевести  число: ");
    inputInt(&system, 2, 16);               //ввод новой системы счисления
    num = convertFromDecimal(decimal, system);  //перевод числа в новую систему счисления
    if (flag)                                        //если число было отрицательным, возвращаем минус путем сдвигов
    {
        n = sizeof(num) + 1;                         //добавляем место для минуса
        num = (char*)realloc(num, n * sizeof(char));
        for(int i = n-1; i > 0; i--)                 //цикл по выражению для сдвига вправо
        {
            num[i] = num[i-1];
        }
        num[0] = '-';                                //первый элемент - минус
    }
    outputString(num);                          //вывод числа на экран
    return num;
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








char getBracket (char s)
{
    if (s == '(')
    {
        return ')';
    }
    else if (s == '[')
    {
        return ']';
    }
    else
    {
        return '}';
    }

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

void choiceTask (enum commands *doTask, const char* tasks[], bool *taskIsFound)
{
    char* task = NULL;
    printf("\nВыберите действие:\n");
    printf("'polish' - записать выражение польской нотацией\n");
    printf("'calculate' - посчитать значение выражения\n");
    printf("'convert' - перевести в другую систему счисления\n");
    printf("'finish' - посчитать значение выражения\n");
    inputStr(&task);
    for(*doTask = polish; *doTask < finish; (*doTask)++)
    {
        if(strcmp(task, tasks[*doTask]) == 0)
        {
            *taskIsFound = true;
            break;
        }
    }
}

char* convertFromDecimal (int num, int system)
{
    struct FILO *head = NULL;
    const char digits[] = "0123456789ABCDEF";
    char* result = (char*)calloc(100, sizeof(char));
    union hold data;
    int i = 0;
    while (num > 0) {
        data.number = num % system;
        push(&head, data);
        num /= system;
    }
    while (head != NULL)
    {
        data = popStruct(&head);
        result[i++] = digits[data.number];
    }
    result = (char*)realloc(result, (++i) * sizeof(char));
    result[i-1] = '\0';
    return result;
}



void checkMath (char* str)
{
    int n = strlen(str);
    for(int i = 0; i < n; i++)
    {
        if ((!ifOperator(str[i])) && (!ifNumber(str[i])) && (ifBracket(str[i])))
        {
            exit(EXIT_FAILURE);
        }
    }
}

int ifBracket (char s)
{
    if (s == '{' || s == '}' || s == '[' || s == ']')
        return 1;
    return 0;
}













