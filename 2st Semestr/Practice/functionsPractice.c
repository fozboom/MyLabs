#include "headerPractice.h"
#include "../myLibrary.h"


//////////////////////////////////////////////////////функции для шифрования алгоритмом RSA////////////////////////////

//функция проверки числа на простоту
long isPrimes (long x)
{
    if(x == 0) return 0;
    for(int i = 2; i < x; i++)
        if (x%i == 0) return 0;
    return 1;
}


//функция создания простого числа
void createPrime (long *x)
{
    srand(time(NULL));
    *x = rand()%10;
    *x = (*x)*(*x) - (*x) + 41;
}


//функция создания чисел p, q, n, fi
void createNumbers (long *p, long *q, long *n, long *fi)
{
    createPrime(p);                      //создать простое число p

    do
    {
        createPrime(q);                  //создать простое число q, не равное p
    }while(*q == *p);

    *n = (*p) * (*q);                       //создать число n - часть приватного и публичного ключа
    *fi = ((*p) - 1)*((*q) - 1);            //создать число fi, которое будем нужно для создания ключей

}



//функция создания числа e - части открытого ключа
void createEilerNumber (long *e, long fi)
{
    do                                      //создать простое число e, взаимно простое с fi, e >= fi
    {
        createPrime(e);
    }while(NOD(*e, fi) != 1 && *e >= fi);
}



//функция нахождения НОД алгоритмом Евклида
long NOD (long x, long y)
{
    if (y == 0)
        return x;
    else
        return NOD (y, x%y);
}



//расширенный алгоритм Евклида для нахождения обратного по модулю числа
void search_d(long* x, long e, long fi)
{
    long m0 = fi;                                       //сохраняю значение fi для восстановления отрицательного результата
    long y = 0, xPrev = 1;                              //инициализирую начальные значения коэффициентов

    while (e > 1)
    {
        long q = e / fi;                                //вычислить частное от деления e на fi
        long t = fi;                                    //временная переменная для сохранения значения fi

        fi = e % fi;                                    //вычисля остаток от деления e на fi
        e = t;                                          //обновить значение e для следующей итерации
        t = y;                                          //сохранить предыдущее значение y

        y = xPrev - q * y;
        xPrev = t;
    }
    if (xPrev < 0)
    {
        xPrev += m0;                                    //если результат отрицательный, сделать положительным
    }
    *x = xPrev;
}



//функция бинарного возведения в степень по модулю
long powerMod(long x, long y, long n)
{
    if(y == 0)
        return 1;                                       //при y=0 вернуть 1
    if (y%2 == 0)                                       //если степень четная, рекурсивно вызвать для степени y/2
    {
        long z = powerMod(x, y/2, n);
        return (z*z)%n;                                 //вернуть остаток от деления
    }
    else
        return (x * powerMod(x, y-1, n))%n;         //если степень нечетная, рекурсивно вызвать возведение для y-1
}



//функция кодирования текста алгоритмом RSA
long** coding (char** mas, long e, long n, long rows)
{
    if (mas == NULL)                                                           //проверка, ввел ли пользователь текст
    {
        printf("\nВы не ввели текст, который надо зашифровать\n");
        return NULL;
    }
    long **cods = (long **)calloc(rows, sizeof(long*));             //выделить память на двумерный массив с закодированным текстом
    for(int j = 0; j < rows; j++)                                              //цикл по строкам
    {
        int k = 1;                                                             //k - позиция с которой начинается запись
        long size = strlen(*(mas + j));                                     //определяем длину строки
        *(cods + j) = (long *)calloc(size + 1, sizeof(long));       //выделяем память на строку
        cods[j][0] = size + 1;                                                 //записываю первым элементов кол-во элементов в строке
        for (int i = 0; mas[j][i] != '\0'; i++)                                //цикл по строке
        {
            long s = (long) (mas[j][i]);                                        //перевожу символ в ASCII - код
            cods[j][k] = powerMod(s, e, n);                               //кодирую символ
            k++;                                                                //переход на следующий элемент для записи
        }
    }
    return cods;
}



