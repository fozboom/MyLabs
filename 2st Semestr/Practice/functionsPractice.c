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


long* coding (char* mas, long e, long n, long* size)
{
    long *cods = (long*)calloc(strlen(mas), sizeof(long));
    for (int i = 0; mas[i] != '\0'; i++)
    {
        long s = (long)(mas[i]);
        cods[i] = powerMod(s, e, n);
        (*size)++;
    }
    return cods;
}

char* decoding (long* cods, long d, long n, int size)
{
    char* mas = (char*)calloc(size, sizeof(char));
    for(int i = 0; i < n; i++)
    {
        long s = powerMod(cods[i], d, n);
        mas[i] = (char)s;
    }
    return mas;
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
    str = decoding(code, d, n, strlen(str));
}













void writeBox (char** box, int n)
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
    outputBox(box, SIZE);
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
    outputBox(box, SIZE);

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

void readInfo (char** box, int n, const char* name)
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


char* codingSquare (char** box1, char** box2, char** box3, char** box4, char *mas)
{
    int n = strlen(mas);
    int i = 0, j = 0, k = 0, l = 0;
    if(strlen(mas)%2 == 1)
    {
        n+=2;
        mas = (char*)realloc(mas, (n) * sizeof(char));
        mas[n - 2] = ' ';
        mas[n - 1] = '\0';
    }
    for(int z = 0; z < n-1; z++)
    {
        if (checkLetter(mas[z]))
        {
            i = (mas[z] - 'A') / SIZE;
            j = (mas[z] - 'A') % SIZE;
        }
        else
        {
            searchLetterIndex(box1, &i, &j, SIZE, mas[z]);
        }
        z++;
        if (checkLetter(mas[z]))
        {
            k = (mas[z] - 'A') / SIZE;
            l = (mas[z] - 'A') % SIZE;
        } else
        {
            searchLetterIndex(box4, &k, &l, SIZE, mas[z]);
        }
        char x1, x2;
        x1 = box2[i][l];
        x2 = box3[k][j];
        mas[z-1] = x1;
        mas[z] = x2;
    }
    return mas;

}

void decodeSquare (char** box1, char** box2, char** box3, char** box4, char* mas)
{
    int i = 0, j = 0, k = 0, l = 0, n = strlen(mas);
    for(int z = 0; z < n ; z++)
    {
        searchLetterIndex(box2, &i, &j, SIZE, mas[z]);
        searchLetterIndex(box3, &k, &l, SIZE, mas[z + 1]);
        char x1, x2;
        x1 = box1[i][l];
        x2 = box4[k][j];
        mas[z] = x1;
        mas[z + 1] = x2;
        z++;
    }

}


int checkLetter (char s)
{
    int flag = 1;
    if(s < 'A' || s > 'Z')
        flag = 0;
    return flag;
}

void pushRandom (char** box, char s, int i, int j)
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


void searchLetterIndex (char **box, int *i, int* j, int n, char s)
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



