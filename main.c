#include <stdio.h>
#include <stdlib.h>
#include "header/stack.h"

int main() {
    STACK *stack;
    int *value;

    stack = createStack();
    value = (int *)malloc(sizeof(int));
    *value = 23;
    pushStack(stack, value);
    printf("Stack size: %d\n", stack->count);
    value = (int *)malloc(sizeof(int));
    *value = 45;
    pushStack(stack, value);
    printf("Stack size: %d\n", stack->count);

    value = (int *)popStack(stack);
    printf("Stack size %d, popped value: %d\n", stack->count, *value);
    free(value);
    value = (int *)popStack(stack);
    printf("Stack size %d, popped value: %d\n", stack->count, *value);
    free(value);

    return 0;
}