//функция декодирования текста алгоритмом RSA
char** decodingRSA(long** codeText, long d, long n, long rows)
{
    char** decodedText = (char**)malloc(rows * sizeof(char*));          //выделяю память для массива строк

    for (long i = 0; i < rows; i++)                                          //цикл по двумерному массиву
    {
        long cols = codeText[i][0];                                          //получаю кол-во элементов в строке

        decodedText[i] = (char*)malloc((cols + 1) * sizeof(char));      //выделяем память для строки (плюс 1 для символа '\0')

        for (long j = 1; j < cols; j++)                                      //цикл по массиву
        {
            long s = powerMod(codeText[i][j], d, n);                   //декодирую текущий элемент

            decodedText[i][j-1] = (char)s;                                   //преобразую числовое значение в символ
        }

        decodedText[i][cols] = '\0';
    }
    return decodedText;
}






//////////////////////////////////////////////////////функции для шифрования алгоритмом четырех квадратов////////////////////////////

//функция для создания квадрата
void writeBox(char box[SIZE][SIZE], int n)
{
    int k = 0;                                                      //индекс для записи букв в квадрат
    char* word = NULL;                                              //word - кодовое слово
    char letters[26] = "abcdefghijklmnopqrstuvwxyz";                //алфавит для заполнения квадрата
    int used[26] = {0}, flag;                                       //used отвечает за повторение букв, flag нужен для проверки кодового слова
    printf("\nПридумайте кодовое слово, в котором только строчные буквы");
    do
    {
        flag = 0;
        printf("\nВведите кодовое слово: ");
        inputStr(&word);                                        //считываю кодовое слово
        for (int i = 0; word[i] != '\0'; i++)                        //цикл для проверки на повторение букв и недопустимые символы
        {
            for (int j = i + 1; word[j - 1] != '\0'; j++)
            {
                if ((word[i] == word[j]) || !checkLetter(word[i])) //если есть повторение или недопустимый символ
                {
                    flag = 1;
                    break;
                }
            }

            if (flag) {break;}                                        //если флаг установлен в 1, прерываю и внешний цикл
        }
        if(flag) {printf("\n\033[1;41m\033[1mКодовое слово введено неверно\033[0m\n");}

    } while (flag);

    for (int i = 0; word[i] != '\0'; i++)                               //записываем буквы ключевого слова в квадрат
    {
        used[word[i] - 'a'] = 1;                                        //отмечаю букву как использованную
        box[k / SIZE][k % SIZE] = word[i];                              //записываю букву в квадрат
        k++;
    }


    for (int i = 0; i < 26; i++)                                        //записываю оставшиеся буквы алфавита в квадрат
    {
        if (used[letters[i] - 'a'] == 0)                                //если буква не была использована
        {
            box[k / SIZE][k % SIZE] = letters[i];                       //записываю букву в квадрат
            used[letters[i] - 'a'] = 1;                                 //отмечаю букву как использованную
            k++;
        }
    }
    pushRandom (box, ' ', 4, 2);                                //случайным образом вставляю символы
    pushRandom (box, ';', 4, 3);
    pushRandom (box, '!', 4, 4);
    pushRandom (box, '?', 4, 5);
    pushRandom (box, '.', 5, 0);
    pushRandom (box, ',', 5, 1);
    pushRandom (box, '(', 5, 2);
    pushRandom (box, ')', 5, 3);
    pushRandom (box, '-', 5, 4);
    pushRandom (box, ':', 5, 5);
    //outputBox(box, SIZE);

}

void outputBox (char** box, int n)
{
    for(int i = 0; i < n; i++)
    {
        printf("\n");
        for (int j = 0; j < n; j++)
        {
            printf("%c ", box[i][j]);
        }
    }
    printf("\n\n\n");
}



//кодирование текста алгоритмом четырех квадратов
char** codingSquare(char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char **text, int size)
{
    for(int c = 0; c < size; c++)                                       //цикл по строкам
    {
        int n = strlen(text[c]);                                     //получаю длину текста
        int i = 0, j = 0, k = 0, l = 0;                                 //переменные для хранения индексов букв

        if (strlen(text[c]) % 2 == 1)                                //если длина текста нечетная
        {
            n += 2;                                                     //расширяю строку
            char* tmp = (char*)realloc(text[c], (n) * sizeof(char));
            if (tmp != NULL)
            {
                text[c] = tmp;
                text[c][n - 2] = ' ';                                    //добавляю пробел перед дополнительными символами
                text[c][n - 1] = '\0';                                   //добавляю символ конца строки
            }
            else
            {
                printf("\n\033[1;41m\033[1mОшибка памяти\033[0m\n");
                exit(EXIT_FAILURE);
            }
        }
        for (int z = 0; z < n - 1; z++)
        {
            if (checkLetter(text[c][z]))                                //если символ является буквой
            {
                i = (text[c][z] - 'a') / SIZE;                             //вычисляю индекс строки в квадрате
                j = (text[c][z] - 'a') % SIZE;                             //вычисляю индекс столбца в квадрате
            } else
            {
                searchLetterIndex(box1, &i, &j, SIZE, text[c][z]); //ищу индексы символа в квадрате box1
            }
            z++;
            if (checkLetter(text[c][z]))                                //если символ является буквой
            {
                k = (text[c][z] - 'a') / SIZE;                             //вычисляю индекс строки в квадрате
                l = (text[c][z] - 'a') % SIZE;                             //вычисляю индекс столбца в квадрате
            } else
            {
                searchLetterIndex(box4, &k, &l, SIZE, text[c][z]); //ищу индексы символа в квадрате box4
            }
            char x1, x2;
            x1 = box2[i][l];                                                //получаю символ из квадрата box2
            x2 = box3[k][j];                                                //получаю символ из квадрата box3
            text[c][z - 1] = x1;                                            //заношу закодированные буквы в массив
            text[c][z] = x2;                                                //заношу закодированные буквы в массив
        }
    }
    return text;
}



