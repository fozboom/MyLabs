#include "headerUnion2.h"

int main()
{
    int n = 1;
    struct child *inf;
    inputStruct(&inf, &n);
    outputStr(inf, n);
    quickSorting(inf, 0, n - 1, comparatorSurnames);
    outputStr(inf, n);
    return 0;
}