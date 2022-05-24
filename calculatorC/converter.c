#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "converter.h"
#include "errors.h"
#include "stack.h"

 char* convert(char* expression, int* status, int length, FILE* file) {

    // Initializing buffer and output char string
    char result[length];
    memset(result, 0, length);
    char buffer[length];
    memset(buffer, 0, length);

    // General variables
    int count = 0;
    int number = 0;
    int operator = 1;
    char* op;

    // Node pointers
    struct node* toAdd;
    struct node* toCompare;
    struct node* toCheck;
    node* Node;

    // Checking for empty string
    if (strlen(expression) == 0)
        goto ERR4;

    // Setting delimiter for strtok() function
    const char delim[2] = " ";

    // First call to strtok(), must be done outside of loop due to how function is written
    char *token = strtok(expression, delim);

    if (*token == '+' | *token == '-' | *token == '*' | *token == '/' | *token == '^')
        goto ERR2;
    else if (*token == '(') {
        Node = createOperatorNode(*token, operator);
        push(Node);
    } else {
        Node = createNumberNode(strtod(token, NULL), number);
        sprintf(buffer, "%f ", Node->contents.value);
        strcat(result, buffer);
    }

    // Main while function for operators
     while ( token != NULL ) {
         count++;
         token = strtok(NULL, delim);
         int height = getHeight();

         if (!token) { // If end of expression is reached, break from loop and pop the result of expression
             break;
         }

         // For all operators except parentheses
         if (*token < 48 & *token != 40 & *token != 41 | *token == 94) {
             node* node = createOperatorNode(*token, operator);

             if (height > 0) {
                 toCompare = peek();
                 if (height > 0) {
                     while ((height > 0) & ((node->precedence) > (toCompare->precedence))) {

                         toAdd = pop();
                         sprintf(buffer, "%c ", toAdd->contents.operator);
                         strcat(result, buffer);
                         free(toAdd);
                         toAdd = NULL;

                         height = getHeight();
                         if (height > 0)
                            toCompare = peek();
                         else
                             break;

                     }
                 }

             } push(node);

         // Handles case if token is a left parentheses
         } else if (*token == '(') {
             node* Node = createOperatorNode(*token, operator);
             push(Node);

         // Handles case if token is a right parentheses
         } else if (*token == ')') {
             toCheck = peek();
             char check = toCheck->contents.operator;
             int hgt = getHeight();
             while(check != '(' & hgt > 0) {

                 hgt = getHeight();

                 Node = pop();
                 sprintf( buffer, "%c ", Node->contents.operator);
                 strcat(result, buffer);

                 free(Node);
                 Node = NULL;
                 toCheck = peek();

                 if (toCheck)
                    check = toCheck->contents.operator;
                 if (hgt == 1 & check != '(')
                     goto ERR5;

             }

             height = getHeight();
             if (check == '(') {

                 node *trash = pop();
                 free(trash);
                 trash = NULL;
             }
         } else if (*token < 48 | *token > 57) {
            goto ERR6;
         }  else {

             Node = createNumberNode(strtod(token, NULL), number);
             sprintf( buffer, "%f ", Node->contents.value);
             strcat(result, buffer);

         }
     }

     int height = getHeight();

     // Popping all remaining operators and appending them to string unless they are parentheses
     while(height != 0) {
         toAdd = pop();
         if (toAdd->contents.operator == '(' | toAdd->contents.operator == ')') {
             goto ERR5;
         }

         sprintf( buffer, "%c ", toAdd->contents.operator);
         strcat(result, buffer);
         free(toAdd);
         toAdd = NULL;
         height = getHeight();

     }

     char* result_p = &result;
     return result_p;

     ERR1:
     *status = -2;
     errorCheck(status, file);
     return "";

     ERR2:
     *status = -3;
     errorCheck(status, file);
     return "";

     ERR3:
     *status = -1;
     errorCheck(status, file);
     return "";

     ERR4:
     *status = -4;
     errorCheck(status, file);
     return "";

     ERR5:
     *status = -5;
     errorCheck(status, file);
     return "";

     ERR6:
     *status = -6;
     errorCheck(status, file);
     return "";

 }