//функция декодирования текста алгоритмом четырех квадратов
char** decodeSquare(char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char** text, long rows)
{
    for (int c = 0; c < rows; c++)                                                  //цикл по строкам
    {
        int i = 0, j = 0, k = 0, l = 0, n = strlen(text[c]);                     //инициализирую переменные и получаю длину текста
        for (int z = 0; z < n; z++)
        {
            searchLetterIndex(box2, &i, &j, SIZE, text[c][z]);           //ищу индексы символа в квадрате box2
            searchLetterIndex(box3, &k, &l, SIZE, text[c][z + 1]);  //ищу индексы символа в квадрате box3
            char x1 = box1[i][l];                                                   //получаю символ из квадрата box1
            char x2 = box4[k][j];                                                   //получаю символ из квадрата box4
            text[c][z] = x1;                                                        //делаю замены в исходном массиве
            text[c][z + 1] = x2;                                                    //делаю замены в исходном массиве
            z++;
        }
    }
    return text;
}



//функция проверки, является ли символ буквой
int checkLetter (char s)
{
    int flag = 1;
    if(s < 'a' || s > 'z')                              //если не строчная буква, вернуть 0, иначе 1
        flag = 0;
    return flag;
}



//функция вставки элемента в случайную позицию
void pushRandom(char box[SIZE][SIZE], char s, int i, int j)
{
    int l, m;
    srand(time(NULL));
    l = rand() % SIZE;                                  //генерирую случайную строку в квадрате
    m = rand() % SIZE;                                  //генерирую случайный столбец в квадрате

    char letter = box[l][m];                            //сохраняю символ, который будет заменен
    box[l][m] = s;                                      //заменяю символ случайной позиции на новый символ s
    box[i][j] = letter;                                 //заменяю символ в позиции (i, j) на сохраненный символ
}



//функция поиска индексов символа в квадрате
void searchLetterIndex (char box[SIZE][SIZE], int *i, int* j, int n, char s)
{
    int flag = 0;
    for ((*i) = 0; (*i) < n; (*i)++)                //цикл по строкам
    {
        for ((*j) = 0; (*j) < n; (*j)++)            //цикл по символам
        {
            if (box[(*i)][(*j)] == s)               //если нашел символ, выйти из двойного цикла
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1) {break;}
    }
}



//функция выбора команды
void choiceTask (enum choiceCommand *doTask, const char* tasks[], bool *taskIsFound)
{
    char* task = NULL;
    printf("\n\033[32m Выберите действие: \033[0m\n");
    printf("\033[3;34m input \033[0m - ввод текста, который необходимо закодировать\n");
    printf("\033[3;34m read \033[0m - считать текстК из файла\n");
    printf("\033[3;34m encoding \033[0m - закодировать текст\n");
    printf("\033[3;34m decoding \033[0m - раскодировать текст\n");
    printf("\033[3;34m save \033[0m - сохранить зашифрованный текст в файл\n");
    printf("\033[3;34m finish \033[0m - завершить программу\n");
    rewind(stdin);
    inputStr(&task);
    for(*doTask = input; *doTask < finish; (*doTask)++)
    {
        if(strcmp(task, tasks[*doTask]) == 0)
        {
            *taskIsFound = true;
            break;
        }
    }
}


