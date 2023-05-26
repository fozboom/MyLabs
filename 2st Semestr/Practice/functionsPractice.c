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
    do                                      //создать простое число e, удовлетворяющее условию: (e*d) mod ((p-1)*(q-1))=1, e >= fi
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



//функция нахождения числа d - части приватного ключа
void search_d(long* x, long e, long fi)
{
    long m0 = fi;  // Сохраняем значение fi для восстановления отрицательного результата
    long y = 0, xPrev = 1;  // Инициализируем начальные значения коэффициентов

    while (e > 1)
    {
        long q = e / fi;  // Вычисляем частное от деления e на fi
        long t = fi;  // Временная переменная для сохранения значения fi

        fi = e % fi;  // Вычисляем остаток от деления e на fi
        e = t;  // Обновляем значение e для следующей итерации
        t = y;  // Сохраняем предыдущее значение y

        y = xPrev - q * y;  // Обновляем значение y
        xPrev = t;  // Обновляем предыдущее значение x
    }

    if (xPrev < 0) {
        xPrev += m0;  // Если результат отрицательный, приводим его к положительному
    }

    *x = xPrev;  // Присваиваем значение x через указатель
}

long power (long x, long n)
{
    if (n == 0)
        return 1;
    else
        return x * power(x, n-1);
}


long powerMod(long x, long y, long n)
{
    if(y == 0)
        return 1;
    if (y%2 == 0)
    {
        long z = powerMod(x, y/2, n);
        return (z*z)%n;
    }
    else
        return (x * powerMod(x, y-1, n))%n;
}



//функция кодирования текста алгоритмом RSA
long** coding (char** mas, long e, long n, long rows)
{
    if (mas == NULL)
    {
        printf("Вы не ввели текст, который надо зашифровать");
        return NULL;
    }
    long **cods = (long **)calloc(rows, sizeof(long*));
    for(int j = 0; j < rows; j++)
    {
        int k = 1;
        long size = strlen(*(mas + j));
        *(cods + j) = (long *)calloc(size + 1, sizeof(long));
        cods[j][0] = size + 1;
        for (int i = 0; mas[j][i] != '\0'; i++)
        {
            long s = (long) (mas[j][i]);
            cods[j][k] = powerMod(s, e, n);
            k++;
        }
    }
    return cods;
}




char** decodingRSA(long** codeText, long d, long n, long rows)
{
    char** decodedText = (char**)malloc(rows * sizeof(char*)); // Выделяем память для массива строк

    for (long i = 0; i < rows; i++)
    {
        long cols = codeText[i][0]; // Получаем количество элементов в текущей строке

        decodedText[i] = (char*)malloc((cols + 1) * sizeof(char)); // Выделяем память для строки (плюс 1 для символа '\0')

        for (long j = 1; j < cols; j++)
        {
            long s = powerMod(codeText[i][j], d, n); // Декодируем текущий элемент

            decodedText[i][j-1] = (char)s; // Преобразуем числовое значение в символ и сохраняем в строке
        }

        decodedText[i][cols] = '\0'; // Добавляем символ '\0' в конец строки
    }

    return decodedText;
}












