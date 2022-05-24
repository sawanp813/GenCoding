#ifndef PS5_STACK_H
#define PS5_STACK_H

#include "node.h"
void push( node* );
node* pop();
node* peek();
void clearStack();
void printStack();
int getHeight();
void resetHeight();

#endif //PS5_STACK_H