void createKeyRSA (long *p, long* q, long*n, long* fi, long* e, long* d)
{
    do
    {
        printf("\nВведите простое число p - ");
        scanf("%ld", p);
    } while (!isPrimes(*p));
    do
    {
        printf("\nВведите простое число q - ");
        scanf("%ld", q);
    } while (!isPrimes(*q));
    *n = (*p) * (*q);
    *fi = ((*p) - 1) * ((*q) - 1);
    createEilerNumber(e, *fi);
    search_d(d, *e, *fi);
}



//функция чтения квадрата из файла
void readInfo(char box[SIZE][SIZE], int n, const char* name)
{
    FILE* file;
    char s;                                                     //символ в который считывается
    int j;                                                      //параметр по символам строки

    file = fopen(name, "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++)
    {
        j = 0;
        while ((s = getc(file)) != '\n' && !feof(file))         //читаю символы из файла до символа новой строки или конца файла
        {
            box[i][j] = s;                                      //сохраняю считанный символ в соответствующей ячейке массива `box`
            j++;
        }
    }

    fclose(file);
}




//////////////////////////////////////////Основные функции вызов функций для кодирования и декодирования/////////////////////////////////



//основная функция для кодирования текста
struct dataCode encodingText (char** text, int n, long ***codeText, char ***newText)
{
    struct dataCode key;                                                //key - новая структура хранящая данные о зашифрованном тексте
    char* task = NULL;                                                  //task - переменная для выбора задачи
    int choice;
    long p, q, fi;                                                      //p, q, fi - переменные для шифрования алгоритмом RSA
    long **code = (long**)calloc(n, sizeof(long*));          //code - двумерный массив кода алгоритмом RSA
    char **codingText = (char**)calloc(n, sizeof(char*));    //codingText - двумерный массив зашифрованного текста
    for(int i = 0; i < n; i++)
        *(codingText + i) = (char*)calloc(strlen(text[i]), sizeof(char));
    char box1[SIZE][SIZE], box2[SIZE][SIZE], box3[SIZE][SIZE], box4[SIZE][SIZE];
    printf("\nВведите название алгоритма, каким вы хотите закодировать текст");
    printf("\n'RSA' - закодировать алгоритмом RSA");
    printf("\n'Square' - закодировать алгоритмом четырех квадратов");
    do
    {
        printf("\nВведите название алгоритма: ");
        inputStr(&task);
        if (strcmp(task, "RSA") == 0)
        {
            key.flag = 1;                                               //помечаю, каким алгоритмом зашифровано
            printf("\nЧтобы сгенерировать ключ случайно, введите 0");
            printf("\nЧтобы сгенерировать ключ вручную, введите 1\n");
            inputInt(&choice, 0, 1);                           //выбор, как создать ключ
            if (choice)
            {
                do                                                      //создаю нужные числа для шифрования RSA
                {
                    printf("\nВведите простое число p - ");
                    scanf("%ld", &p);
                } while (!isPrimes(p));                              //создаю число p
                do
                {
                    printf("\nВведите простое число q - ");
                    scanf("%ld", &q);
                } while (!isPrimes(q));                               //создаю число q
                key.n = p * q;                                           //создаю n - модуль для расшифровки
                fi = (p - 1) * (q - 1);                                  //создаю функцию Эйлера, чтобы создать e и d
                createEilerNumber(&(key.e), fi);                         //создаю e - открытую экспоненту
                search_d(&(key.d), key.e, fi);                        //создаю d - закрытую экспоненту
            }
            else                                                         //иначе сгенерировать ключи случайно
            {
                createNumbers(&p, &q, &key.n, &fi);                      //сгенерировать p, q, n и fi
                createEilerNumber(&key.e, fi);                           //создать закрытую экспоненту e
                search_d(&key.d, key.e, fi);                          //создать число d - часть закрытого ключа
            }
            printf("\nОткрытый ключ: {%ld, %ld}, закрытый ключ: {%ld, %ld} ", key.n, key.e, key.n, key.d);
        }



        else if (strcmp(task, "Square") == 0)
        {
            key.flag = 0;
            readInfo(box1, SIZE, "box1.txt");               //считать box1, box4 из файла
            readInfo(box4, SIZE, "box4.txt");
            writeBox(box2, SIZE);                                 //сгенерировать box2 и box3 пользователем
            writeBox(box3, SIZE);
            for (int i = 0; i < SIZE; i++)                                //сохранить ключи (box2) в структуру
                for(int j = 0; j < SIZE; j++)
                    key.box2[i][j] = box2[i][j];
            for (int i = 0; i < SIZE; i++)                                //сохранить ключи (box3) в структуру
                for(int j = 0; j < SIZE; j++)
                    key.box3[i][j] = box3[i][j];
        }
        else
        {
            printf("\nНазвание алгоритма неверное");
            key.flag = 2;
        }
    }while(key.flag == 2);

    if (key.flag)
    {
        code = coding(text, key.e, key.n, n);                   //закодировать текст алгоритмом RSA
        output2DNumbers(code, n);                                     //вывести закодированный текст на экран
        codingText = NULL;                                                 //указатель на другой массив поставить в NULL
    }
    else
    {
        codingText = codingSquare(box1, box2, box3, box4, text, n);   //закодировать текст алгоритмом четырех квадратов
        output2DString(codingText, n);                                //вывести закодированный текст на экран
        code = NULL;                                                       //указатель на другой массив поставить в NULL
    }
    *newText = codingText;
    *codeText = code;
    return key;
}



//декодирование текста из файла
char** decodingTextFromFile(long** codeText, char** newText, struct dataCode* keys, int count, char box[SIZE][SIZE], long* rows)
{
    int flag = 0;                                       //flag - флаг для проверки наличия файла
    int i;
    char **text = NULL;                                 //text - расшифрованный текст
    char* fileName = NULL;                              //fileName - имя файла для расшифровки

    printf("\nВведите имя файла, который необходимо расшифровать: ");
    inputStr(&fileName);                           //ввод имени файла для расшифровки

    for (i = 0; i < count; i++)                         //проверка, есть ли файл с таким именем в массиве структур
    {
        if (strcmp(fileName, keys[i].fileName) == 0)
        {
            flag = 1;
            break;
        }
    }

    if (flag)                                                                   //если файл найден
    {
        FILE* file;
        file = fopen(keys[i].fileName, "rt");
        if (file != NULL)
        {
            int dataType = keys[i].flag;                                        //dataType -  тип данных: 1 - long, 0 - char
            if (dataType == 1)
            {
                codeText = loadNumberFromFile(codeText, rows, fileName);   //загрузка числовых данных из файла
                text = decodingRSA(codeText, keys[i].d, keys[i].n, *rows);       //расшифровка алгоритмом RSA

            }
            else if (dataType == 0)
            {
                newText = loadTextFromFile(rows, fileName);                      //загрузка текстовых данных из файла
                text = decodeSquare(box, keys[i].box2, keys[i].box3, box, newText, *rows);
            }                                                                    //расшифровка методом четырех квадратов
            fclose(file);
        }
        else
        {
            printf("\nОшибка при открытии файла для чтения\n");
        }
    }
    else
    {
        printf("\nФайл с таким именем не найден\n");
    }
    return text;
}




//функция декодирования текста, введенного с клавиатуры
char** decodingInputText(char box[SIZE][SIZE], long* rows)
{
    char* string;                               //string - строка для выбора алгоритма шифрования
    char** text;                                //text - текст для расшифровки
    char* name1, *name2;                        //имя файлов для хранения ключей box2 и box3
    char box2[SIZE][SIZE], box3[SIZE][SIZE];    //ключи для шифрования алгоритмом четырех квадратов
    long** code;                                //числовое представление текста для алгоритма RSA
    long d, n;                                  //ключи для расшифровки алгоритма RSA
    int flag = 0;                               //flag - флаг для проверки корректного ввода

    do
    {
        printf("\nКаким алгоритмом зашифрован текст? (RSA или Square)\n");
        inputStr(&string);                 //ввод алгоритма шифрования

        if (strcmp("RSA", string) == 0 || strcmp("Square", string) == 0)
        {
            flag = 1;
        }
        else
        {
            printf("\n\033[3;31m Команда введена неверно, попробуйте еще раз \\033[0m");
        }
    } while (!flag);

    if (strcmp("RSA", string) == 0)
    {
        printf("\nВведите через пробел цифры, которыми закодирована каждая буква");
        input2DString(&text, rows);                         //ввод закодированного текста
        code = myAtoi2DText(text, *rows);                      //преобразование текста в числовое представление
        printf("\nВведите ключ для расшифровки\nВведите число d - ");
        inputLong(&d, 0, 10000);                      //ввод значения d
        printf("Введите число n - ");
        inputLong(&n, 0, 10000);                      //ввод значения n
        text = decodingRSA(code, d, n, *rows);        //расшифровка текста с использованием RSA
    }
    else
    {
        printf("\nВведите закодированный текст\n");
        input2DString(&text, rows);                        //ввод закодированного текста
        printf("\nВведите имя файла, в котором хранится box2 - ");
        inputStr(&name1);                                //ввод имени файла для box2
        readInfo(box2, SIZE, name1);            //чтение информации из файла в box2
        printf("\nВведите имя файла, в котором хранится box3 - ");
        inputStr(&name2);                                //ввод имени файла для box3
        readInfo(box3, SIZE, name2);            //чтение информации из файла в box3
        text = decodeSquare(box, box2, box3, box, text, *rows);
    }                                                         // расшифровка текста методом четырех квадратов

    return text;
}

///////////////////////////////////////////////////////Функции работы с файлами////////////////////////////////////////


//функция сохранения массива структур с данными о зашифрованных файлах в бинарный файл
void saveStructInfo (struct dataCode* key, long count)
{
    FILE* file;
    file = fopen("keyInfo", "wb");
    if (file != NULL)
    {
        fwrite(&count, sizeof(long), 1, file);              //записываю кол-во элементов в массиве структур
        fwrite(key, sizeof(struct dataCode), count, file);  //записываю весь массив структур
    }
    else
        printf("\n\033[1;41m\033[1m\nОшибка при открытии бинарного файла для записи ключей\033[0m");
    fclose(file);
}



//функция чтения массива структур с данными о зашифрованных файлах
void readStructInfo(struct dataCode** key, long* count)
{
    FILE* file;
    file = fopen("keyInfo", "rb");
    if (file != NULL)
    {
        fread(count, sizeof(long), 1, file);                //считываю количество элементов
        *key = (struct dataCode*)calloc((*count), sizeof(struct dataCode));   //Выделяем память для массива структур
        fread(*key, sizeof(struct dataCode), *count, file); //Считываю массив структур
        fclose(file);
    }
    else
        printf("\n\033[1;41m\033[1m\nОшибка при открытии бинарного файла для чтения ключей\033[0m");
}



//функция сохранения двумерного массива чисел в файл
void saveNumberToFile(long** code, long rows, char* fileName)
{
    int format;                                         //переменная для выбора формата: бинарный или текстовый

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format)
    {
        file = fopen(fileName, "wt");               //открываю текстовый файл для записи
        if (file != NULL)
        {
            fprintf(file, "%ld\n", rows);                 //записываю количество строк

            for (long i = 0; i < rows; i++)               //цикл по двумерному массиву
            {
                long cols = code[i][0];                   //получаю количество элементов в текущей строке
                fprintf(file, "%ld ", cols);              //записываю количество элементов

                for (long j = 1; j <= cols; j++)          //цикл по строке двумерного массива
                {
                    fprintf(file, "%ld ", code[i][j]);    //Записываю элементы строки
                }

                fprintf(file, "\n");
            }

            fclose(file);
        }
        else
        {
            printf("\nОшибка при открытии текстового файла для записи кода\n");
        }
    }
    else
    {
        file = fopen(fileName, "wb");                                           //открываю бинарный файл для записи
        if (file != NULL)
        {
            fwrite(&rows, sizeof(long), 1, file);               //записываю количество строк

            for (long i = 0; i < rows; i++)
            {
                long cols = code[i][0];                                                //получаю количество элементов в текущей строке
                fwrite(&cols, sizeof(long), 1, file);           //записываю количество элементов

                for (long j = 1; j <= cols; j++)                                       //цикл по строке двумерного массива чисел
                {
                    fwrite(&code[i][j], sizeof(long), 1, file); //записываю элементы строки
                }
            }
            fclose(file);
        }
        else
        {
            printf("\nОшибка при открытии бинарного файла для записи кода\n");
        }
    }
}



