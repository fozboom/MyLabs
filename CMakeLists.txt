cmake_minimum_required(VERSION 3.24)
project(myLabs C)

set(CMAKE_C_STANDARD 99)

add_executable(labNumber2.4
        "2st Semestr/lubNumber2.4/mainUnion.c"
        "2st Semestr/lubNumber2.4/functionsUnion.c"
        "2st Semestr/lubNumber2.4/headerUnion.h"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")

add_executable(labNumber2.4.2
        "2st Semestr/lubNumber2.4.2/mainUnion2.c"
        "2st Semestr/lubNumber2.4.2/functionsUnion2.c"
        "2st Semestr/lubNumber2.4.2/headerUnion2.h"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")

add_executable(labNumber2.5
        "2st Semestr/lubNumber2.5/headerStack.h"
        "2st Semestr/lubNumber2.5/mainStack.c"
        "2st Semestr/lubNumber2.5/functionsStack.c"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")

add_executable(Practice
        "2st Semestr/Practice/headerPractice.h"
        "2st Semestr/Practice/functionsPractice.c"
        "2st Semestr/Practice/mainPractice.c"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")