void writeBox (char box[SIZE][SIZE], int n)
{
    int k = 0;
    char* word = NULL;
    char letters[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int used[26] = {0}, flag;                           //used - массив отвечающий за повторение букв
    do                                                  //проверяем ключевое слово на повторенеи букв
    {
        flag = 0;
        printf("\nВведите кодовое слово: ");
        inputStr(&word);
        for (int i = 0; word[i] != '\0'; i++)
        {
            for (int j = i + 1; word[j-1] != '\0'; j++)
            {
                if ((word[i] == word[j]) || !checkLetter(word[i]))
                {
                    flag = 1;
                    break;
                }
            }
            if (flag) break;
        }
    }while(flag);

    for(int i = 0; word[i] != '\0'; i++)                           //запись букв ключевого слова в квадрат
    {
        used[word[i] - 'A'] = 1;
        box[k / SIZE][k % SIZE] = word[i];
        k++;
    }

    for(int i = 0; i < 26; i++)
    {
        if(used[letters[i] - 'A'] == 0)
        {
            box[k / SIZE][k % SIZE] = letters[i];
            used[letters[i] - 'A'] = 1;
            k++;
        }
    }
    //outputBox(box, SIZE);
    pushRandom (box, ' ', 4, 2);
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
    for(int i = 0; i < n; i++) {
        printf("\n");
        for (int j = 0; j < n; j++) {
            printf("%c ", box[i][j]);
        }
    }
    printf("\n\n\n");
}

void readInfo (char box[SIZE][SIZE], int n, const char* name)
{
    FILE* file;
    char s;
    int j;
    file = fopen(name, "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n; i++)
    {
        j = 0;
        while((s = getc(file)) != '\n' && !feof(file))
        {
            box[i][j] = s;
            j++;
        }
    }
    fclose(file);
}



char** codingSquare (char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char **text, int size)
{
    for(int c = 0; c < size; c++)
    {
        int n = strlen(text[c]);
        int i = 0, j = 0, k = 0, l = 0;
        if (strlen(text[c]) % 2 == 1)
        {
            n += 2;
            char* tmp = (char*)realloc(text[c], (n) * sizeof(char));
            if (tmp != NULL)
            {
                text[c] = tmp;
                text[c][n - 2] = ' ';
                text[c][n - 1] = '\0';
            } else {
                printf("\nОшибка памяти");
                exit(EXIT_FAILURE);
            }

        }
        for (int z = 0; z < n - 1; z++)
        {
            if (checkLetter(text[c][z]))
            {
                i = (text[c][z] - 'A') / SIZE;
                j = (text[c][z] - 'A') % SIZE;
            } else
            {
                searchLetterIndex(box1, &i, &j, SIZE, text[c][z]);
            }
            z++;
            if (checkLetter(text[c][z]))
            {
                k = (text[c][z] - 'A') / SIZE;
                l = (text[c][z] - 'A') % SIZE;
            } else
            {
                searchLetterIndex(box4, &k, &l, SIZE, text[c][z]);
            }
            char x1, x2;
            x1 = box2[i][l];
            x2 = box3[k][j];
            text[c][z - 1] = x1;
            text[c][z] = x2;
        }
    }
    return text;

}



char** decodeSquare(char box1[SIZE][SIZE], char box2[SIZE][SIZE], char box3[SIZE][SIZE], char box4[SIZE][SIZE], char** text, long rows)
{
    for (int c = 0; c < rows; c++)
    {
        int i = 0, j = 0, k = 0, l = 0, n = strlen(text[c]);
        for (int z = 0; z < n; z++)
        {
            searchLetterIndex(box2, &i, &j, SIZE, text[c][z]);
            searchLetterIndex(box3, &k, &l, SIZE, text[c][z + 1]);
            char x1 = box1[i][l];
            char x2 = box4[k][j];
            text[c][z] = x1;
            text[c][z + 1] = x2;
            z++;
        }
    }
    return text;
}


int checkLetter (char s)
{
    int flag = 1;
    if(s < 'A' || s > 'Z')
        flag = 0;
    return flag;
}

void pushRandom (char box[SIZE][SIZE], char s, int i, int j)
{
    int l, m;
    srand(time(NULL));
    l = rand()%3;
    srand(time(NULL));
    m = rand()%3;
    char letter = box[l][m];
    box[l][m] = s;
    box[i][j] = letter;

}


void searchLetterIndex (char box[SIZE][SIZE], int *i, int* j, int n, char s)
{
    int flag = 0;
    for ((*i) = 0; (*i) < n; (*i)++)
    {
        for ((*j) = 0; (*j) < n; (*j)++)
        {
            if (box[(*i)][(*j)] == s)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
            break;
    }
}

//функция выбора команды
void choiceTask (enum choiceCommand *doTask, const char* tasks[], bool *taskIsFound)
{
    char* task = NULL;
    printf("\nВыберите действие:\n");
    printf("'input' - ввод текста, который необходимо закодировать\n");
    printf("'read' - считать текст из файла\n");
    printf("'encoding' - закодировать текст\n");
    printf("'decoding' - раскодировать текст\n");
    printf("'save' - сохранить зашифрованный текст в файл\n");
    printf("'finish' - завершить программу\n");
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

struct dataCode createKeyCoding (char box2[SIZE][SIZE], char box3[SIZE][SIZE])
{
    char* task = NULL;
    int flag, choice;
    long p, q, fi;
    struct dataCode key;
    printf("\nДля какого алгоритма шифрования вы хотите создать ключ?\n");
    printf("'RSA' - шифрование алгоритмом RSA\n");
    printf("'Square' - шифрование алгоритмом четырех квадратов\n");
    do
    {
        printf("Введите название алгоритма: ");
        inputStr(&task);
        if (strcmp(task, "RSA") == 0)
        {
            flag = 1;
        } else if (strcmp(task, "Square") == 0)
        {
            flag = 0;
        } else
        {
            printf("\nКоманда введена неверно");
            flag = 2;
        }
    }while(flag == 2);

    if(flag)
    {
        printf("\nЧтобы сгенерировать ключ случайно, введите 0");
        printf("\nЧтобы сгенерировать ключ вручную, введите 1\n");
        inputInt(&choice, 0, 1);
        if (choice)
        {

        }
        else
        {
            createNumbers(&p, &q, &key.n, &fi);
            createEilerNumber(&key.e, fi);
            search_d(&key.d, key.e, fi);
        }
        printf("\nОткрытый ключ: {%ld, %ld}, закрытый ключ: {%ld, %ld} ", key.n, key.e, key.n, key.d);
    }
    else
    {
        writeBox(box2, SIZE);
        writeBox(box3, SIZE);
        for (int i = 0; i < SIZE; i++)
            for(int j = 0; j < SIZE; j++)
                key.box2[i][j] = box2[i][j];
        for (int i = 0; i < SIZE; i++)
            for(int j = 0; j < SIZE; j++)
                key.box3[i][j] = box3[i][j];
    }

    return key;
}

struct dataCode encodingText (char** text, int n, long ***codeText, char ***newText)
{
    struct dataCode key;
    char* task = NULL;
    int choice;
    long p, q, fi;
    long **code = (long**)calloc(n, sizeof(long*));
    char **codingText = (char**)calloc(n, sizeof(char*));
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
            key.flag = 1;
            printf("\nЧтобы сгенерировать ключ случайно, введите 0");
            printf("\nЧтобы сгенерировать ключ вручную, введите 1\n");
            inputInt(&choice, 0, 1);
            if (choice)
            {
                do
                {
                    printf("\nВведите простое число p - ");
                    scanf("%ld", &p);
                } while (!isPrimes(p));
                do
                {
                    printf("\nВведите простое число q - ");
                    scanf("%ld", &q);
                } while (!isPrimes(q));
                key.n = p * q;
                fi = (p - 1) * (q - 1);
                createEilerNumber(&(key.e), fi);
                search_d(&(key.d), key.e, fi);
            }
            else
            {
                createNumbers(&p, &q, &key.n, &fi);
                createEilerNumber(&key.e, fi);
                search_d(&key.d, key.e, fi);
            }
            printf("\nОткрытый ключ: {%ld, %ld}, закрытый ключ: {%ld, %ld} ", key.n, key.e, key.n, key.d);
        }



        else if (strcmp(task, "Square") == 0)
        {
            key.flag = 0;
            readInfo(box1, SIZE, "box1.txt");
            readInfo(box4, SIZE, "box4.txt");
            writeBox(box2, SIZE);
            writeBox(box3, SIZE);
            for (int i = 0; i < SIZE; i++)
                for(int j = 0; j < SIZE; j++)
                    key.box2[i][j] = box2[i][j];
            for (int i = 0; i < SIZE; i++)
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
        code = coding(text, key.e, key.n, n);
        output2DNumbers(code, n);
        codingText = NULL;
    }
    else
    {
        codingText = codingSquare(box1, box2, box3, box4, text, n);
        output2DString(codingText, n);
        code = NULL;
    }
    *newText = codingText;
    *codeText = code;
    return key;
}


char** decodingTextFromFile(long** codeText, char** newText, struct dataCode* keys, int count, char box[SIZE][SIZE], long* rows)
{
    int flag = 0, i;
    char **text = NULL;
    char* fileName = NULL;
    printf("\nВведите имя файла, который надо расшифровать: ");
    inputStr(&fileName);
    for (i = 0; i < count; i++)
    {
        if (strcmp(fileName, keys[i].fileName) == 0)
        {
            flag = 1;
            break;
        }
    }
    if (flag)
    {
        FILE* file;
        file = fopen(keys[i].fileName, "rt");
        if (file != NULL)
        {
            int dataType = keys[i].flag; // Тип данных: 1 - long, 0 - char
            if (dataType == 1)
            {
                codeText = loadNumberFromFile(codeText, rows, fileName);
                text = decodingRSA(codeText, keys[i].d, keys[i].n, *rows);

            }
            else if (dataType == 0)
            {
                newText = loadTextFromFile(rows, fileName);
                text = decodeSquare(box, keys[i].box2, keys[i].box3, box, newText, *rows);
            }

            fclose(file);
        }
        else
        {
            printf("\nОшибка при открытии файла для чтения\n");
        }
    }
    else
    {
        printf("\n\033[1;41m\033[1m\nФайл с таким именем не найден\033[0m");
    }
    return text;
}



void saveStructInfo (struct dataCode* key, long count)
{
    FILE* file;
    file = fopen("keyInfo", "wb");
    if (file != NULL)
    {
        fwrite(&count, sizeof(long), 1, file);
        fwrite(key, sizeof(struct dataCode), count, file);
    }
    else
        printf("\n\033[1;41m\033[1m\nОшибка при открытии бинарного файла для записи ключей\033[0m");
    fclose(file);
}

void readStructInfo(struct dataCode** key, long* count)
{
    FILE* file;
    file = fopen("keyInfo", "rb");
    if (file != NULL)
    {
        fread(count, sizeof(long), 1, file); // Считываем количество элементов
        *key = (struct dataCode*)calloc((*count), sizeof(struct dataCode)); // Выделяем память для массива структур
        fread(*key, sizeof(struct dataCode), *count, file); // Считываем массив структур
        fclose(file);
    }
    else
        printf("\n\033[1;41m\033[1m\nОшибка при открытии бинарного файла для чтения ключей\033[0m");
}

void saveNumberToFile(long** code, long rows, char* fileName)
{
    int format;

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format)
    {
        file = fopen(fileName, "wt");
        if (file != NULL)
        {
            fprintf(file, "%ld\n", rows); // Записываем количество строк

            for (long i = 0; i < rows; i++)
            {
                long cols = code[i][0]; // Получаем количество элементов в текущей строке
                fprintf(file, "%ld ", cols); // Записываем количество элементов

                for (long j = 1; j <= cols; j++)
                {
                    fprintf(file, "%ld ", code[i][j]); // Записываем элементы строки
                }

                fprintf(file, "\n"); // Переходим на новую строку
            }

            fclose(file);
        }
        else
        {
            printf("\nОшибка при открытии бинарного файла для записи кода\n");
        }
    }
    else
    {
        file = fopen(fileName, "wb");
        if (file != NULL)
        {
            fwrite(&rows, sizeof(long), 1, file); // Записываем количество строк

            for (long i = 0; i < rows; i++)
            {
                long cols = code[i][0]; // Получаем количество элементов в текущей строке
                fwrite(&cols, sizeof(long), 1, file); // Записываем количество элементов

                for (long j = 1; j <= cols; j++)
                {
                    fwrite(&code[i][j], sizeof(long), 1, file); // Записываем элементы строки
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
    int format;

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format)
    {
        file = fopen(fileName, "rt");
        if (file != NULL)
        {
            if (fscanf(file, "%ld", rows) == 1)
            {
                code = (long**)malloc((*rows) * sizeof(long*));

                for (long i = 0; i < *rows; i++)
                {
                    long cols;
                    if (fscanf(file, "%ld", &cols) == 1)
                    {
                        code[i] = (long*)malloc((cols + 1) * sizeof(long));
                        code[i][0] = cols;

                        for (long j = 1; j <= cols; j++)
                        {
                            fscanf(file, "%ld", &code[i][j]);
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
        file = fopen(fileName, "rb");
        if (file != NULL)
        {
            if (fread(rows, sizeof(long), 1, file) == 1)
            {
                code = (long**)malloc((*rows) * sizeof(long*));

                for (long i = 0; i < *rows; i++)
                {
                    long cols;
                    if (fread(&cols, sizeof(long), 1, file) == 1)
                    {
                        code[i] = (long*)malloc((cols + 1) * sizeof(long));
                        code[i][0] = cols;

                        for (long j = 1; j <= cols; j++)
                        {
                            if (fread(&code[i][j], sizeof(long), 1, file) != 1)
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



void saveTextToFile(char** text, long rows, char* fileName) {
    int format;

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format) {
        file = fopen(fileName, "w");
        if (file != NULL) {
            for (long i = 0; i < rows; i++) {
                fprintf(file, "%s\n", text[i]); // Записываем строку в текстовый файл
            }
            fclose(file);
            printf("Массив строк успешно сохранен в текстовый файл: %s\n", fileName);
        } else {
            printf("Ошибка при открытии текстового файла для записи\n");
        }
    } else {
        file = fopen(fileName, "wb");
        if (file != NULL) {
            fwrite(&rows, sizeof(long), 1, file); // Записываем количество строк в бинарный файл

            for (long i = 0; i < rows; i++) {
                long len = strlen(text[i]); // Получаем длину строки
                fwrite(&len, sizeof(long), 1, file); // Записываем длину строки
                fwrite(text[i], sizeof(char), len, file); // Записываем строку
            }

            fclose(file);
            printf("Массив строк успешно сохранен в бинарный файл: %s\n", fileName);
        } else {
            printf("Ошибка при открытии бинарного файла для записи\n");
        }
    }
}

void inputString(char* str)
{
    int i = 0;
    fgets(str, MAX_LENGTH, stdin);
    while (str[i] != '\n')
        i++;
    str[i] = '\0';
}

char** loadTextFromFile(long* rows, char* fileName)
{
    int format;

    printf("Выберите тип файла (0 - текстовый или 1 - бинарный): ");
    inputInt(&format, 0, 1);

    FILE* file;

    if (!format) {
        file = fopen(fileName, "r");
    } else {
        file = fopen(fileName, "rb");
    }

    if (file != NULL) {
        if (!format) {
            fscanf(file, "%ld\n", rows); // Считываем количество строк
        } else {
            fread(rows, sizeof(long), 1, file); // Считываем количество строк
        }

        char** text = (char**)malloc(*rows * sizeof(char*));
        if (text != NULL) {
            for (long i = 0; i < *rows; i++) {
                char buffer[MAX_LENGTH];
                if (!format) {
                    inputString(buffer);
                    text[i] = strdup(buffer);
                } else {
                    long len;
                    fread(&len, sizeof(long), 1, file); // Считываем длину строки
                    text[i] = (char*)malloc((len + 1) * sizeof(char)); // Выделяем память для строки
                    fread(text[i], sizeof(char), len, file); // Считываем строку
                    text[i][len] = '\0'; // Добавляем символ конца строки
                }


            }
        } else {
            printf("Ошибка при выделении памяти\n");
        }

        fclose(file);
        return text;
    } else {
        printf("Ошибка при открытии файла для чтения\n");
        return NULL;
    }
}








struct dataCode saveEncodingInfo (char** newText, long** code, long rows, struct dataCode key)
{
    char fileName[N];
    int i = 0;
    printf("\nВведите имя файла, в который хотите сохранить: ");
    fgets(fileName, N, stdin);
    while (fileName[i] != '\n')
        i++;
    fileName[i] = '\0';
    strcpy(key.fileName, fileName);
    if(key.flag)
    {
        saveNumberToFile(code, rows, key.fileName);
    }
    else
    {
        saveTextToFile(newText, rows, key.fileName);
    }
    return key;
}


void caseEncoding (struct dataCode **keys, long *countKeys, long*** codeText, char** text, int n, char*** newText)
{
    (*countKeys)++;
    (*keys) = (struct dataCode*)realloc((*keys), (*countKeys) * sizeof(struct dataCode));
    *(*keys + (*countKeys) - 1) = encodingText(text, n, codeText, newText);
    if((*keys + (*countKeys) - 1)->flag)
        output2DNumbers(*codeText, n);
    else
        output2DString(*newText, n);
}


void caseDecoding (char ***text, long **codeText, char **newText, struct dataCode *keys, long countKeys, char box1[SIZE][SIZE], long *rows)
{
    int format;
    printf("\nЧтобы расшифровать текст, введите 1");
    printf("\nЧтобы расшифровать файл, введите 0\n");
    inputInt(&format, 0, 1);
    if(format)
    {
        *text = decodingInputText(box1, rows);
    }
    else
    {
        *text = decodingTextFromFile(codeText, newText, keys, countKeys, box1, rows);
    }

    printf("\nРаскодированный текст:\n");
    output2DString(*text, *rows);
}

char** decodingInputText (char box[SIZE][SIZE], long* rows)
{
    char* string, **text, *name1, *name2, box2[SIZE][SIZE], box3[SIZE][SIZE];
    long** code, d, n;
    int flag = 0;
    do
    {
        printf("\nКаким алгоритмом зашифрован текст? (RSA или Square)\n");
        inputStr(&string);
        if (strcmp("RSA", string) == 0 || strcmp("Square", string) == 0)
        {
            flag = 1;
        }
        else
        {
            printf("\nКоманда введена неверно, попробуйте еще раз");
        }
    }while(!flag);

    if(strcmp("RSA", string) == 0)
    {
        printf("\nВведите через пробел цифры, которыми закодирована каждая буква");
        input2DString(&text, rows);
        code = myAtoi2DText(text, *rows);
        //output2DNumbers(code, rows);
        printf("\nВведите ключ для расшифровки\nВведите число d - ");
        inputLong(&d, 0, 10000);
        printf("Введите число n - ");
        inputLong(&n, 0, 10000);
        text = decodingRSA(code, d, n, *rows);
        //output2DString(text, rows);
    }
    else
    {
        printf("\nВведите закодированный текст\n");
        input2DString(&text, rows);
        printf("\nВведите имя файла, в котором хранится box2 - ");
        inputStr(&name1);
        readInfo(box2, SIZE, name1);
        printf("\nВведите имя файла, в котором хранится box3 - ");
        inputStr(&name2);
        readInfo(box3, SIZE, name2);
        text = decodeSquare(box, box2, box3, box, text, *rows);
    }
    return text;
}



long** myAtoi2DText(char** text, long rows)
{
    long** numbers = (long**)malloc(rows * sizeof(long*));

    for (int i = 0; i < rows; i++)
    {
        int count = 0;                                  //кол-во чисел в текущей строке

        char* copy = strdup(text[i]);               //создаем копию строки с выделением памяти, чтобы избежать изменения исходной строки
        char* token = strtok(copy," " );
        while (token != NULL)
        {
            count++;
            token = strtok(NULL, " ");
        }
        free(copy);

        numbers[i] = (long*)malloc((count + 1) * sizeof(long));
        numbers[i][0] = count + 1;

                                                        //преобразование строки в число
        char* tokenPtr = strtok(text[i], " ");
        int j = 1;
        while (tokenPtr != NULL) {
            numbers[i][j++] = atol(tokenPtr);
            tokenPtr = strtok(NULL, " ");
        }
    }

    return numbers;
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

    strcpy((keys + countKeys - 1)->fileName, fileName);

    if (format == 1)
    {
        saveTextToFile(text, rows, fileName);
    }
    if (format == 2)
    {
        saveNumberToFile(code, rows, fileName);
    }
    else
    {
        saveTextToFile(newText, rows, fileName);
    }
}

void caseReadText (char*** text, long* rows)
{
    char* fileName;
    printf("\nВведите имя файла, из которого хотите считать текст\n");
    inputStr(&fileName);
    *text = loadTextFromFile(rows, fileName);
    printf("Прочитанный текст:\n");
    output2DString(*text, *rows);
}