long** loadNumberFromFile(long** code, long* rows, char* fileName)
{
    int format;                             //переменная для выбора типа файла: бинарный или текстовый

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format)                                                          //если текстовый файл
    {
        file = fopen(fileName, "rt");                               //открываю текстовый файл для чтения
        if (file != NULL)
        {
            if (fscanf(file, "%ld", rows) == 1)                            //читаю количество строк из файла
            {
                code = (long**)malloc((*rows) * sizeof(long*));       //выделяю память под массив строк

                for (long i = 0; i < *rows; i++)
                {
                    long cols;
                    if (fscanf(file, "%ld", &cols) == 1)                    //читаю количество элементов в текущей строке
                    {
                        code[i] = (long*)malloc((cols + 1) * sizeof(long)); //выделяю память под элементы строки
                        code[i][0] = cols;                                  //сохраняю количество элементов в первом элементе строки

                        for (long j = 1; j <= cols; j++)
                        {
                            fscanf(file, "%ld", &code[i][j]);               //читаю элементы строки из файла
                        }
                    }
                    else
                    {
                        printf("Ошибка чтения файла\n");
                        fclose(file);
                        return NULL;
                    }
                }
            }
            else
            {
                printf("Ошибка чтения файла\n");
            }

            fclose(file);
        }
        else
        {
            printf("Ошибка при открытии текстового файла для чтения\n");
        }
    }
    else
    {
        file = fopen(fileName, "rb");                                       //открываю бинарный файл для чтения
        if (file != NULL)
        {
            if (fread(rows, sizeof(long), 1, file) == 1)    //читаю количество строк из файла
            {
                code = (long**)malloc((*rows) * sizeof(long*));               //выделяю память под массив строк

                for (long i = 0; i < *rows; i++)
                {
                    long cols;
                    if (fread(&cols, sizeof(long), 1, file) == 1) //читаю количество элементов в текущей строке
                    {
                        code[i] = (long*)malloc((cols + 1) * sizeof(long));    //выделяю память под элементы строки
                        code[i][0] = cols;                                          //сохраняю количество элементов в первом элементе строки

                        for (long j = 1; j <= cols; j++)
                        {
                            if (fread(&code[i][j], sizeof(long), 1, file) != 1)
                            {                                                       //читаю элементы строки из файла
                                printf("Ошибка чтения файла\n");
                                fclose(file);
                                return NULL;
                            }
                        }
                    }
                    else
                    {
                        printf("Ошибка чтения файла\n");
                        fclose(file);
                        return NULL;
                    }
                }
            }
            else
            {
                printf("Ошибка чтения файла\n");
            }

            fclose(file);
        }
        else
        {
            printf("Ошибка при открытии бинарного файла для чтения\n");
        }
    }
    return code;
}



