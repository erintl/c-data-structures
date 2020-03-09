#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "stack_examples.h"

void decimalToBinary() {
    int *number;
    int *digit;
    STACK *stack;

    stack = createStack();
    number = (int *)malloc(sizeof(int));
    printf("Enter an integer: ");
    scanf("%d", number);

    while(*number > 0) {
        digit = (int *)malloc(sizeof(int));
        *digit = *number % 2;
        pushStack(stack, digit);
        *number = *number / 2;
    }

    printf("The number in binary is:\n");
    while (!emptyStack(stack)) {
     digit = (int *)popStack(stack);
     printf("%d", *digit);
     free(digit);
    }
    destroyStack(stack);
    free(number);
}

const char closeMiss[] = "Close paren missing at line";
const char openMiss[] = "Open paren missing at line";

int checkParentheses() {
    STACK *stack;
    char token;
    char *data;
    char filename[30];
    FILE *file;
    int lineCount = 1;

    stack = createStack();
    printf("Enter file name: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (!file) {
        printf("Error open %s\n", filename);
        return 100;
    }

    while((token = fgetc(file)) != EOF) {
        if (token == '\n') {
            lineCount++;
        } else if (token == '(') {
            data = (char *)malloc(sizeof(char));
            pushStack(stack, data);
        } else {
            if (token == ')') {
                if (emptyStack(stack)) {
                    printf("%s %d\n", openMiss, lineCount);
                    return 1;
                } else {
                    popStack(stack);
                }
            }
        }
    }

    if (!emptyStack(stack)) {
        printf("%s %d\n", closeMiss, lineCount);
        return 1;
    }

    destroyStack(stack);
    return 0;
}