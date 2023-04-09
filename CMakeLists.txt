cmake_minimum_required(VERSION 3.24)
project(myLabs C)

set(CMAKE_C_STANDARD 99)

add_executable(labNumber2.4
        "2st Semestr/lubNumber2.4/mainUnion.c"
        "2st Semestr/lubNumber2.4/functionsUnion.c"
        "2st Semestr/lubNumber2.4/headerUnion.h" )

add_executable(labNumber2.4.2
        "2st Semestr/lubNumber2.4.2/mainUnion2.c"
        "2st Semestr/lubNumber2.4.2/functionsUnion2.c"
        "2st Semestr/lubNumber2.4.2/headerUnion2.h" )

add_executable(labNumber2.5
        "2st Semestr/lubNumber2.5/headerStack.h"
        "2st Semestr/lubNumber2.5/mainStack.c"
        "2st Semestr/lubNumber2.5/functionsStack.c")

