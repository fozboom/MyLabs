#include "headerPractice.h"

void writeBox (char** box, int n)
{
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++) {
            printf("Введите %d символ %d строки ", j+1, i+1);
            scanf("%c", &box[i][j]);
            rewind(stdin);
        }
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
    file = fopen(name, "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            fscanf(file, "%s", &box[i][j]);
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

void inputStr ()
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
}


void mainTask (char** box1, char** box2, char** box3, char** box4, int n, char* s1, char* s2)
{
    int i = 0, j = 0, k = 0, l = 0, flag = 0;

    for(i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (box1[i][j] == *s1) {
                flag = 1;
                break;
            }
        }
        if(flag) break;
    }
    flag = 0;

    for(k = 0; k < n; k++) {
        for (l = 0; l < n; l++) {
            if (box1[k][l] == *s1) {
                flag = 1;
                break;
            }
        }
        if(flag) break;
    }
    *s1 = box2[i][l];
    *s2 = box3[k][j];

    printf("%c", *s1);
    printf("%c", *s2);
}


