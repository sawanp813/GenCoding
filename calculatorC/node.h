#ifndef PS5_NODE_H
#define PS5_NODE_H

typedef struct node {
    union {
        double value;
        char operator;
    } contents;
    int type;
    int precedence;
    struct node* next;
} node;

struct node* createNumberNode(double value, int type); //Create a new node with a given value
struct node* createOperatorNode(char value, int type);

#endif //PS5_NODE_H
