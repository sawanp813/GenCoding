#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

node* head = NULL;
int height = 0;


void push(node* Node) {

    if (height != 0)
        Node->next = head;

    head = Node;
    height++;

}

node* pop() {

    node* toReturn = head;
    head = head->next;
    height--;

    return toReturn;

}

node* peek() {

    return head;

}

void clearStack() {

    while (head) {

        node* toClear = head;
        head = head->next;
        free(toClear);
        height--;

    }

    free(head);
    height--;
    head = NULL;

}

void printStack() {

    node* Node = head;

    while (Node) {

        if (Node->type == 0)
            printf("%f\n", Node->contents.value);
        else
            printf("%c\n", Node->contents.operator);

        Node = Node->next;

    }

}

int getHeight() {

    return height;

}

void resetHeight() {

    height = 0;

}