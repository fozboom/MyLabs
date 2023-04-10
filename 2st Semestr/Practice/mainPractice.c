#include "headerPractice.h"

int main() {
    int n = 5;
    char s1 = 'a', s2 = 'b';
    char** box1, **box2, **box3, **box4;
    createBoxes(&box1, &box2, &box3, &box4, n);
    //writeBox(box1, n);
    readInfo(box1, n, "box1.txt");
    outputBox(box1, n);
    readInfo(box2, n,"box2.txt");
    outputBox(box2, n);
    readInfo(box3, n, "box3.txt");
    outputBox(box3, n);
    readInfo(box4, n, "box4.txt");
    outputBox(box4, n);


    mainTask(box1, box2, box3, box4, n, &s1, &s2);
    inputStr();

}