//функция сохранения текста в файл
void saveTextToFile(char** text, long rows, char* fileName)
{
    int format;                                 //переменная для определения типа файла

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format)
    {
        file = fopen(fileName, "w");        //открываю текстовый файл для записи
        if (file != NULL)
        {
            fprintf(file, "%ld\n", rows);         //записываю количество строк в текстовый файл

            for (long i = 0; i < rows; i++)
            {
                fprintf(file, "%s\n", text[i]);   //записываю строку в текстовый файл
            }
            fclose(file);
        }
        else
        {
            printf("Ошибка при открытии текстового файла для записи\n");
        }
    }
    else
    {
        file = fopen(fileName, "wb");                                   //открываю бинарный файл для записи
        if (file != NULL)
        {
            fwrite(&rows, sizeof(long), 1, file);       //записываю количество строк в бинарный файл

            for (long i = 0; i < rows; i++)
            {
                long len = strlen(text[i]);                                 //получаю длину строки
                fwrite(&len, sizeof(long), 1, file);    //записываю длину строки
                fwrite(text[i], sizeof(char), len, file); //записываю строку
            }

            fclose(file);
        }
        else
        {
            printf("Ошибка при открытии бинарного файла для записи\n");
        }
    }
}


//функция считывания текста в двумерный массив из файла
char** loadTextFromFile(long* rows, char* fileName)
{
    int format;                                             //переменная для определения типа файла

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format)
    {
        file = fopen(fileName, "r");                  //открываю текстовый файл для чтения
    }
    else
    {
        file = fopen(fileName, "rb");                 //открываю бинарный файл для чтения
    }

    if (file != NULL)
    {
        if (!format)
        {
            fscanf(file, "%ld\n", rows);                    //считываю количество строк
        }
        else
        {
            fread(rows, sizeof(long), 1, file); //считываю количество строк
        }

        char** text = (char**)malloc(*rows * sizeof(char*));      //выделяю память под двумерный массив
        if (text != NULL)
        {
            for (long i = 0; i < *rows; i++)
            {
                char buffer[MAX_LENGTH];                                //буфер для считывания строки
                if (!format)
                {
                    fgets(buffer, MAX_LENGTH, file);                    //считываю строку из текстового файла
                    int j = 0;
                    while (buffer[j] != '\n')
                        j++;
                    buffer[j] = '\0';                                   //удаляю \n заменяя на \0
                    text[i] = strdup(buffer);                       //выделяю память и копирую строку
                }
                else
                {
                    long len;
                    fread(&len, sizeof(long), 1, file);         //считываю длину строки
                    text[i] = (char*)malloc((len + 1) * sizeof(char));            //выделяю память для строки
                    fread(text[i], sizeof(char), len, file);    //считываю строку
                    text[i][len] = '\0';                                               //добавляю символ конца строки
                }
            }
        }
        else
        {
            printf("Ошибка при выделении памяти\n");
        }
        fclose(file);
        return text;
    }
    else
    {
        printf("\nФайл с таким именем не найден\n");
        return NULL;
    }
}



