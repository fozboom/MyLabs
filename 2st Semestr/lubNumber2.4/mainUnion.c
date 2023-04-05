#include "headerUnion.h"





int main()
{
    int n = 1;
    struct child *inf;
    //inputStruct (&inf, &n);
    readInformation(&inf, &n);
    outputStr(inf, n);
    quickSort(inf, 0, n - 1);
    outputStr(inf, n);
    return 0;
}
