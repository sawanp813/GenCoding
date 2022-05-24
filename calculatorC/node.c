#include <stdlib.h>
#include <stdio.h>
#include "node.h"

struct node* createNumberNode(double value, int type) {

    node* node_p = NULL;
    node_p = (struct node*) malloc(sizeof(node));
//    enum {OPERATOR, NUMBER} val;

    if (node_p == NULL) // checking if malloc returned an address or NULL
        printf("Not enough memory available for allocation.\n");
    else {

        node_p->contents.value = value;
        node_p->next = NULL;
        node_p->type = type; // Default, changed if needed in rpn.c
        node_p->precedence = NULL;

    }

    return node_p;

}

struct node* createOperatorNode(char value, int type) {

    node* node_p = NULL;
    node_p = (struct node*) malloc(sizeof(node));
//    enum {OPERATOR, NUMBER} val;

    if (node_p == NULL) // checking if malloc returned an address or NULL
        printf("Not enough memory available for allocation.\n");
    else {

        node_p->contents.operator = value;
        node_p->next = NULL;
        node_p->type = type; // Default, changed if needed in rpn.c
        if (value == '^')
            node_p->precedence = 1;
        else if (value == '(' | value == ')')
            node_p->precedence = 4;
        else if (value == '*' | value == '/')
            node_p->precedence = 2;
        else if (value == '+' | value == '-')
            node_p->precedence = 3;
        else {
            printf("invalid operator.\n");
            exit(-1);
        }
    }

    return node_p;

}