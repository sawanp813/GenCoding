#include "precedence.h"

bool checkPrecedence(char check, char top) {

    bool result;

//    char firstSet[1] = {'^'};
//    char secondSet[2] = {'*', '/'};
//    char thirdSet[2] = {'+', '-'};
//
//    char operatorSet[3] = {firstSet, secondSet, thirdSet};
//    int length = 3;
//
//    for (int i = 0; i < length; i++) {
//
//        if (check)
//    }

    if (check == '^') {
        result = false;

    } else if (check == '*' | check == '/') {
        if (top == '*' | top == '/') {
            result = true;

        } else if (top == '^')
            result = false;
        else
            result = false;
    } else {
        if (top == '^' | top == '*' | top == '/')
            result = false;
        else
            result = true;
    }

    return result;

}