//функция перевода двумерного массива чисел в массив строк
long** myAtoi2DText(char** text, long rows)
{
    long** numbers = (long**)malloc(rows * sizeof(long*));      //выделяю память

    for (int i = 0; i < rows; i++)                                   //цикл по строкам
    {
        int count = 0;                                               //кол-во чисел в текущей строке

        char* copy = strdup(text[i]);                            //создаю копию строки с выделением памяти
        char* token = strtok(copy," " );                    //разбиваю строку на слова, чтобы посчитать кол-во слов
        while (token != NULL)
        {
            count++;
            token = strtok(NULL, " ");
        }
        free(copy);

        numbers[i] = (long*)malloc((count + 1) * sizeof(long));     //выделяю память под строку
        numbers[i][0] = count + 1;                                       //записываю первым элементов кол-во чисел в строке


        char* tokenPtr = strtok(text[i], " ");                  //разбиваю на слова
        int j = 1;
        while (tokenPtr != NULL)
        {
            numbers[i][j++] = atol(tokenPtr);                           //слово (число) преобразую в long
            tokenPtr = strtok(NULL, " ");
        }
    }
    return numbers;
}



////////////////////////Вспомогательные функции которые вызывают другие функции/////////////////////



//функция для кодирования текста
void caseEncoding (struct dataCode **keys, long *countKeys, long*** codeText, char** text, int n, char*** newText)
{
    (*countKeys)++;
    (*keys) = (struct dataCode*)realloc((*keys), (*countKeys) * sizeof(struct dataCode));   //расширяю массив структур
    *(*keys + (*countKeys) - 1) = encodingText(text, n, codeText, newText);                          //кодирую текст
    if((*keys + (*countKeys) - 1)->flag)                                                             //вывод на экран результата шифрования
        output2DNumbers(*codeText, n);
    else
        output2DString(*newText, n);
}



