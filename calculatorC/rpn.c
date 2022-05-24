#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "rpn.h"
#include "errors.h"


double evaluate (char* expression, int* status) {

    resetHeight();
//    int height = getHeight();
//    printf("Height: %d\n", height);
    int number = 0;
    int operator = 1;

    // Setting delimiter for strtok() function
    const char delim[2] = " ";

//    printf("RPN Expression to evaluate: %s\n", expression);

    char* newExpression[100];
    memset(newExpression, 0, 100);
    strcpy(newExpression, expression);
    // First call to strtok(), must be done outside of loop due to how function is written
    char *token = strtok(newExpression, delim);

    // Checking for empty string
//    printf("%lu\n", strlen(expression));
//    if (strlen(expression) == 0)
//        goto ERR4;

    // Checking if result of first call to strtok() is an operator, redirects to error if necessary
    if (*token == '+' | *token == '-' | *token == '*' | *token == '/' | *token == '^')
        goto ERR2;

    // If not an operator, a node is created for the numerical value which is pushed to stack
    node* Node = createNumberNode(strtod(token, NULL), number);
    push(Node);

    // Stack height is updated
    int Height = getHeight();
    int count = 0;


    while ( token != NULL ) {

        count++;
        int Height = getHeight(); // Updating stack height at start of loop once again

        token = strtok(NULL, delim); // Next term in string is pulled

        if (!token) { // If end of expression is reached, break from loop and pop the result of expression
            break;
        }

//        node* newNode = createNode(strtod(token, NULL)); // If expression is still being evaluated, create new node with the new token

        // If token is an operator, send it through switch statement circuit for evaluation of expression
        if (*token == '+' | *token == '-' | *token == '*' | *token == '/' | *token == '^') {

            node* newNode = createOperatorNode(*token, operator);

            if (Height < 2) { // If a token is an operator and there are less than 2 numbers in stack, redirect to error - TOO MANY OPERATORS
                goto ERR2;
            }

            // Decrement type of node back to an operator and evaluate the expression, answer stored in result
//            (newNode->type)--;
            node* val1 = pop();
            node* val2 = pop();
            node* result;

            switch(*token) {
                case '+':
                    result = createNumberNode(val2->contents.value + val1->contents.value, number);
                    break;
                case '-':
                    result = createNumberNode(val2->contents.value - val1->contents.value, number);
                    break;
                case '*':
                    result = createNumberNode(val2->contents.value * val1->contents.value, number);
                    break;
                case '/':
                    result = createNumberNode(val2->contents.value / val1->contents.value, number);
                    break;
                case '^':
                    result = createNumberNode(power(val2->contents.value, val1->contents.value), number);
                    break;
                default:
                    printf("Something went wrong.\n");
                    break;
            }

            // Once expression is evaluated, the number nodes in expression are freed, as well as node containing operator. Pointers are grounded.
            free(newNode);
            free(val1);
            free(val2);
            val1 = NULL;
            val2 = NULL;
            newNode = NULL;
            push(result); // Result is pushed back onto stack

        } else {

            node* newNode = createNumberNode(strtod(token, NULL), number);
            push(newNode); // If token is NOT an operator, just push node onto stack and continue

        }

    }

    Height = getHeight(); // Update height once a 'null' token has been reached, for error-checking purposes

    if (Height > 1) // If there is more than one node left in stack after loop terminates, there are too many operands
        goto ERR1;

//    printf("%d\n", *status);
    *status = 0;
    errorCheck(status, NULL); // Final error-check before function returns
    return (pop()->contents.value); // If there is only one number left in stack, it is popped and returned by evaluate()


    char* dull;
    // Error-Handling
    ERR1:
    *status = -2;
    errorCheck(status, NULL);
    return -1;
    ERR2:
    *status = -3;
    errorCheck(status, NULL);
    return -1;
    ERR3:
    *status = -1;
    errorCheck(status, NULL);
    return -1;
    ERR4:
    *status = -4;
    errorCheck(status, NULL);
    return -1;

}


// Power function: takes two doubles as input and returns the result of the expression: n1 ^ n2
double power (double n1, double n2) {

    double result = 1;

    if (n2 > 0) {
        while (n2 != 0) {
            n2--;
            result = result * n1;
        }
    } else if (n2 < 0) {
        while (n2 != 0) {
            n2++;
            result = result / n1;
        }
    }

    return result;
}
