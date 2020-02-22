#include <stdlib.h>
#include "../header/stack.h"

/**
 * Creates a new stack
 *
 * @return Pointer to the stack
 */
STACK *createStack(void) {
    STACK *stack;

    stack = (STACK *)malloc(sizeof(STACK));
    if (stack) {
        stack->count = 0;
        stack->top = NULL;
    }
    return stack;
}

/**
 * Adds an element to a stack
 *
 * @param stack a pointer to the stack to add an element to
 * @param data  a pointer to the element to add to the stack
 * @return true if successful; false otherwise
 */
bool pushStack(STACK *stack, void *data) {
    STACK_NODE *node;
    node = (STACK_NODE *)malloc(sizeof(STACK_NODE));
    if (!node) {
        return false;
    }
    node->data = data;
    node->link = stack->top;
    stack->top = node;
    (stack->count)++;
    return true;
}

/**
 * Removes an element from a stack
 *
 * @param stack the stack to remove an element from
 * @return a pointer to the the removed element
 */
void *popStack(STACK *stack) {
    void *data;
    STACK_NODE *temp;

    if (stack->count == 0) {
        data = NULL;
    } else {
        temp = stack->top;
        data = stack->top->data;
        stack->top = stack->top->link;
        free(temp);
        (stack->count)--;
    }
    return data;
}

/**
 * Returns the element at the top of the stack
 *
 * @param stack the stack to return the top element from
 * @return the element at the top of the stack
 */
void *stackTop(STACK *stack) {
    if (stack->count == 0) {
        return NULL;
    } else {
        return stack->top->data;
    }
}

/**
 * Determines if a stack is empty
 *
 * @param stack the stack to check
 * @return true if the stack is empty; false otherwise
 */
bool emptyStack(STACK *stack) {
    return stack->count == 0;
}