//функция для декодирования текста
void caseDecoding (char ***text, long **codeText, char **newText, struct dataCode *keys, long countKeys, char box1[SIZE][SIZE], long *rows)
{
    int format;
    printf("\nЧтобы расшифровать текст, введите 1");
    printf("\nЧтобы расшифровать файл, введите 0\n");
    inputInt(&format, 0, 1);
    if(format)
    {
        *text = decodingInputText(box1, rows);                              //декодирование текста введенного с клавиатуры
    }
    else
    {                                                                            //декодирование текста из файла
        *text = decodingTextFromFile(codeText, newText, keys, countKeys, box1, rows);
    }
    printf("\nРаскодированный текст:\n");
    output2DString(*text, *rows);
}







void saveInformation (char** text, char** newText, long** code, long rows, struct dataCode *keys, long countKeys)
{
    int format;
    char* fileName;
    printf("\nЧто вы хотите сохранить в файл?");
    printf("\n1 - исходный текст");
    printf("\n2 - текст, закодированный алгоритмом RSA");
    printf("\n3 - текст, закодированный алгоритмом Square");
    inputInt(&format, 1, 3);
    printf("\nВведите имя файла, в который хотите сохранить\n");
    inputStr(&fileName);

    strcpy((keys + countKeys - 1)->fileName, fileName);                 //сохраняю имя файла

    if (format == 1)
    {
        saveTextToFile(text, rows, fileName);                           //сохраняю исходный текст
    }
    if (format == 2)
    {
        saveNumberToFile(code, rows, fileName);                         //сохраняю текст зашифрованный RSA
    }
    else
    {
        saveTextToFile(newText, rows, fileName);                    //сохраняю текст зашифрованный алгоритмом четырех квадратов
    }
}

//функция чтения текста из файла
void caseReadText (char*** text, long* rows)
{
    char* fileName;
    printf("\033[3;32m Введите имя файла\033[0m, из которого хотите считать текст\n");
    inputStr(&fileName);
    *text = loadTextFromFile(rows, fileName);                           //читаю текст из файла
    if(*text != NULL)
    {
        printf("Прочитанный текст:\n");
        output2DString(*text, *rows);
    }

}






