#include "headerPractice.h"
#include "../myLibrary.h"

long isPrimes (long x)
{
    if(x == 0) return 0;
    for(int i = 2; i < x; i++)
        if (x%i == 0) return 0;
    return 1;
}

void createPrime (long *x)
{
    srand(time(NULL));
    *x = rand()%10;
    *x = (*x)*(*x) - (*x) + 41;
}

void createNumbers (long *p, long *q, long *n, long *fi)
{
    createPrime(p);
    do
    {
        createPrime(q);
    }while(*q == *p);
    *n = (*p) * (*q);
    *fi = ((*p) - 1)*((*q) - 1);

}

void createEilerNumber (long *e, long fi)
{
    do
    {
        createPrime(e);
    }while(NOD(*e, fi) != 1 && *e >= fi);

}

long NOD (long x, long y)
{
    if (y == 0)
        return x;
    else
        return NOD (y, x%y);
}

void search_d (long *d, long e, long fi)
{
    *d = 3;
    while (((*d) * e) % fi != 1)
    {
        (*d)++;
    }
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




long** coding (char** mas, long e, long n, long rows)
{
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

        for (long j = 0; j < cols; j++)
        {
            long s = powerMod(codeText[i][j + 1], d, n); // Декодируем текущий элемент

            decodedText[i][j] = (char)s; // Преобразуем числовое значение в символ и сохраняем в строке
        }

        decodedText[i][cols] = '\0'; // Добавляем символ '\0' в конец строки
    }

    return decodedText;
}

void textRSA(long* code, long size, long d, long n)
{
    const char* fileName;
    FILE* file;
    printf("Введите имя файла, в который хотите сохранить");
    inputStr(&fileName);
    file = fopen(fileName, "w");
    if(file == NULL)
    {
        printf("Ошибка создания текстового файла");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%ld ", d);
    fprintf(file, "%ld\n", n);
    for (int i = 0; i < size; i++)
    {
        fprintf(file, "%ld", code[i]);
        fprintf(file, " ");
    }
}

char* antiTextRSA (long* code, long d, long n, long size)
{
    FILE* file = NULL;
    const char* str;
    printf("Введите имя файла, который хотите раскодировать:\n");
    inputStr(&str);
    fopen(str, "r");
    if(file == NULL)
    {
        printf("\nФайла с таким именем не найден\n");
        exit(EXIT_FAILURE);
    }
    //str = decoding(code, d, n, strlen(str));
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

void createBoxes (char*** box1, char*** box2, char*** box3, char*** box4, int n)
{

    *box1 = (char**)calloc(n, sizeof(char*));
    for(int i = 0; i < n; i++)
        *(*box1 + i) = (char*)calloc(n, sizeof(char));

    *box2 = (char**)calloc(n, sizeof(char*));
    for(int i = 0; i < n; i++)
        *(*box2 + i) = (char*)calloc(n, sizeof(char));

    *box3 = (char**)calloc(n, sizeof(char*));
    for(int i = 0; i < n; i++)
        *(*box3 + i) = (char*)calloc(n, sizeof(char));

    *box4 = (char**)calloc(n, sizeof(char*));
    for(int i = 0; i < n; i++)
        *(*box4 + i) = (char*)calloc(n, sizeof(char));
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
    printf("'createKey' - создать публичный и приватный ключ\n");
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

struct dataCode createKeyCoding (char **box2, char **box3)
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


char** decodingText(long** codeText, char** newText, struct dataCode* keys, int count, char box[SIZE][SIZE])
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
            long rows;
            fscanf(file, "%ld\n", &rows); // Читаем количество строк

            int dataType = keys[i].flag; // Тип данных: 0 - long, 1 - char
            if (dataType == 1)
            {
                codeText = (long**)malloc(rows * sizeof(long*)); // Выделяем память для массива строк

                for (long j = 0; j < rows; j++)
                {
                    long cols;
                    fscanf(file, "%ld ", &cols); // Читаем количество элементов

                    codeText[j] = (long*)malloc(cols * sizeof(long)); // Выделяем память для строки

                    for (long k = 0; k < cols; k++)
                    {
                        fscanf(file, "%ld ", &codeText[j][k]); // Читаем элементы строки
                    }
                }

                text = decodingRSA(codeText, keys[i].d, keys[i].n, rows);

                // Не забудьте освободить память после использования
                for (long j = 0; j < rows; j++)
                {
                    free(codeText[j]);
                }
                free(codeText);
            }
            else if (dataType == 0)
            {
                newText = (char**)malloc(rows * sizeof(char*)); // Выделяем память для массива строк

                for (long j = 0; j < rows; j++)
                {
                    newText[j] = (char*)malloc(MAX_LENGTH * sizeof(char)); // Выделяем память для строки
                    fgets(newText[j], MAX_LENGTH, file); // Читаем строку текста
                    newText[j][strcspn(newText[j], "\n")] = '\0'; // Удаляем символ новой строки
                }

                text = decodeSquare(box, keys[i].box2, keys[i].box3, box, newText, rows);


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
    FILE* file = fopen(fileName, "w");
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
        printf("\nОшибка при открытии текстового файла для записи кода\n");
    }
}

long** loadNumberFromFile(long* rows)
{
    char* fileName;
    printf("\nВведите имя файла, в который хотите сохранить текст");
    inputStr(&fileName);
    FILE* file = fopen(fileName, "r");
    if (file != NULL)
    {
        fscanf(file, "%ld\n", rows); // Читаем количество строк

        long** code = (long**)malloc((*rows) * sizeof(long*)); // Выделяем память для массива строк

        for (long i = 0; i < *rows; i++)
        {
            long cols;
            fscanf(file, "%ld ", &cols); // Читаем количество элементов

            code[i] = (long*)malloc((cols + 1) * sizeof(long)); // Выделяем память для строки

            code[i][0] = cols; // Сохраняем количество элементов в первом элементе строки

            for (long j = 1; j <= cols; j++)
            {
                fscanf(file, "%ld ", &code[i][j]); // Читаем элементы строки
            }
        }

        fclose(file);
        return code;
    }
    else
    {
        printf("\nОшибка при открытии текстового файла для чтения кода\n");
        return NULL;
    }
}

void saveTextToFile(char** text, long rows, char* fileName)
{
    FILE* file = fopen(fileName, "wt");
    if (file != NULL)
    {
        fprintf(file, "%ld\n", rows); // Записываем количество строк

        for (long j = 0; j < rows; j++)
        {
            fprintf(file, "%s\n", text[j]); // Записываем строку текста
        }

        fclose(file);
        printf("Текст успешно сохранен в файл: %s\n", fileName);
    }
    else
    {
        printf("Ошибка при открытии файла для записи\n");
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





