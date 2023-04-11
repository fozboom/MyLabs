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


long* coding (char* mas, long e, long n)
{
    long *cods = (long*)calloc(strlen(mas), sizeof(long));
    for (int i = 0; mas[i] != '\0'; i++)
    {
        long s = (long)(mas[i]);
        cods[i] = powerMod(s, e, n);
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
