#ifndef MYLABS_HEADERPRACTICE_H
#define MYLABS_HEADERPRACTICE_H

#endif //MYLABS_HEADERPRACTICE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

long toASCII (char s);
long isPrimes (long x);
void createPrime (long *x);
void createNumbers (long *p, long *q, long *n, long *fi);
void createEilerNumber (long *e, long fi);
void search_d (long *d, long e, long fi);
long power (long x, long n);
long NOD (long x, long y);

long powerMod(long x, long y, long n);
long* coding (char* mas, long e, long n);
char* decoding (long* cods, long d, long n, int size);