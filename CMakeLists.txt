cmake_minimum_required(VERSION 3.24)
project(myLabs C)

set(CMAKE_C_STANDARD 99)

add_executable(labNumber2.4
        "2st Semestr/lubNumber2.4/mainUnion.c"
        "2st Semestr/lubNumber2.4/functionsUnion.c"
        "2st Semestr/lubNumber2.4/headerUnion.h"
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

add_executable(Lections
        "2st Semestr/Lections/headerLections.h"
        "2st Semestr/Lections/mainLections.c"
        "2st Semestr/Lections/functionsLections.c"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")

add_executable(labNumber2.6
        "2st Semestr/lubNumber 2.6/headerRing.h"
        "2st Semestr/lubNumber 2.6/mainRing.c"
        "2st Semestr/lubNumber 2.6/functionsRing.c"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")

add_executable(labNumber2.7
        "2st Semestr/lubNumber2.7/headerTree.h"
        "2st Semestr/lubNumber2.7/mainTree.c"
        "2st Semestr/lubNumber2.7/functionsTree.c"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")

add_executable(numberSystems
        "2st Semestr/numbersystems/headerSystems.h"
        "2st Semestr/numbersystems/mainSystems.c"
        "2st Semestr/numbersystems/functionsSystems.c"
        "2st Semestr/myLibrary.h"
        "2st Semestr/myLibrary.c")
