#include "headerUnion2.h"

int main()
{
    int n = 1;
    struct child *inf;
    inputStruct(&inf, &n);
    outputStr(inf, n);

    return 0;
}