#include "headerExamPrep.h"

//стек
//int main ()
//{
//    struct FILO * head1 = NULL, * head2 = NULL;
//    int n1 = 0, n2 = 0, max1, max2;
//    input2FILO(&head1, &head2, &n1, &n2, 3, 3);
//    return 0;
//}




//очередь однонаправленная
//int main ()
//{
//    int n = 0;
//    struct FIFO * head = NULL, * tail = NULL;
//    taskFIFO(&head, &tail, &n, 6);
//}

//очередь двунаправленная
int main ()
{
    int n = 0;
    struct FIFO2 * head = NULL, * tail = NULL;
    pushFIFO2(&head, &tail, 2);
    pushFIFO2(&head, &tail, 3);
    pushFIFO2(&head, &tail, 1);
    sortFIFO2(&head, &tail);
}