#ifndef C_DATA_STRUCTURES_STACK_H
#define C_DATA_STRUCTURES_STACK_H

#include <stdbool.h>

// typedefs
typedef struct node {
    void *data;
    struct node *link;
} STACK_NODE;

typedef struct stack
{
    int count;
    STACK_NODE *top;
} STACK;

// Function prototypes
STACK *createStack(void);
bool pushStack(STACK *stack, void *data);
void *popStack(STACK *stack);
void *stackTop(STACK *stack);
bool emptyStack(STACK *stack);

#endif //C_DATA_STRUCTURES_STACK_H
